using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace LR3_task3
{
    public class Program
    {
        public static void Main(string[] args)
        {
            Console.WriteLine("Программа определяет день недели произвольной даты. " +
                "\nТакже определяет сколько дней пройдет между текущей датой и датой введенной пользователем.");
            
            Console.Write("Введите дату (например 24.03.2022): ");
            string? date = Console.ReadLine();
            Console.WriteLine($"Ваша дата: {date}");

            DateService.GetDay(date);

            Console.WriteLine("\nТеперь программа определит разницу между текущем днем, и днем, введыным пользователем.");
            
            Console.Write("Введите число: ");
            int day = Convert.ToInt32(Console.ReadLine());

            Console.Write("Введите месяц: ");
            int month = Convert.ToInt32(Console.ReadLine());


            Console.Write("Введите год: ");
            int year = Convert.ToInt32(Console.ReadLine());

            DateService.GetDaysSpan(day, month, year);
        }
    }
}