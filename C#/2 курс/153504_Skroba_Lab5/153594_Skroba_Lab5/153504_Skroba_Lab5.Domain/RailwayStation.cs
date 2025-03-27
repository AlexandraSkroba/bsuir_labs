namespace _153504_Skroba_Lab5.Domain
{
    [Serializable] //атрибут, чтобы объект данного класса можно было сериализовать
    public class RailwayStation
    {
        public RailwayStation() { }
        public RailwayStation(string route, int capacity, bool isFull = false)
        {
            this.route = route;
            Luggage = new LuggageCompartment(capacity, isFull);
        }
        public LuggageCompartment luggage = new();
        public LuggageCompartment Luggage {
            get
            {
                return luggage;
            }
            set
            {
                luggage = value;
            }
        }

        public string route = " ";
        public string Route
        {
            get
            {
                return route;
            }
            set
            {
                route = value;
            }
        }
        public string ShowStationInfo()
        {
            return "\n Маршрут: " + route.ToString() +
                "\n Размер: " + Luggage.LuggageCapacity.ToString() +
                "\n Заполнено ли багажное отделение: " + Luggage.IsFull.ToString();
        }
        
        public void FullLuggage() => Luggage.IsFull = true;
        public void NotFullLuggage() => Luggage.IsFull = false;
    }
}