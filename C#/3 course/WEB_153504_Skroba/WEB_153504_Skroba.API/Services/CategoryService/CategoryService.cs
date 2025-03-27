using WEB_153504_Skroba.API.Data;
using WEB_153504_Skroba.Domain.Entities;
using WEB_153504_Skroba.Domain.Models;

namespace WEB_153504_Skroba.API.Services.CategoryService
{
	public class CategoryService : ICategoryService
	{

		AppDbContext _context;
		public CategoryService(AppDbContext context)
		{
			_context = context;
		}
		public Task<ResponseData<List<Category>>> GetCategoryListAsync()
		{
			var result = new ResponseData<List<Category>>();
			List<Category> categoryList = _context.Categories.ToList();
			result.Data = categoryList;

			return Task.FromResult(result);
		}
	}
}
