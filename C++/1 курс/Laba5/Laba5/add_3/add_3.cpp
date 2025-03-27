// Лабораторная 5, задача дополнительная 3 :/. Выполнена: Скроба А.П.

/* Пусть f(n) - наибольший нечетный делитель натурального числа n. 
По заданному натуральному n необходимо вычислить значение суммы f(1) + f(2) + ... + f(n) */

#include<iostream>
#include "../../Libs for add/StaticLib_add1/StaticLib_add3/StaticLib_add3.h"

/* проверка на ввод */
long input() {
    while (true) {
        long double value;

        std::cin >> value;

        if (std::cin.fail() || value < 1 || value - (long int)value != 0) {
            std::cin.clear();
            std::cin.ignore(32767, '\n');
            std::cout << "\nОшибка\nВведите целое натуральное число - ";
        }
        else {
            std::cin.ignore(32767, '\n');
            return value;
        }
    }
}

long main() {
    setlocale(LC_ALL, "rus");

	long long n;
	std::cout << "Программа нахрдит значение суммы f(1) + f(2) + ... + f(n) по заданному натуральному n.";
	std::cout << "\nВведите число n - ";
    n = input();

    std::cout << "\nf(1) + f(2) + ... + f(" << n << ") = " << function(n) << std::endl;

	return 0;
}