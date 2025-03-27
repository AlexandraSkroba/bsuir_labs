using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _153504_Skroba_Lab5.Domain
{
    [Serializable]
    public class LuggageCompartment
    {
        public LuggageCompartment() { }
        public LuggageCompartment(int luggageCapacity, bool isFull = false) => (LuggageCapacity, IsFull) = (luggageCapacity, isFull);
        public int LuggageCapacity { get; set; }
        public bool IsFull { get; set; } = false;
    }
}
