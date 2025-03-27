using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace LR3_task3
{
    public class DateService
    {

        public static string GetDay(string date)
        {

            char[] separators = new char[] { '.' };
            string[] subs = date.Split(separators, StringSplitOptions.RemoveEmptyEntries);

            int month_code, date_code, year_code;
            int.TryParse(subs[0], out date_code);
            int.TryParse(subs[1], out month_code);
            int.TryParse(subs[2], out year_code);

            int month = month_code;
            int year = year_code;

            //determine the code of the month
            if (month_code == 01 || month_code == 10) month_code = 1;
            if (month_code == 04 || month_code == 07) month_code = 0;
            if (month_code == 02 || month_code == 03 || month_code == 11) month_code = 4;
            if (month_code == 05) month_code = 2;
            if (month_code == 08) month_code = 3;
            if (month_code == 06) month_code = 5;
            if (month_code == 12 || month_code == 09) month_code = 6;

            //determine the code of the year
            int centur_code = (int)year_code / 100;
            if (year_code % 100 != 0) centur_code++;

            while (centur_code >= 4)
            {
                centur_code -= 4;
            }
            if (centur_code <= 0) centur_code += 4;
            if (centur_code == 1) centur_code = 6;
            if (centur_code == 4) centur_code = 0;
            if (centur_code == 2) centur_code = 4;
            if (centur_code == 3) centur_code = 2;

            year_code = year_code % 100;
            year_code = (centur_code + year_code + (year_code / 4)) % 7; 

            int result = (date_code + month_code + year_code) % 7;

            //for leap year
            if (year % 4 == 0)
            {
                if (month == 1 || month == 2) result -= 1;
            }

            if (result == 0) Console.WriteLine("День недели: Суббота");
            if (result == 1) Console.WriteLine("День недели: Воскресенье");
            if (result == 2) Console.WriteLine("День недели: Понедельник");
            if (result == 3) Console.WriteLine("День недели: Вторник");
            if (result == 4) Console.WriteLine("День недели: Среда");
            if (result == 5) Console.WriteLine("День недели: Четверг");
            if (result == 6 || result == -1) Console.WriteLine("День недели: Пятница");

                return date;
        }

        public static void GetDaysSpan(int day, int month, int year)
        {
            int day_, month_, year_;

            string x = Convert.ToString(System.DateTime.Now);

            char[] arrays = x.ToCharArray();

            day_ = (arrays[0] - 48) * 10 + arrays[1] - 48;
            month_ = (arrays[3] - 48) * 10 + arrays[4] - 48;
            year_ = (arrays[6] - 48) * 1000 + (arrays[7] - 48) * 100 + (arrays[8] - 48) * 10 + (arrays[9] - 48);

            DateTime date1 = new DateTime(year, month, day);
            DateTime date2 = new DateTime(year_, month_, day_);
            Console.WriteLine("\nРазность дней между настоящим и введённым пользователем: " + date1.Subtract(date2).Days);
        }

    }
}
