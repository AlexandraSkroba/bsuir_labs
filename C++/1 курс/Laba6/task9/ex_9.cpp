// Лабораторная 6, задача 9. Выполнена: Скроба А.П.
/* В заданной строке, состоящей из букв, цифр и прочих символов, найдите сумму всех чисел. */

#include <iostream>
#include <string>
#include <cctype>
#include <cmath>
#include <Windows.h>
#include "../static_libs/ststic_libs.h"

using namespace std;

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "rus");

    long double buff, sum = 0;
    int fraction, ex;
    bool minus, exMinus;

   string input;

   cout << "Введите строку: ";
   getline(cin, input);

   cout << "\n\nСумма: " << Sum(input) << endl;

    return 0;
}