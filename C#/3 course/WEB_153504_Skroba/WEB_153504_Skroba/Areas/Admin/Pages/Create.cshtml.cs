using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Mvc.RazorPages;
using Microsoft.AspNetCore.Mvc.Rendering;
using WEB_153504_Skroba.Services.CategoryService;
using WEB_153504_Skroba.Services.ProductService;
using WEB_153504_Skroba.Domain.Entities;

namespace WEB_153504_Skroba.Areas.Admin.Pages
{
    public class CreateModel : PageModel
    {
        private readonly ITeaService _teaService;
		private readonly ICategoryService _categoryService;

		public CreateModel(ITeaService teaService, ICategoryService categoryService)
        {
            _teaService= teaService;
            _categoryService= categoryService;
        }

        public async Task<IActionResult> OnGet()
        {
			var response = await _categoryService.GetCategoryListAsync();
			if (!response.Success)
			{
				return NotFound();
			}
			ViewData["CategoryId"] = new SelectList(response.Data, "Id", "Name");
			return Page();
		}

        [BindProperty]
        public Tea Tea { get; set; } = default!;

		[BindProperty]
		public IFormFile? Image { get; set; }


		// To protect from overposting attacks, see https://aka.ms/RazorPagesCRUD
		public async Task<IActionResult> OnPostAsync()
        {
			if (!ModelState.IsValid)
			{
				return Page();
			}

			var response = await _teaService.CreateProductAsync(Tea, Image);

			if (!response.Success)
			{
				return Page();
			}

			return RedirectToPage("./Index");
		}
    }
}
