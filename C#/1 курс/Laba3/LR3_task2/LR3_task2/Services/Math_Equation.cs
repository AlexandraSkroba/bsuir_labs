using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace LR3_task2.Services
{
    public class Math_Equation
    {
        public static double Equation(double z)  
        {
            double x, y;
            if (z < -1) x = -z / 3;
            else x = Math.Abs(z);

            y = Math.Log(x + 0.5) + (Math.Pow(Math.E, x) - Math.Pow(Math.E, -x));

            return y;
        }
    }
}
