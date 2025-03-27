using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Task1
{
    enum Tariff
    {
        VIP,
        Usual    // перечисление траифного плана
    }
    public class ATS
    {
        public class Client
        {
            private readonly string Name_Of_Client;
            private readonly int Number_Of_Calls;
            private readonly string Status;
            private readonly double Cost_Of_Calls_VIP;
            private readonly double Cost_Of_Calls_Usual;

            Tariff tariff1 = Tariff.VIP;
            Tariff tariff2 = Tariff.Usual;
            public Client(string Name_Of_Client, string Status, int Number_Of_Calls, double Cost_Of_Calls_VIP, double Cost_Of_Calls_Usual)
            {
                this.Name_Of_Client = Name_Of_Client;
                this.Status = Status;
                this.Number_Of_Calls = Number_Of_Calls;
                this.Cost_Of_Calls_VIP = Cost_Of_Calls_VIP;
                this.Cost_Of_Calls_Usual = Cost_Of_Calls_Usual;
            }
            public int Get_Number_Of_Calls()
            {
                return Number_Of_Calls;
            }
            public string Get_Name_Of_Client()
            {
                return Name_Of_Client;
            }
            public string Get_Status()
            {
                return Status;
            }
            public double Creative_Cost_Of_Calls() // метод для определения стоимости опредленного количества звонков по определенному тарифу
            {
                if (Get_Status() == "VIP")
                {
                    return Number_Of_Calls * Cost_Of_Calls_VIP;
                }
                else
                {
                    return Number_Of_Calls * Cost_Of_Calls_Usual;
                }
            }
            public double Information_Cost_Of_Calls() // метод для вычисления по введенному имени стоимость всех звонков по тарифу клиента 
            {
                if (Get_Name_Of_Client() == Console.ReadLine())
                {
                    return Creative_Cost_Of_Calls();
                }
                else
                {
                    return Information_Cost_Of_Calls();
                }
            }
            public string Info()
            {
                return "\n\n\t\t\tИмя: " + Name_Of_Client + ". Статус: " + Get_Status() + ". Кол-во звонков: " + Get_Number_Of_Calls().ToString() + ". Общая стоимость звонков: " + Creative_Cost_Of_Calls().ToString();
            }
        }

        private readonly List<Client> clients;

        public ATS()
        {
            clients = new List<Client>();
        }

        public void AddClient(string Name_Of_Client, string Status, int Number_Of_Calls, double Cost_Of_Calls_VIP, double Cost_Of_Calls_Usual)
        {
            clients.Add(new Client(Name_Of_Client, Status, Number_Of_Calls, Cost_Of_Calls_VIP, Cost_Of_Calls_Usual));
        }

        public void AddClient(Client person)
        {
            clients.Add(person);
        }

        public void PrintInfo()
        {
            foreach (var person in clients)
            {
                Console.WriteLine(person.Info());
            }
        }

        public double Total_Calls()
        {
            double sum = 0;

            foreach (var person in clients)
            {
                sum += person.Creative_Cost_Of_Calls();
            }

            return sum;
        }
    }

    //----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

    class Program
    {
        static void Main(string[] args)
        {
            ATS obj = new();

            char answer = '1';

            do
            {
                Console.Write("Введите имя клиента: ");
                string Name_Of_Client = Console.ReadLine();

                Console.Write("\nВведите статус клиента (VIP or Usual): ");
                string Status = Console.ReadLine();

                Console.Write("\nВведите кол-во звонков: ");
                int Number_Of_Calls = Convert.ToInt32(Console.ReadLine());

                Console.Write("\nВведите стоимость звонков для VIP: ");
                double Cost_Of_Calls_VIP = Convert.ToDouble(Console.ReadLine());

                Console.Write("\nВведите стоимость звонков для Usual: ");
                double Cost_Of_Calls_Usual = Convert.ToDouble(Console.ReadLine());

                obj.AddClient(Name_Of_Client, Status, Number_Of_Calls, Cost_Of_Calls_VIP, Cost_Of_Calls_Usual);

                Console.Write("\nПродолжить ввод? (1/0) ");

                answer = Convert.ToChar(Console.ReadLine());
                Console.Write('\n');

            } while (answer != '0');

            obj.PrintInfo();

            Console.WriteLine($"\n\n\t\t\t\t\tОбщая стоимость звонков клиентов: {obj.Total_Calls()}");
        }
    }
}
