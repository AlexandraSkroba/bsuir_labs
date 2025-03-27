using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _153504_Skroba_Lab6
{
    [Serializable]
    public class Employee
    {
        public Employee() { }
        public Employee(string name, int salary, bool onHoliday) => (Name, Salary, OnHoliday) = (name, salary, onHoliday);
        public string Name { get; set; }
        public int Salary { get; set; }
        public bool OnHoliday { get; set; }
        public override string ToString()
        {
            return "Name: " + Name +
                "\nSalary: " + Salary.ToString() +
                "\nIs on vacation: " + OnHoliday.ToString();
        }
    }
}
