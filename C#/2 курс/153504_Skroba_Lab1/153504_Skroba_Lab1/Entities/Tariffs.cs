using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using _153504_Skroba_Lab1.Collections;

namespace _153504_Skroba_Lab1.Entities
{
    internal class Tariffs
    {
        public string Route { get; set; }
        public double Price { get; set; }
        private MyCustomCollection<Passengers> passengers;
        private string allP;
        public Tariffs(string route, double price)
        {
            Route = route; //маршрут
            Price = price; //цена билета
            passengers = new MyCustomCollection<Passengers>();
            allP = "";
        }

        public string AllP 
        {
            get
            {
                allP = "\t";

                for(int i = 0; i < passengers.Count; i++)
                {
                    allP += "\n   "+passengers[i].FullName;
                }

                return allP;
            }

            set
            {
                allP = value;
            }
        }
        public void AddPassengersToTrain(Passengers item)
        {
            passengers.Add(item);
        }

        public MyCustomCollection<Passengers> GetPassengers()
        {
            return passengers;
        }
    }
}
