using WEB_153504_Skroba.Domain.Entities;
using WEB_153504_Skroba.Domain.Models;

namespace WEB_153504_Skroba.API.Services.CategoryService
{
	public interface ICategoryService
	{
		/// <summary>
		/// Получение списка всех категорий
		/// </summary>
		/// <returns></returns>
		public Task<ResponseData<List<Category>>> GetCategoryListAsync();
	}
}
