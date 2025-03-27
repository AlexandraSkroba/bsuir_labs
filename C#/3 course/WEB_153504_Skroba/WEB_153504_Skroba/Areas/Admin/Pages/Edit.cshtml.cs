using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Mvc.RazorPages;
using WEB_153504_Skroba.Services.ProductService;
using WEB_153504_Skroba.Domain.Entities;
using Microsoft.CodeAnalysis.Operations;
using WEB_153504_Skroba.Services.CategoryService;
using WEB_153504_Skroba.Domain.Models;
using Microsoft.AspNetCore.Mvc.Rendering;

namespace WEB_153504_Skroba.Areas.Admin.Pages
{
    public class EditModel : PageModel
    {
        private readonly ITeaService _teaService;
        private readonly ICategoryService _categoryService;

        public EditModel(ITeaService teaService, ICategoryService categoryService)
        {
            _teaService = teaService;
            _categoryService = categoryService;
        }

        [BindProperty]
        public Tea Tea { get; set; } = default!;

        [BindProperty]
        public IFormFile? ImagePath { get; set; }

        public async Task<IActionResult> OnGetAsync(int? id)
        {
            if (id == null)
            {
                return NotFound();
            }

            var response = await _teaService.GetProductByIdAsync(id.Value);

            var responseCat = await _categoryService.GetCategoryListAsync();
            if (!response.Success)
            {
                return NotFound();
            }
            ViewData["CategoryId"] = new SelectList(responseCat.Data, "Id", "Name");

            if (!response.Success)
            {
                return NotFound();
            }
            Tea = response.Data!;

            return Page();
        }

        // To protect from overposting attacks, enable the specific properties you want to bind to.
        // For more details, see https://aka.ms/RazorPagesCRUD.
        public async Task<IActionResult> OnPostAsync()
        {
            if (!ModelState.IsValid)
            {
                return Page();
            }
            await _teaService.UpdateProductAsync(Tea.Id, Tea, ImagePath);

            return RedirectToPage("./Index");
        }

        private async Task<bool> TeaExists(int id)
        {
			var response = await _teaService.GetProductByIdAsync(id);
			return response.Success;
		}
    }
}
