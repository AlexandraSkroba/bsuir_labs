using System;
using System.Collections.Generic;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace LR6_task1
{
    class Program
    {
        public static void Main(string[] args)
        {
            Shape rectangle = new Rectangle("Прямоугольник", 15, 10);
            rectangle.View();

            rectangle.Get_side1(10.5);
            rectangle.Get_side2(50);
            rectangle.ChangeName("Измененный прямоугольник");
            rectangle.View();

            Shape triangle = new Triangle("Треугольник", 20, 20, 40);
            triangle.View();

            triangle.Get_side1(40);
            triangle.ChangeName("Другой треугольник");
            triangle.View();

            Triangle triangle_2 = new Triangle("Ещё один треугольник", 40, 35, 20);
            triangle_2.View();

            triangle_2.Get_side1(50);
            triangle_2.ChangeName("Новое имя треугольника");
            triangle_2.View();
        }   
    }
}