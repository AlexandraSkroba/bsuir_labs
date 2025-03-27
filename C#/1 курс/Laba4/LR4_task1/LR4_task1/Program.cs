using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace LR4_task1
{
    public class Program
    {
        public static void Main(string[] args)
        {

            Console.WriteLine("Программа хранит информацию об адресе АТС, числе абонентов, абонентской плате (для всех абонентов одна)." +
                "\nТак же есть возможность изменять размер тарифа (увеличивать или уменьшать), перезаписывать данные АТС.");

            while (true)
            {
                Console.Write("Введите адрес АТС: ");
                string Address_Of_ATS = Console.ReadLine();

                Console.Write("Введите число абонентов: ");
                int Number_Of_Subscribers = Convert.ToInt32(Console.ReadLine());

                Console.Write("Введите абонентскую плату: ");
                double Subscription_Fee = Convert.ToDouble(Console.ReadLine());

                Class_Singleton obj = Class_Singleton.getInstance(Address_Of_ATS, Number_Of_Subscribers, Subscription_Fee);

                obj.Calculation_Of_Money();

                Console.Write("\n\nХотите ввести новую абонентскую плату? (1 - Да, 0 - Нет): ");
                int answer = Convert.ToInt32(Console.ReadLine());

                if (answer == 0) break;

                Console.Write("Введите новую абонентскую плату: ");
                double New_Fee = Convert.ToDouble(Console.ReadLine());

                obj.Changing_The_Fee(New_Fee);
                obj.Calculation_Of_Money();
                Console.WriteLine();
                break;
            }
        }
    }

}