using Microsoft.AspNetCore.Mvc;
using WEB_153504_Skroba.Models;

namespace WEB_153504_Skroba.Controllers
{
    public class HomeController : Controller
    {
		public ActionResult Index()
        {
            ViewData["Message"] = "Лабораторная работа 2";

			var listItems = new List<ListDemo>
			{
				new ListDemo { Id = 1, Name = "Item 1" },
				new ListDemo { Id = 2, Name = "Item 2" },
				new ListDemo { Id = 3, Name = "Item 3" }
			};

			return View(listItems);
        }
    }
}
