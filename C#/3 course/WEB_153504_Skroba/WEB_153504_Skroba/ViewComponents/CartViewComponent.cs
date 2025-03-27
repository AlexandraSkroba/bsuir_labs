using Microsoft.AspNetCore.Mvc;
using WEB_153504_Skroba.Domain.Entities;

namespace WEB_153504_Skroba.ViewComponents
{
    public class CartViewComponent : ViewComponent
    {
        public Cart Cart { get; set; }

        public CartViewComponent(Cart cart)
        {
            Cart = cart;
        }

        public IViewComponentResult Invoke()
        {
            return View(Cart);
        }
    }
}
