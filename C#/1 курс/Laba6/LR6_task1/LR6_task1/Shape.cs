using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace LR6_task1
{
    public abstract class Shape
    {
        protected double side_1;
        protected double side_2;
        protected double side_3;
        protected string name;
        public void Get_side1(double side_1)
        {
            this.side_1 = side_1;
        }
        public void Get_side2(double side_2)
        {
            this.side_2 = side_2;
        }
        public void Get_side3(double side_3)
        {
            this.side_3 = side_3;
        }
        public void ChangeName(string NewName)
        {
            name = NewName;
        }
        public abstract void View(); //метод не реализуется в классе

        public abstract double Square();

        //перегрузка
        public Shape(double side_1, double side_2, double side_3, string name) //для треугольника
        {
            this.side_1 = side_1;
            this.side_2 = side_2;
            this.side_3 = side_3;
            this.name = name;
        }
        public Shape(double side_1, double side_2, string name) //для прямоугольника
        {
            this.side_1 = side_1;
            this.side_2 = side_2;
            this.name = name;
        }
    }

    public sealed class Rectangle : Shape //класс запрещенный для переопределения
    {
        public double Side1()
        {
            return side_1;
        }
        public double Side2()
        {
            return side_2;
        }
        public Rectangle(string name, double side_2, double side_1) : base(side_1, side_2, name){}
        public override void View()
        {
            Console.WriteLine("\nНазвание: " + name + " Первая сторона: " + side_1 + " Вторая сторона: " + side_2);
        }
    }

    public class Triangle : Shape
    {
        public double Side1()
        {
            return side_1;
        }
        public double Side2()
        {
            return side_2;
        }
        public double Side3()
        {
            return side_3;
        }
        public Triangle(string name_, double side_1, double side_2, double side_3) : base(side_1, side_2, side_3, name_) {}
        public override void View()
        {
            Console.WriteLine("\nНазвание: " + name + ". Первая сторона " + side_1 + ". Вторая сторона " + side_2 + ". Третья сторона " + side_3);
        }
    }
}
