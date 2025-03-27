using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _153504_Skroba_Lab3.Entities
{
    internal class Tariffs
    {
        public string Route { get; set; }
        public double Price { get; set; }
        public Tariffs(string route, double price) => (Route, Price) = (route, price);
    }
}
