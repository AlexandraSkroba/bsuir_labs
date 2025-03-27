namespace LR2_task1
{
    static class Program
    {
        static void Main()
        {
            Console.WriteLine("The program checks if the given number is odd.");

            while (true)
            {
                Console.Write("Enter the number: ");
                int num;

                while (!int.TryParse(Console.ReadLine(), out num))
                {
                    Console.Write("\nInput Error! Enter an integer: ");
                }

                if (num % 2 == 0)
                {
                    Console.WriteLine("Number is even");
                }
                else
                {
                    Console.WriteLine("Number is odd");
                }
                Console.WriteLine("\nDo you want to continue typing?(1 - Yes, 0 - No)");

                int answer;
                while (!int.TryParse(Console.ReadLine(), out answer) || answer > 1 || answer < 0)
                {
                    Console.Write("\nInput Error! Enter an 1 to contine or 0 to break: ");
                }

                if (answer == 0)
                {
                    break;
                }
            }
        }
    }
}
