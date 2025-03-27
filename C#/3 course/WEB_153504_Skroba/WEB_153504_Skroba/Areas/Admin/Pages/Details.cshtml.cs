using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Mvc.RazorPages;
using WEB_153504_Skroba.Services.ProductService;
using WEB_153504_Skroba.Domain.Entities;

namespace WEB_153504_Skroba.Areas.Admin.Pages
{
    public class DetailsModel : PageModel
    {
        private readonly ITeaService _teaService;

        public DetailsModel(ITeaService teaService)
        {
            _teaService = teaService;
        }

      public Tea Tea { get; set; } = default!; 

        public async Task<IActionResult> OnGetAsync(int? id)
        {
            if (id == null)
            {
                return NotFound();
            }

            var response = await _teaService.GetProductByIdAsync(id.Value);
            if (!response.Success)
            {
                return NotFound();
            }

			Tea = response.Data!;

			return Page();
        }
    }
}
