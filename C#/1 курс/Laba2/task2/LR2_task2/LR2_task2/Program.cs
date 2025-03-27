namespace LR2_task2
{
    static class Program
    {
        static void Main()
        {
            Console.WriteLine("Программа выдает одно из сообщений (Да, Нет, На границе) в зависимости от того, лежит ли точка внутри заштрихованной области, вне заштрихованной области или на ее границе.");
            while (true)
            {
                Console.WriteLine("Введите координаты точки (x, y): ");
                double x;
                while (!double.TryParse(Console.ReadLine(), out x))
                {
                    Console.WriteLine("Некорректный ввод!Введите число: ");
                }

                double y;
                while (!double.TryParse(Console.ReadLine(), out y))
                {
                    Console.WriteLine("Некорректный ввод!Введите число: ");
                }

                double R = Math.Sqrt(Math.Pow(x, 2) + Math.Pow(y, 2));

                //на границе
                if (x == 0)
                {
                    if ((y <= 8 && y >= 3) || (y <= -3 && y >= -8))
                    {
                        Console.WriteLine("На границе!");
                    }
                }
                else if (x < 0)
                {
                    if (R == 3 || R == 8)
                    {
                        Console.WriteLine("На границе!");
                    }
                }

                //нет
                if (x >= 0 || (y < -8 && y > -3) || (y < 3 && y > 8))
                {
                    Console.WriteLine("Нет!");
                }
                else if (x < 0)
                {
                    if (R < 3 || R > 8)
                    {
                        Console.WriteLine("Нет!");
                    }
                }

                //да
                if (x < 0)
                {
                    if (R > 3 && R < 8)
                    {
                        Console.WriteLine("Да");
                    }
                }

                Console.WriteLine("\nХотите продолжить ввод? (1 - Да, 0 - Нет)");
                int answer;
                while (!int.TryParse(Console.ReadLine(), out answer) || answer > 1 || answer < 0)
                {
                    Console.WriteLine("Некорректный ввод!\nВведите 1 - Если хотите продолжить\n\t0 - Если хотите завершить программу ");
                }

                if (answer == 0)
                {
                    break;
                }
            }  
        }
    }
}
