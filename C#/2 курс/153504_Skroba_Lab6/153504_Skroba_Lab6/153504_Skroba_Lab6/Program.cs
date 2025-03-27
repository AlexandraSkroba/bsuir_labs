using _153504_Skroba_Lab6;
using System.Runtime.Loader;
using System.Reflection;

internal class Program
{
    private static void Main(string[] args)
    {
        List<Employee> employees = new List<Employee>()
        {
            new Employee("Pasha", 100, false),
            new Employee("Pasha", 100, false),
            new Employee("Pasha", 100, false),
            new Employee("Pasha", 100, false),
            new Employee("Pasha", 100, false),

        };

        Console.WriteLine("\tInitial data: ");
        foreach (var item in employees) { Console.WriteLine(item); }
        AssemblyLoadContext context = new AssemblyLoadContext("Lib.dll", true);

        Assembly assembly = context.LoadFromAssemblyPath("D:\\С#\\2 курс\\153504_Skroba_Lab6\\153504_Skroba_Lab6\\Lib\\bin\\Debug\\net6.0\\Lib.dll");
        var libClassType = assembly.GetType("Lib.FileService`1").MakeGenericType(typeof(Employee));

        if (libClassType is not null)
        {
            var libClass = Activator.CreateInstance(libClassType);

            var SaveData = libClassType.GetMethod("SaveData");
            var ReadFile = libClassType.GetMethod("ReadFile");

            SaveData?.Invoke(libClass, new object[] { employees, "Employees.json" });
            var newEmployees = ReadFile.Invoke(libClass, new object[] { "Employees.json" });

            Console.WriteLine("\n\tData after serialization: ");
            foreach (var item in newEmployees as List<Employee>)
            {
                Console.WriteLine(item);
            }
            context.Unload();
        }
    }
}