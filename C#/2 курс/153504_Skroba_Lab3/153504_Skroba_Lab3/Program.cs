using System.Collections.Generic;
using _153504_Skroba_Lab3.Entities;

internal class Program
{
    private static void Main(string[] args)
    {
        RailwayStation railwayStation = new RailwayStation();

        railwayStation.AddEvent += (string message) => { Console.WriteLine($"\tПроизошло дейтсвие:\n {message}\n"); };
        railwayStation.ErrorEvent += (string message) => { Console.WriteLine($"\tОшибка действия:\n {message}\n");  };

        railwayStation.AddPassenger("Ivanov", "MC2304242");
        railwayStation.AddPassenger("Bachurin", "MC8263549");
        railwayStation.AddPassenger("Gurinovich", "MC2242357");
        railwayStation.AddPassenger("Ivanova", "MC5263847");

        railwayStation.AddTariff("Minsk - Grodno", 16.52);
        railwayStation.AddTariff("Minsk - Molodecno", 2.24);
        railwayStation.AddTariff("Molodecno - Festivalnu", 0.52);

        railwayStation.RegistrationTariff("Ivanov", "Minsk - Grodno");
        railwayStation.RegistrationTariff("Bachurin", "Minsk - Grodno");
        railwayStation.RegistrationTariff("Ivanov", "Minsk - Molodecno");
        railwayStation.RegistrationTariff("Gurinovich", "Molodecno - Festivalnu");

        Console.WriteLine($"\nИнформация о пассажирах: ");
        railwayStation.PassangersInfo();

        railwayStation.TariffsByCost();

        Console.WriteLine($"\nИнформация о маршрутах: ");
        railwayStation.TariffsInfo();

        Console.WriteLine($"Общая стоимость всех купленных билетов: {railwayStation.TotalCostTariff()}");

        Console.WriteLine($"\nПассажир, заплативший максимальную сумму: {railwayStation.GetCostlyPassenger}");

    }
}