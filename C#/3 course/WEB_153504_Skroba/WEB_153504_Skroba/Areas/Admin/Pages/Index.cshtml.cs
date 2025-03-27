using Microsoft.AspNetCore.Mvc.RazorPages;
using WEB_153504_Skroba.Domain.Entities;
using WEB_153504_Skroba.Domain.Models;
using WEB_153504_Skroba.Services.ProductService;

namespace WEB_153504_Skroba.Areas.Admin.Pages
{
	public class IndexModel : PageModel
    {
        private readonly ITeaService _teaService;

        public IndexModel(ITeaService teaService)
        {
            _teaService = teaService;
        }

        public ListModel<Tea> Tea { get; set; } = new ListModel<Tea>();

        public int CurrentPage { get; set; }
        public int TotalPages { get; set; }

        public async Task OnGetAsync(int pageNo = 1)
        {
            var response = await _teaService.GetProductListAsync(null, pageNo);

            if (response.Success)
            {
                Tea = response.Data;
                CurrentPage = response.Data.CurrentPage;
                TotalPages = response.Data.TotalPages;
            }
        }
    }
}
