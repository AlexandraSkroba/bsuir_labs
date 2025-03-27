using _153504_Skroba_Lab5.Domain;
using _Serializer;

internal class Program
{
    private static void Main(string[] args)
    {
        _Serializer.Serializer serializer = new();
        List<RailwayStation> station = new();

        station.Add(new RailwayStation("Минск - Молодечно", 23, false));
        station.Add(new RailwayStation("Брест - Гродно", 11, false));
        station.Add(new RailwayStation("Крыница - Фестивальный", 5, false));


        Console.WriteLine("\n\t|~~~~~SerializeJSON~~~~~|");
        serializer.SerializeJSON(station, "Json.json");

        var railwayStationJSON = serializer.DeSerializeJSON("Json.json");

        foreach (var item in railwayStationJSON)
        {
            Console.WriteLine(item.ShowStationInfo());

        }

        Console.WriteLine("\n\t|~~~~~SerializeByLINQ~~~~~|");
        serializer.SerializeByLINQ(station, "SerializeByLINQ.xml");

        var railwayStationLINQ = serializer.DeSerializeByLINQ("SerializeByLINQ.xml");
        foreach (var item in railwayStationLINQ)
        {
            Console.WriteLine(item.ShowStationInfo());
        }

        Console.WriteLine("\n\t|~~~~~SerializeXML~~~~~|");
        serializer.SerializeXML(station, "XML.xml");

        var railwayStationXML= serializer.DeSerializeXML("XML.xml");
        foreach (var item in railwayStationXML)
        {
            Console.WriteLine(item.ShowStationInfo());
        }
    }
}