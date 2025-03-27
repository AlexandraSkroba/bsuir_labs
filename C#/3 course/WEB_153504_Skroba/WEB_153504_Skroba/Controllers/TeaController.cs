using Microsoft.AspNetCore.Mvc;
using WEB_153504_Skroba.Extensions;
using WEB_153504_Skroba.Services.CategoryService;
using WEB_153504_Skroba.Services.ProductService;

namespace WEB_153504_Skroba.Controllers
{
	[Route("catalog")]
	public class TeaController : Controller
	{
		//Внедрите в конструктор контроллера объекты типа IProductService и ICategoryService
		ITeaService _teaService;
		ICategoryService _categoryService;
		public TeaController(ITeaService teaService, ICategoryService categoryService) {
			_teaService = teaService;
			_categoryService = categoryService;
		}

		[Route("{category?}")]
		public async Task<IActionResult> Index(string? category, int pageno = 1)
		{
            // получить список категорий
            var categoryResponse = await _categoryService.GetCategoryListAsync();

            // если список не получен, вернуть код 404
            if (!categoryResponse.Success)
                return NotFound(categoryResponse.ErrorMessage);

            // передать список категорий во ViewData
            ViewData["categories"] = categoryResponse.Data;

            // передать во ViewData имя текущей категории
            ViewData["currentCategory"] = category == null 
				? "Все" 
				: categoryResponse
							.Data!
							.FirstOrDefault((c) => c.NormalizedName.Equals(category))?.Name;

            // получить список объектов
            var productResponse = await _teaService.GetProductListAsync(category, pageno);

            // если список не получен, вернуть код 404
            if (!productResponse.Success)
				return NotFound(productResponse.ErrorMessage);

            // проверить, был ли запрос асинхронным
            if (Request.IsAjaxRequest())
			{
                // в случае асинхронного запроса вернуть частичное представление
                return PartialView("_CatalogPartial", productResponse.Data);
			}

            // вернуть полное представление
            return View(productResponse.Data);
		}
	}
}
