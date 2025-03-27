using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _153504_Skroba_Lab1.Entities
{
    internal class MyException : Exception
    {
        public MyException(string message) : base(message) { }
    }
}
