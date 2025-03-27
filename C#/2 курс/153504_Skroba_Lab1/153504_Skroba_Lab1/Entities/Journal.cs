using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using _153504_Skroba_Lab1.Collections;

namespace _153504_Skroba_Lab1.Entities
{
    internal class Journal
    {
        private MyCustomCollection<string> events = new MyCustomCollection<string>();

        public void AddEvents(string message)
        {
            events.Add(message);
        }

        public void ShowEvents()
        {
            foreach(var item in events)
            {
                Console.WriteLine(item);
            }
        }
    }
}
