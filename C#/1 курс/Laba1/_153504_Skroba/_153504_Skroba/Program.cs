namespace _153504_Skroba 
{
    static class Program
    {
        static void Main()
        {
            Console.Write("Enter the first number: ");
            var firstNumber = Convert.ToInt32(Console.ReadLine());
            Console.Write("Enter the second number: ");
            var secondNumber = Convert.ToInt32(Console.ReadLine());
            var result = (double) firstNumber / secondNumber;
            Console.Write("Result of division: ");
            Console.Write(result);
        }
    }
}