using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace LR3_task1
{
    public class Program
    {
        public static void Main (string [] args)
        {
            double x, y, z;
            Console.WriteLine("Программа решает уравнение вида z = min(x, 2y + x) - min(7x + 2y, y).");
            Console.Write("Введите два числа (x, y): ");
            x = Convert.ToDouble(Console.ReadLine());
            y = Convert.ToDouble(Console.ReadLine());

            z = Math_Equation.min(x, 2*y + x) - Math_Equation.min(7 * x + 2 * y, y);
            Console.WriteLine($"Ответ: {z}");
        }
    }
}