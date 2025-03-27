using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Task1
{
    public class Complex
    {
        public double A { get; set; }
        public double B { get; set; }

        public Complex(double a, double b)
        {
            A = a;
            B = b;
        }
        // перегрузка чтобы складывать объекты комплексных типов - классов и структур
        public static Complex operator + (Complex first, Complex second) //перегружаемый оператор будет использоваться для всех объектов данного класса
        {
            return new Complex(first.A + second.A, first.B + second.B);
        }

        public static Complex operator - (Complex first, Complex second)
        {
            return new Complex(first.A - second.A, first.B - second.B);
        }

        public static Complex operator * (Complex first, Complex second)
        {
            return new Complex(first.A * second.A, first.B * second.B);
        }

        public static Complex operator / (Complex first, Complex second)
        {
            if (second.A == 0)
                return new Complex(0, 0);
            if (second.B == 0)
                return new Complex(0, 0);
            return new Complex(first.A / second.A, first.B / second.B);
        }

        public static explicit operator double(Complex x) //явное преобразование
        {
            return x.A;
        }

        public static implicit operator Complex(double x) //неявное преобразование
        {
            return new Complex(x, 0);
        }

        public static bool operator true(Complex obj)
        {
            if ((obj.A != 0) && (obj.B != 0))
                return true;
            return false;
        }
        public static bool operator false (Complex obj)
        {
            if ((obj.A == 0) || (obj.B == 0) )
                return true;
            return false;
        }
        public override string ToString()
        {
            return $"({A};{B})";
        }
    }
}