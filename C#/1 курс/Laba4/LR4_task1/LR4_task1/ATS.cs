using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace LR4_task1
{
    public class Class_Singleton
    {

        private string Address_Of_ATS = "";
        private int Number_Of_Subscribers = 0;
        private double Subscription_Fee = 0;

        private static Class_Singleton instance;


        public static Class_Singleton getInstance(string Address_Of_ATS, int Number_Of_Subscribers, double Subscription_Fee)
        {
            if (instance == null)
                instance = new Class_Singleton(Address_Of_ATS, Number_Of_Subscribers, Subscription_Fee);
            return instance;
        }
        private Class_Singleton(string Address_Of_ATS, int Number_Of_Subscribers, double Subscription_Fee)
        {
            this.Address_Of_ATS = Address_Of_ATS;
            this.Number_Of_Subscribers = Number_Of_Subscribers;
            this.Subscription_Fee = Subscription_Fee;
        }

        public void Calculation_Of_Money()
        {
            double all_money = (double)this.Number_Of_Subscribers * this.Subscription_Fee;

            Console.Write("\nОбщая стоимость абонентской платы: " + all_money);
        }

        public void Changing_The_Fee(double New_Fee)
        {
            this.Subscription_Fee = New_Fee;
        }
    }
}
