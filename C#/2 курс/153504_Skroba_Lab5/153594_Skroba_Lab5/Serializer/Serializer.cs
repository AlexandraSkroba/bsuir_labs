using _153504_Skroba_Lab5.Domain;
using System.Text.Json;
using System.Xml.Serialization;
using System.Xml.Linq;

namespace _Serializer
{
    public class Serializer : ISerializer
    {
        public IEnumerable<RailwayStation>? DeSerializeByLINQ(string fileName)
        {
            XDocument xDocument = XDocument.Load(fileName);
            var luggages = xDocument.Element("Luggage");

            if (luggages is not null)
            {
                foreach (var luggage in luggages.Elements("Luggage"))
                {
                    var luggageCompartment = luggage.Element("Luggage_Compartment");

                    yield return new RailwayStation(Convert.ToString(luggage.Element("Route")?.Value),
                                                    Convert.ToInt32(luggageCompartment.Element("Capacity")?.Value),
                                                    Convert.ToBoolean(luggageCompartment.Element("IsFull")?.Value));
                }
            }
        }

        public IEnumerable<RailwayStation>? DeSerializeXML(string fileName)
        {
            XmlSerializer serializer = new XmlSerializer(typeof(List<RailwayStation>));
            using (FileStream fileStream = new FileStream(fileName, FileMode.OpenOrCreate))
            {
                return serializer.Deserialize(fileStream) as List<RailwayStation>;
            }
        }

        public IEnumerable<RailwayStation>? DeSerializeJSON(string fileName)
        {
            using (FileStream fileStream = new FileStream(fileName, FileMode.OpenOrCreate))
            {
                return JsonSerializer.Deserialize(fileStream, typeof(List<RailwayStation>)) as IEnumerable<RailwayStation>;
            }
        }

        public void SerializeByLINQ(IEnumerable<RailwayStation> value, string fileName)
        {
            XDocument document = new();
            XElement stations = new XElement("RailwayStations");

            foreach (var item in value)
            {
                XElement station = new XElement("RailwayStation");
                XElement route = new XElement("Route", item.Route);

                XElement luggage = new XElement("Luggage");

                XElement luggageCapacity = new XElement("Capacity", item.Luggage.LuggageCapacity);
                XElement luggageFull = new XElement("IsFull", item.Luggage.IsFull);

                luggage.Add(luggageCapacity);
                luggage.Add(luggageFull);

                station.Add(route);
                station.Add(luggage);

                stations.Add(station);
            }
            document.Add(stations);
            document.Save(fileName);
           
        }

        public void SerializeXML(IEnumerable<RailwayStation> value, string fileName)
        {
            XmlSerializer serializer = new XmlSerializer(typeof(List<RailwayStation>));
            using (FileStream fileStream = new FileStream(fileName, FileMode.OpenOrCreate))
            {
                serializer.Serialize(fileStream, value);
            }
        }

        public void SerializeJSON(IEnumerable<RailwayStation> value, string fileName)
        {
            using (FileStream fileStream = new FileStream(fileName, FileMode.Create))
            {
                JsonSerializer.Serialize(fileStream, value);
            }
        }
    }
}