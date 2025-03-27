using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Task1
{
    public class Program
    {
        public static void Main(string[] args)
        {
            Complex obj1 = new Complex(1, -1);
            Complex obj2 = new Complex(1, -1);

            //Complex.Comparizon(obj1, obj2);

            double dd = (double)obj1; //явное преобразование
            obj1 = dd; //неявное преобразование
        }
    }
}
