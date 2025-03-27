#include <iostream>
#include <cmath>
#include <cstdlib>

int input()
{
    setlocale(LC_ALL, "rus");
    using namespace std;

    unsigned int x;
    while (true)
    {
        cin >> x;

        if (cin.fail() || cin.peek() != '\n')
        {
            cout << "\nПроизошла ошибка, попробуйте ещё раз)\n";
            cin.clear();
            cin.ignore(30000, '\n');
        }
        else
        {
            return x;
        }
    }
}

using namespace std;

int main()
{
    setlocale(LC_ALL, "rus");

    unsigned long long int i, a, n;
    long double value = 0.0;

    cout << "Введите количество членов ряда n: ";

    n = input();
    if (n == 0)
    {
        main();
    }

    for (i = 0; i <= (n - 1); ++i)
    {
        a = srand(100);
        value += pow(2, i) * pow(-1, i) * a;
    }

    cout << "\nЗначение функции = " << value << endl;

    system("pause");
    return 0;
}