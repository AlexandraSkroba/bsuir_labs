using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _153504_Skroba_Lab5.Domain
{
    public interface ISerializer
    {
        IEnumerable<RailwayStation> DeSerializeByLINQ(string fileName);
        IEnumerable<RailwayStation> DeSerializeXML(string fileName);
        IEnumerable<RailwayStation> DeSerializeJSON(string fileName);
        void SerializeByLINQ(IEnumerable<RailwayStation> value, string fileName);
        void SerializeXML(IEnumerable<RailwayStation> value, string fileName);
        void SerializeJSON(IEnumerable<RailwayStation> value, string fileName);
    }
}
