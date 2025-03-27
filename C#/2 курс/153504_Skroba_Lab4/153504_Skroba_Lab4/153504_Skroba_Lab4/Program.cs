using _153504_Skroba_Lab4.Entities;
using _153504_Skroba_Lab4.Service;
using System.Collections.ObjectModel;

internal class Program
{
    private static void Main(string[] args)
    {
        FileService fileService = new FileService();
        Collection<Computer> computers = new Collection<Computer>();

        computers.Add(new Computer("MacBook Air", 2017, 13.3, false));
        computers.Add(new Computer("MacBook Pro", 2021, 14.2, true));
        computers.Add(new Computer("iMac       ", 2019, 21.5, false));
        computers.Add(new Computer("MacBook Pro", 2020, 13.3, true));
        computers.Add(new Computer("MacBook Pro", 2016, 13.3, false));

        fileService.SaveData(computers, "Computers.bin");

        try
        {
            File.Move("Computers.bin", "NewComputers.bin");
        }
        catch (IOException)
        {
            File.Delete("NewComputers.bin");
            File.Move("Computers.bin", "NewComputers.bin");
        }

        List<Computer> NewComputers = new List<Computer>(fileService.ReadFile("NewComputers.bin"));

        Console.WriteLine("\n\tВывод на экран коллекции: ");
        foreach (var item in NewComputers)
        {
            Console.WriteLine($"{item.Name}  || {item.ReleaseDate} || Display - {item.Display} || TouchId - {item.TouchID}");
        }

        //Сортировка коллекции по полю Name
        var myCustomComparer = new MyCustomComparer();

        var sortNewComputers = NewComputers.OrderBy(item => item,
            myCustomComparer);

        Console.WriteLine("\n\tВывод на экран отсортированной по имени коллекции");
        foreach (var item in sortNewComputers)
        {
            Console.WriteLine($"{item.Name}  || {item.ReleaseDate} || Display - {item.Display} || TouchId - {item.TouchID}");
        }

        //Сортировка коллекции по полю Display
        sortNewComputers = NewComputers.OrderBy((item) => { return item.Display; });

        Console.WriteLine("\n\tВывод на экран отсортированной по размеру дисплея коллекции");
        foreach (var item in sortNewComputers)
        {
            Console.WriteLine($"{item.Name}  || {item.ReleaseDate} || Display - {item.Display} || TouchId - {item.TouchID}");
        }
    }
}