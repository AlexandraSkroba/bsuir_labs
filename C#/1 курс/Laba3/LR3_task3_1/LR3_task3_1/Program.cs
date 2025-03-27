using System;
namespace Task3
{
    public class Program
    {
        public static void Main(string[] args)
        {
            Console.WriteLine("Введите дату в формате DD.MM.YYYY");

            string date = Console.ReadLine();
            DateService.GetDay(date);

            Console.Write("Введите число: ");
            int day = Convert.ToInt32(Console.ReadLine());

            Console.Write('\n');

            Console.Write("Введите месяц: ");
            int month = Convert.ToInt32(Console.ReadLine());

            Console.Write('\n');

            Console.Write("Введите год: ");
            int year = Convert.ToInt32(Console.ReadLine());

            DateService.GetDaysSpan(day, month, year);
        }
    }
}