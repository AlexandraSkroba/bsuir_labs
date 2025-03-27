using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Mvc.RazorPages;
using WEB_153504_Skroba.Services.ProductService;
using WEB_153504_Skroba.Domain.Entities;

namespace WEB_153504_Skroba.Areas.Admin.Pages
{
    public class DeleteModel : PageModel
    {
        private readonly ITeaService _teaService;

        public DeleteModel(ITeaService teaService)
        {
            _teaService = teaService;
        }

        [BindProperty]
      public Tea Tea { get; set; } = default!;

        public async Task<IActionResult> OnGetAsync(int? id)
        {
            if (id == null)
            {
                return NotFound();
            }

            /*var response = await _teaService.GetProductByIdAsync(id.Value);*/
            var response = await _teaService.GetProductByIdAsync((int)id);

            if (!response.Success)
            {
                return NotFound();
            }

			Tea = response.Data!;

			return Page();
        }

        public async Task<IActionResult> OnPostAsync(int? id)
        {
            if (id == null)
            {
                return NotFound();
            }

			try
			{
				await _teaService.DeleteProductAsync(id.Value);
			}
			catch (Exception e)
			{
				return NotFound(e.Message);
			}

			return RedirectToPage("./Index");
        }
    }
}
