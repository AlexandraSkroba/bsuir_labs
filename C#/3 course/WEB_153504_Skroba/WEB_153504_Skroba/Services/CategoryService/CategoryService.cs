using WEB_153504_Skroba.Domain.Entities;
using WEB_153504_Skroba.Domain.Models;

namespace WEB_153504_Skroba.Services.CategoryService
{
	public class MemoryCategoryService : ICategoryService
	{
		public Task<ResponseData<List<Category>>> GetCategoryListAsync()
		{
			var categories = new List<Category> {
					new Category {Id=1, Name="Зеленый чай", NormalizedName="green"},
					new Category {Id=2, Name="Черный чай", NormalizedName="black"},
					new Category {Id=3, Name="Зеленый связанный чай", NormalizedName="greenconn"},
					new Category {Id=4, Name="Белый чай", NormalizedName="white"},
					new Category {Id=5, Name="Желтый чай", NormalizedName="yellow"},
					new Category {Id=6, Name="Улун", NormalizedName="ulun"},
			};

			var result = new ResponseData<List<Category>>();
			result.Data = categories;
			return Task.FromResult(result);
		}
	}
}
