using WEB_153504_Skroba.Domain.Entities;
using WEB_153504_Skroba.Domain.Models;
using WEB_153504_Skroba.Services.ProductService;
using WEB_153504_Skroba.Services.CategoryService;
using Microsoft.AspNetCore.Mvc;

namespace WEB_153504_Skroba.Services.TeaService
{
	public class MemoryTeaService : ITeaService
	{

		List<Category> _categories;
		List<Tea> _teas;
		readonly IConfiguration _config;
	
		public MemoryTeaService([FromServices] IConfiguration config, ICategoryService categoryService, int pageNo = 1)
		{
			_config = config;
			_categories = categoryService.GetCategoryListAsync().Result.Data;

			SetupData();
		}


		public void SetupData()
		{
			_teas = new List<Tea>
			{
				new Tea { Id = 1, 
					Name = "Чай 1", 
					Description = "teeeeeeea", 
					Category = _categories.Find(c=>c.NormalizedName.Equals("green")),
					Price = 100, 
					ImagePath = "images/tee1.jpg"},
				new Tea { Id = 2, 
					Name = "Чай 2", 
					Price = 100,
					ImagePath = "images/greenTea2.jpg", 
					Description = "teeeeeeea", 
					Category = _categories.Find(c=>c.NormalizedName.Equals("green")) },
				new Tea { Id = 3,
					Name = "Чай 3",
					Description = "teeeeeeea",
					Category = _categories.Find(c=>c.NormalizedName.Equals("black")),
					Price = 100,
					ImagePath = "images/blackTea1.jpg"},
				new Tea { Id = 4,
					Name = "Чай 4",
					Description = "teeeeeeea",
					Category = _categories.Find(c=>c.NormalizedName.Equals("green")),
					Price = 100,
					ImagePath = "images/greenTea2.jpg"},
				new Tea { Id = 1,
					Name = "Чай 1",
					Description = "teeeeeeea",
					Category = _categories.Find(c=>c.NormalizedName.Equals("green")),
					Price = 100,
					ImagePath = "images/tee1.jpg"},
				new Tea { Id = 2,
					Name = "Чай 2",
					Price = 100,
					ImagePath = "images/greenTea2.jpg",
					Description = "teeeeeeea",
					Category = _categories.Find(c=>c.NormalizedName.Equals("green")) },
				new Tea { Id = 3,
					Name = "Чай 3",
					Description = "teeeeeeea",
					Category = _categories.Find(c=>c.NormalizedName.Equals("black")),
					Price = 100,
					ImagePath = "images/blackTea1.jpg"},
				new Tea { Id = 4,
					Name = "Чай 4",
					Description = "teeeeeeea",
					Category = _categories.Find(c=>c.NormalizedName.Equals("green")),
					Price = 100,
					ImagePath = "images/greenTea2.jpg"},
			};
		}

		public async Task<ResponseData<ListModel<Tea>>> GetProductListAsync(string? categoryNormalizedName, int pageNo = 1)
		{
			try
			{
				var data = string.IsNullOrEmpty(categoryNormalizedName)
					? _teas
					: _teas.Where(p => p.Category?.NormalizedName == categoryNormalizedName).ToList();

				int pageSize = int.Parse(_config["Pagination:ItemsPerPage"]);
				System.Console.WriteLine(pageSize);
				int totalCount = data.Count;
				int totalPages = (int)Math.Ceiling(totalCount / (double)pageNo);
				int startIndex = (pageNo - 1) * pageSize;

				var itemsOnPage = data.Skip(startIndex).Take(pageSize).ToList();

				var listModel = new ListModel<Tea>
				{
					Items = itemsOnPage,
					CurrentPage = pageNo,
					TotalPages = totalPages
				};

				// Создаем объект ResponseData и возвращаем его
				var responseData = new ResponseData<ListModel<Tea>>
				{
					Data = listModel,
					Success = true,
					ErrorMessage = null // Ошибка отсутствует
				};

				return responseData;
			}
			catch (Exception ex)
			{
				// Обработка ошибок, если что-то так
				return new ResponseData<ListModel<Tea>>
				{
					Data = null,
					Success = false,
					ErrorMessage = "Произошла ошибка при получении списка чая: " + ex.Message
				};
			}
		}
		public Task<ResponseData<Tea>> CreateProductAsync(Tea product, IFormFile? formFile)
		{
			throw new NotImplementedException();
		}

		public Task DeleteProductAsync(int id)
		{
			throw new NotImplementedException();
		}

		public Task<ResponseData<Tea>> GetProductByIdAsync(int id)
		{
			throw new NotImplementedException();
		}

		public Task UpdateProductAsync(int id, Tea product, IFormFile? formFile)
		{
			throw new NotImplementedException();
		}
	}
}
