using _153504_Skroba_Lab1.Collections;
using _153504_Skroba_Lab1.Entities;
using _153504_Skroba_Lab1.Interfaces;

internal class Program
{
    private static void Main(string[] args)
    {
        RailwayStation railwayStation = new RailwayStation();
        Journal journal = new Journal();

        //railwayStation.AddEvent += journal.AddEvents;
        railwayStation.BookEvent += (string message) => Console.WriteLine(message);

        Console.WriteLine("Данные о тарифах:\n");
        railwayStation.AddTariffs("Минск - Молодечно", 2.34);
        railwayStation.AddTariffs("Фестивальный - Минск", 2.26);
        railwayStation.AddTariffs("Минск - Орша", 12.22);
        railwayStation.AddTariffs("Гродно - Минск", 16.50);
        railwayStation.ShowAllTarriffs();
        Console.WriteLine("\n-----------------------------------------------------------\n");

        Console.WriteLine("Регестрируем пассажиров:");
        railwayStation.AddPassengers("Иванова Мария Ивановна", "01.01.2004", 'F', "Молодечно");
        railwayStation.AddPassengers("Иванов Иван Иванович", "02.12.2003", 'М', "Воложин");
        railwayStation.AddPassengers("Семченко Андрей Павлович", "21.10.1999", 'М', "Гродно");
        railwayStation.AddPassengers("Мартынова София Сергеевна", "17.08.2000", 'F', "Орша");
        railwayStation.ShowInfoPassengers();
        Console.WriteLine("\n-----------------------------------------------------------\n");

        Console.WriteLine("Покупаем билеты и рассчитываем сумму, выводим данные: ");
        railwayStation.AllTariffs("Мартынова София Сергеевна", "Фестивальный - Минск");
        railwayStation.AllTariffs("Мартынова София Сергеевна", "Минск - Орша");
        railwayStation.AllTariffs("Иванова Мария Ивановна", "Минск - Молодечно");
        railwayStation.AllTariffs("Иванов Иван Иванович", "Минск - Молодечно");
        railwayStation.AllTariffs("Мартынова София Сергеевна", "Гродно - Минск");
        railwayStation.AllTariffs("Семченко Андрей Павлович", "Гродно - Минск");
        railwayStation.AllTariffs("fgfsds", "Минск");
        railwayStation.ShowInfoPassengers();
        Console.WriteLine("\n-----------------------------------------------------------\n");

        Console.WriteLine("Выводим список всех пассажиров по определенному маршруту: ");
        railwayStation.ShowRoutPassengers("Минск - Молодечно");
        railwayStation.ShowRoutPassengers("Фестивальный - Минск");
        railwayStation.ShowRoutPassengers("Минск - Орша");
        railwayStation.ShowRoutPassengers("Гродно - Минск");
        Console.WriteLine("\n-----------------------------------------------------------\n");

        journal.ShowEvents();

        try
        {
            MyCustomCollection<int> collection = new();
            collection.Add(5);
            collection.Remove(6);
        }
        catch (MyException exception)
        {
            Console.WriteLine($"Во время выполнения было выброшено собственное исключение:\n {exception.Message}");
        }
        catch (Exception exception)
        {
            Console.WriteLine($"Во время выполнения было выброшено исключение:\n {exception.Message}");
        }
    }
}
