#include <iostream>
#include <string>
#include <windows.h>
#include <functional>
#include <regex>
#include <Windows.h>

using namespace std;

string Solve(long double a, long double b, long double c)
{
    const long double LD_4 = 4.0L;
    if (a == 0) {
        return "��������� �� �������� ����������";
    }
    long double D;
    __asm
    {
        FLD b
        FLD b
        FMUL
        FLD LD_4
        FLD a
        FLD c
        FMUL
        FMUL
        FSUB
        FSTP D
    }
    cout << "\n������������: " << D << '\n';
    if (!isfinite(D)) {
        return "������������ �� �������� �������� ������";
    }
    if (D < 0.0L) {
        return "��� ������������ ������";
    }
    if (D == 0.0L) {
        long double x;
        __asm {
            FLD b
            FCHS
            FLD a
            FLD a
            FADD
            FDIV
            FSTP x
        }
        return "x = " + to_string(x);
    }
    if (D > 0.0L) {
        long double x1, x2;
        __asm {
            FLD b
            FCHS
            FLD D
            FSQRT

            FSUB

            FLD a
            FLD a
            FADD
            FDIV

            FSTP x1
        }
        __asm
        {
            FLD b
            FCHS
            FLD D
            FSQRT

            FADD

            FLD a
            FLD a
            FADD
            FDIV

            FSTP x2
        }
        return "x1 = " + to_string(x1) + ", " +
            "x2 = " + to_string(x2);
    }
    return "���-�� ����� �� ���";
}


int main() {

    SetConsoleCP(1251);

    SetConsoleOutputCP(1251);

    long double a, b, c;
    cout << "������� ����������� a: ";
    cin >> a;
    cout << "������� ����������� b: ";
    cin >> b;
    cout << "������� ����������� c: ";
    cin >> c;

    cout << '\n';

    if (a != 1)
        cout << ((a == -1) ? '-' : a);

    cout << "x^2 " << ((b < 0) ? '-' : '+') << ' ' << abs(b) << "x "
        << ((c < 0) ? '-' : '+') << ' ' << abs(c) << " = 0\n";

    cout << '\n' << Solve(a, b, c) << '\n';

    return 0;
}
