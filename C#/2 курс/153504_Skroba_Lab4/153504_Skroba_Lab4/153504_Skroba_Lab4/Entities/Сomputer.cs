using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _153504_Skroba_Lab4.Entities
{
    internal class Computer
    {
        public Computer(string name, int releaseDate, double display, bool touchID) => (Name, ReleaseDate, Display, TouchID) = (name, releaseDate, display, touchID);
        public string Name { get; private set; }
        public int ReleaseDate { get; set; }
        public double Display { get; set; }
        public bool TouchID { get; set; }
    }
}
