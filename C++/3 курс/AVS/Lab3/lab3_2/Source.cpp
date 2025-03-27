#include <iostream>
#include <iomanip>
#include <windows.h>
#include <math.h>
#include <string>
#include <regex>
#include <functional>

using namespace std;

void Solve(long double a, long double b, long double h, long double eps)
{
    cout << '\n';

    cout << setprecision(3) << scientific << showpos <<
        "   eps = " << eps << "        " << "\n\n";
    cout << "       x           S(x)         Y(x)      abs(S - Y)    n    " << "\n\n";

    for (long double x = a; x < b + h / 2; x += h) {

        int n = 0;

        long double Y, S, f, p, intp, fracp, trash;

        //Y = pow(exp, cos(x)) * cos(sin(x));
        __asm
        {
            FLD x
            FCOS
            FLDL2E // загрузку значения логарифма числа 2 по основанию e 
            FMUL
            FSTP p // выгружает значение из вершины стека FPU и сохраняет его в памяти
        }
        __asm
        {
            FLD p 
            FLD1 // загружает значение 1 в вершину стека FPU.
            FSCALE // выполняет масштабирование числа в вершине стека FPU по основанию 2
            FSTP intp
            FSTP trash
        }
        __asm
        {
            FLD1
            FLD p
            FPREM
            F2XM1
            FADD
            FSTP fracp
        }
        __asm
        {
            FLD intp
            FLD fracp
            FMUL

            FLD x
            FSIN
            FCOS
            FMUL
            FSTP Y
        }
        //S = 1.0, f = 1.0;
        __asm
        {
            FLD1
            FSTP S

            FLD1
            FSTP f
        }
        while (abs(S - Y) > eps) {
            n++;
            //f *= n;
            __asm
            {
                FLD f
                FILD n
                FMUL
                FSTP f
            }
            //S += cos(n * x) / f;
            __asm
            {
                FLD S
                FILD n
                FLD x
                FMUL
                FCOS
                FLD f
                FDIV
                FADD
                FSTP S
            }

        }
        cout << setprecision(3) << scientific << showpos <<
            "   " << x << "   " << S << "   " << Y << "   " << abs(S - Y) << "   " <<
            noshowpos << right << setw(2) << n << "   \n";
    }
    //cout << " ---------------------------------------------------------- \n";
}

template<typename ReturnValue>
ReturnValue CorrectInput(const string& variable_name, const std::regex& pattern,
    std::function<ReturnValue(string& input)> converter) {

    string value;

    do {
        cout << "Enter " << variable_name << ": ";
        cin >> value;
    } while (!regex_match(value, pattern));

    return converter(value);

}

int main() {

    SetConsoleCP(1251);

    SetConsoleOutputCP(1251);


    float a = CorrectInput<float>(std::string("the lower bound (à)"),
        std::regex("-?[0-9]+,?[0-9]*"),
        [](std::string& s) {return atof(s.c_str()); });

    float b = CorrectInput<float>(std::string("the upper bound (b)"),
        std::regex("-?[0-9]+,?[0-9]*"),
        [](std::string& s) {return atof(s.c_str()); });

    float h = CorrectInput<float>(std::string("step (h)"),
        std::regex("-?[0-9]+,?[0-9]*"),
        [](std::string& s) {return atof(s.c_str()); });

    float eps = CorrectInput<long double>(std::string("error rate (eps)"),
        std::regex("-?[0-9]+\.?[0-9]*"),
        [](std::string& s) {return atof(s.c_str()); });

    Solve(a, b, h, eps);

    return 0;
}
