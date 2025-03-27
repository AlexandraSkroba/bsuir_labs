using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace LR8
{
    public interface ITariff
    {
        public void ShowTariff();
        public int Price();
    }
    public class Tariff : ITariff
    {
        private string type_of_tariff, price;

        public Tariff(string type_of_tariff_, string price_)
        {
            type_of_tariff = type_of_tariff_;
            price = price_;
        }

        public void ShowTariff()
        {
            Console.WriteLine($"{type_of_tariff} - {price}$");
        }

        int ITariff.Price()
        {
            return Int32.Parse(price);
        }
    }
    public class SpecialTariff : ITariff
    {
        private string type_of_tariff, price, discount;

        public SpecialTariff(string type_of_tariff_, string price_, string discount_)
        {
            type_of_tariff = type_of_tariff_;
            price = price_;
            discount = discount_;
        }
        void ITariff.ShowTariff()
        {
            Console.WriteLine($"{type_of_tariff} - {price}$ - {discount}%");
        }
        int ITariff.Price()
        {
            return Int32.Parse(price) - (Int32.Parse(price) * Int32.Parse(discount) / 100);
        }
    }
    public class ATS
    {
        private static ATS ATS_;

        private string name = "";

        List<ITariff> Tariffs = new List<ITariff>();

        private ITariff? tariff;
        private ITariff? MaxPrice;

        ATS(string name_)
        {
            name = name_; 
        }

        public static ATS CreateATS(string name_)
        {
            if (ATS_ == null)
                ATS_ = new ATS(name_);

            return ATS_;
        }

        public string MaxTariff()
        {
            int max = 0;

            foreach (var current in Tariffs)
            {
                MaxPrice = current;
                if (max < MaxPrice.Price())
                    max = MaxPrice.Price();
            }
            return $"Максимальный тариф - {max}";
        }

        public void Add(Tariff tariff)
        {
            Tariffs.Add(tariff);
        }

        public void Add(SpecialTariff tariff)
        {
            Tariffs.Add(tariff);
        }

        public void Show()
        {
            foreach (var cur in Tariffs)
            {
                tariff = cur;
                tariff.ShowTariff();
            }
        }
    }
}
