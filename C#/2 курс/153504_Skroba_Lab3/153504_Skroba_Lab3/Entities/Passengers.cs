using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _153504_Skroba_Lab3.Entities
{
    internal class Passengers
    {
        public string FullName { get; set; }
        public string PassportNo { get; set; }
        public Passengers(string fullName, string passportNo) => (FullName, PassportNo) = (fullName, passportNo);
        private List<Tariffs> tariffs = new();
        private double totalCost = 0;
        public double TotalCost
        {
            get
            {
                totalCost = 0;

                foreach(var tarriff in tariffs)
                {
                    totalCost += tarriff.Price;
                }
                return totalCost;
            }

            private set
            {
                totalCost = value;
            }
        }

        public List<Tariffs> GetTariffs()
        {
            return tariffs;
        }

        public void AddTariffs(Tariffs tariff)
        {
            tariffs.Add(tariff);
        }

        public void RemoveTariff(Tariffs tariff)
        {
            tariffs.Remove(tariff);
        }
    }
}
