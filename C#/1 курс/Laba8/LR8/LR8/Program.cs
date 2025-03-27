using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace LR8
{
    public class Program
    {
        public static void Main(string[] args)
        {
            ATS BELARUS = ATS.CreateATS("name");

            Tariff tariff = new Tariff("Usual", "250");

            SpecialTariff spc_tar = new SpecialTariff("Preferential", "250", "30");

            BELARUS.Add(tariff);
            BELARUS.Add(spc_tar);

            BELARUS.Show();
            Console.WriteLine();
            BELARUS.Show();

            BELARUS.MaxTariff();
        }
    }
}
