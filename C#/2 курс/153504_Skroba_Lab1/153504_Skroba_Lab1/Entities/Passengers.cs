using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using _153504_Skroba_Lab1.Collections;

namespace _153504_Skroba_Lab1.Entities
{
    internal class Passengers
    {
        public string FullName { get; set; }
        public string DOB { get; set; }
        public char Sex { get; set; }
        public string PBL { get; set; }
        private MyCustomCollection<Tariffs> tariffs;
        public Passengers(string fullName, string dob, char sex, string pbl)
        {
            FullName = fullName; //
            DOB = dob; //дата рождения
            Sex = sex; //пол
            PBL = pbl; //место рождения
            tariffs = new MyCustomCollection<Tariffs>(); //регистрация билета
            totalCost = 0; //общая стоимость билетов
        }

        private double totalCost;

        public double TotalCost
        {
            get { 
                totalCost = 0;

                for(int i = 0; i < tariffs.Count; i++)
                {
                    totalCost += tariffs[i].Price;
                }

                return totalCost;
            }

            set
            {
                totalCost = value;
            }
        }

        public void AddTariffs(Tariffs item)
        {
            tariffs.Add(item);
        }

        public MyCustomCollection<Tariffs> GetTariffs()
        {
            return tariffs;
        }
    }
}
