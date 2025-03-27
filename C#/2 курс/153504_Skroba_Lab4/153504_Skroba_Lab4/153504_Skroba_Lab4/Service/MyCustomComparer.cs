using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using _153504_Skroba_Lab4.Entities;

namespace _153504_Skroba_Lab4.Service
{
    internal class MyCustomComparer :IComparer<Computer>
    {
        public int Compare(Computer x, Computer y) => x.Name.CompareTo(y.Name);
    }
}
