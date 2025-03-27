using Microsoft.EntityFrameworkCore;
using WEB_153504_Skroba.API.Data;
using WEB_153504_Skroba.API.Services.CategoryService;
using WEB_153504_Skroba.Domain.Entities;
using WEB_153504_Skroba.Domain.Models;

namespace WEB_153504_Skroba.API.Services.TeaService
{
	public class TeaService : ITeaService
	{
		// максимальный размер страницы 
		private readonly int _maxPageSize = 20;

		AppDbContext _context;
		/*ICategoryService _categoryService;*/
		/*private List<Category>? _categories;*/
        private readonly IHttpContextAccessor _httpContextAccessor;
        private readonly IWebHostEnvironment _webHostEnvironment;


        public TeaService(AppDbContext context, 
			IHttpContextAccessor httpContextAccessor, IWebHostEnvironment webHostEnvironment)
		{
			_context = context;
            /*_categoryService = categoryService;*/
            _httpContextAccessor = httpContextAccessor;
            _webHostEnvironment = webHostEnvironment;
/*            _categories = _categoryService.GetCategoryListAsync().Result.Data;*/
		}

		public async Task<ResponseData<ListModel<Tea>>> GetProductListAsync(string? categoryNormalizedName, int pageNo = 1, int pageSize = 3)
		{
			if (pageSize > _maxPageSize)
				pageSize = _maxPageSize;
			var query = _context.Teas.AsQueryable();
			var dataList = new ListModel<Tea>();
			query = query.Where(d => categoryNormalizedName == null || d.Category.NormalizedName.Equals(categoryNormalizedName));
			// количество элементов в списке
			var count = query.Count();
			if (count == 0)
			{
				var responseData = new ResponseData<ListModel<Tea>>
				{
					Data = dataList,
				};

				return responseData;
			}
			// количество страниц
			int totalPages = (int)Math.Ceiling(count / (double)pageSize);
			if (pageNo > totalPages)
			{
				var responseData = new ResponseData<ListModel<Tea>>
				{
					Data = null,
					Success = false,
					ErrorMessage = "No such page"
				};

				return responseData;
			}

			dataList.Items = await query
				.Skip((pageNo - 1) * pageSize)
				.Take(pageSize)
				.ToListAsync();
			dataList.CurrentPage = pageNo;
			dataList.TotalPages = totalPages;
			var response = new ResponseData<ListModel<Tea>>
			{
				Data = dataList
			};
			return response;
		}
		public async Task<ResponseData<Tea>> CreateProductAsync(Tea product)
		{
            _context.Teas.Add(product);
            await _context.SaveChangesAsync();

            return new ResponseData<Tea>
            {
                Data = product,
                Success = true
            };
        }

		public Task DeleteProductAsync(int id)
		{
            var recordToDelete = _context.Teas.Find(id);

            if (recordToDelete != null)
            {
                _context.Teas.Remove(recordToDelete);

                _context.SaveChangesAsync();
            }

            return Task.CompletedTask;
        }

		public Task<ResponseData<Tea>> GetProductByIdAsync(int id)
		{
            try
            {
                var teas = _context.Teas.FirstOrDefault(product => product.Id == id);
                if (teas != null)
                {
                    var responseData = new ResponseData<Tea>()
                    {
                        Data = teas,
                        Success = true
                    };

                    return Task.FromResult(responseData);
                }
                else
                {
                    throw new ArgumentOutOfRangeException(nameof(id), "///");
                }
            }
            catch (Exception)
            {
                var responseData = new ResponseData<Tea>()
                {
                    Success = false,
                    ErrorMessage = "///"
                };

                return Task.FromResult(responseData);
            }
        }

		public async Task<ResponseData<string>> SaveImageAsync(int id, IFormFile formFile)
		{
            var responseData = new ResponseData<string>();
            var teas = await _context.Teas.FindAsync(id);
            if (teas == null)
            {
                responseData.Success = false;
                responseData.ErrorMessage = "No item found";

                return responseData;
            }
            else if (_httpContextAccessor.HttpContext == null)
            {
                responseData.Success = false;
                responseData.ErrorMessage = "No HttpContext found";

                return responseData;
            }

            var host = "https://" + _httpContextAccessor.HttpContext.Request.Host;
            var imageFolder = Path.Combine(_webHostEnvironment.WebRootPath, "images");

            if (formFile != null)
            {
                if (!String.IsNullOrEmpty(teas.ImagePath))
                {
                    var prevImageName = Path.GetFileName(teas.ImagePath);
                    var prevImagePath = Path.Combine(imageFolder, prevImageName);

                    File.Delete(prevImagePath);
                }

                var ext = Path.GetExtension(formFile.FileName);
                var fileName = Path.ChangeExtension(Path.GetRandomFileName(), ext);
                var filePath = Path.Combine(imageFolder, fileName);

                using var stream = new FileStream(filePath, FileMode.Create);
                await formFile.CopyToAsync(stream);

                teas.ImagePath = $"{host}/images/{fileName}";

                responseData.Data = teas.ImagePath;
                responseData.Success = true;

                _context.SaveChanges();

                return responseData;
            }
            else
            {
                responseData.Success = false;
                responseData.ErrorMessage = "No formFile found";

                return responseData;
            }
        }

		public async Task UpdateProductAsync(int id, Tea product)
		{
            Tea? productToUpdate = await _context.Teas.FindAsync(id);
            if (productToUpdate != null)
            {
                productToUpdate.CategoryId = product.CategoryId;
                productToUpdate.Name = product.Name;
                productToUpdate.Description = product.Description;
                productToUpdate.Price = product.Price;
                if (product.ImagePath != null)
                    productToUpdate.ImagePath = product.ImagePath;
                _context.Update(productToUpdate);
                await _context.SaveChangesAsync();
            }
        }
	}
}
