using Microsoft.AspNetCore.Authorization;
using Microsoft.AspNetCore.Mvc;
using WEB_153504_Skroba.Domain.Entities;
using WEB_153504_Skroba.Services.ProductService;

namespace WEB_153504_Skroba.Controllers
{
    public class CartController : Controller
    {
        private ITeaService _teaService;
        private Cart _cart;

        public CartController(ITeaService teaService, Cart cart)
        {
            _teaService = teaService;
            _cart = cart;
        }

        public IActionResult Index()
        {
            return View(_cart);
        }

        [Authorize]
        [Route("[controller]/add/{id:int}")]
        public async Task<ActionResult> Add(int id, string returnUrl)
        {
            var data = await _teaService.GetProductByIdAsync(id);
            if (data.Success)
            {
                _cart.AddToCart(data.Data!);
            }
            return Redirect(returnUrl);
        }

        [Authorize]
        public IActionResult RemoveItem(int id, string redirectUrl)
        {
            _cart.RemoveItems(id);
            return Redirect(redirectUrl);
        }
    }
}
