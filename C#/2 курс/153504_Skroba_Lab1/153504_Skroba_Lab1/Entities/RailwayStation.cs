using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using _153504_Skroba_Lab1.Collections;

namespace _153504_Skroba_Lab1.Entities
{
    internal class RailwayStation
    {
        public delegate void EventHandler(string message);
        public EventHandler AddEvent;
        public EventHandler BookEvent;

        private MyCustomCollection<Tariffs> tariffsCollections;
        private MyCustomCollection<Passengers> passengersCollections;
        public RailwayStation()
        {
            tariffsCollections = new MyCustomCollection<Tariffs>();
            passengersCollections = new MyCustomCollection<Passengers>();
        }

        public void AddTariffs(string route, double price)
        {
            tariffsCollections.Add(new Tariffs(route, price));

            AddEvent.Invoke($"Был добавлен новый маршрут: {route}, цена - {price}");
        }
        public void ShowAllTarriffs()
        {
            for (int i = 0; i < tariffsCollections.Count; i++)
            {
                Console.WriteLine($"   Маршрут - {tariffsCollections[i].Route} || Стоимость - {tariffsCollections[i].Price}");
            }
        }

        public void AddPassengers(string fullName, string dob, char sex, string pbl)
        {
            passengersCollections.Add(new Passengers(fullName, dob, sex, pbl));

            AddEvent.Invoke($"Был добавлен новый пассажир: {fullName}");
        }

        public void AllTariffs(string fullName, string route)
        {
            for(int i = 0; i < passengersCollections.Count; i++)
            {
                if (passengersCollections[i].FullName.Equals(fullName))
                {
                    for (int j = 0; j < tariffsCollections.Count; j++)
                    {
                        if (tariffsCollections[j].Route.Equals(route))
                        {
                            passengersCollections[i].AddTariffs(tariffsCollections[j]);
                            tariffsCollections[j].AddPassengersToTrain(passengersCollections[i]);

                            BookEvent.Invoke($"Пассажир {fullName} зарегестировался на маршрут {route}");
                        }
                    }
                    return;
                } 
            }

            Console.WriteLine("\n------------Пассажир не зарегестрирован------------\n");
        }

        public void ShowInfoPassengers()
        {
            for(int i = 0; i < passengersCollections.Count; i++)
            {
                Console.WriteLine($"\n   Имя: {passengersCollections[i].FullName}\n   Дата рождения: {passengersCollections[i].DOB}" +
                    $"\n   Пол: {passengersCollections[i].Sex}\n   Место рождения: {passengersCollections[i].PBL}\n   Стоимость поездки: {passengersCollections[i].TotalCost}");
            }
        }

        public void ShowRoutPassengers(string route)
        {
            Console.WriteLine($"\nСписок пассажиров по  маршруту |{route}|:");
            for(int i = 0; i < tariffsCollections.Count; i++)
            {
                if(tariffsCollections[i].Route.Equals(route))
                {
                    Console.WriteLine($"{tariffsCollections[i].AllP}");
                }
            }
        }
    }
}
