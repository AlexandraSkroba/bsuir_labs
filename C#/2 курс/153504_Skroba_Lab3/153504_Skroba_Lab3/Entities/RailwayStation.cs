using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using _153504_Skroba_Lab3.Entities;

namespace _153504_Skroba_Lab3.Entities
{
    internal class RailwayStation
    {
        private Dictionary<string, Tariffs> tariffsCollections = new Dictionary<string, Tariffs>();
        private List<Passengers> passengersCollections = new();

        public delegate void EventHandler(string message);
        public EventHandler AddEvent;
        public EventHandler ErrorEvent;

        public void AddTariff(string route, double price)
        {
            tariffsCollections.Add(route, new Tariffs(route, price));
            AddEvent.Invoke($"Был добавлен маршрут {route} || Цена - {price}");
        }

        public void AddPassenger(string fullName, string passportNo)
        {
            passengersCollections.Add(new Passengers(fullName, passportNo));
            AddEvent.Invoke($"Был зарегестрирован пассажир {fullName}");
        }

        public void RegistrationTariff(string fullName, string route)
        {
            foreach(var passenger in passengersCollections)
            {
                if (passenger.FullName.Equals(fullName))
                {
                    if (tariffsCollections.ContainsKey(route))
                    {
                        passenger.AddTariffs(tariffsCollections[route]);
                        AddEvent.Invoke($"Пассажир {fullName} купил билет на поезд {route}");
                    }
                    else
                    {
                        ErrorEvent.Invoke($"Поезда {route} не существует!");
                    }

                    return;
                }

                ErrorEvent.Invoke($"Пасаажира {fullName} не существует!");
            }
        }

        public double TotalCostTariff()
        {
            double totalCost = 0;

            foreach (var tariff in tariffsCollections)
            {
                totalCost += tariff.Value.Price;
            }

            return totalCost;
        }

        public List<Tariffs> SortTariffs()
        {
            var sortTariffs = from item in tariffsCollections
                              orderby item.Value.Price
                              select item.Value;

            return new List<Tariffs>(sortTariffs);
        }

        public string GetCostlyPassenger()
        {
            var costlyPassenger = from item in passengersCollections orderby item.TotalCost select item;

            return costlyPassenger.Last().FullName;
        }

        public int CountPassenger(double price)
        {
            var countPassenger = (from item in passengersCollections where item.TotalCost > price select item).Count();

            return countPassenger;
        }

        public void TariffsByCost()
        {
            IEnumerable<(double Price, int Count)> tariffsByCost = from item in tariffsCollections
                                                                  group item.Value by item.Value.Price into gr
                                                                  select (gr.Key, gr.Count());
            foreach(var price in tariffsByCost)
            {
                Console.WriteLine($"Стоимость {price.Price} ---> {price.Count}");
            }
        }

        public void PassangersInfo()
        {
            foreach(var item in passengersCollections)
            {
                Console.WriteLine($"Пассажир {item.FullName}, номер паспорта {item.PassportNo} || Цена - {item.TotalCost}");
            }
        }

        public void TariffsInfo()
        {
            foreach(var item in tariffsCollections)
            {
                Console.WriteLine($"Маршрут {item.Value.Route} || Цена - {item.Value.Price}");
            }
        }
    }
}
