using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace LR3_task2
{
    public class Program
    {
        public static void Main(string[] args)
        {
            Console.WriteLine("Программа решает уравнение, которое задано в условии (вариант 5).");
            Console.Write("Веведите число z: ");
            double z = Convert.ToDouble(Console.ReadLine());

            double y = Services.Math_Equation.Equation(z);
            Console.WriteLine($"Ответ: {y}");
        }
    }
}
