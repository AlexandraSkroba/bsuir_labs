// Лабораторная 6, задача 7. Выполнена: Скроба А.П.

/* В заданной строке S найти максимальную по длине подстроку, которая не является палиндромом */

#include <iostream>
#include<Windows.h>
#include "../static_libs/ststic_libs.h"

int main() {
    SetConsoleCP(1251); //чиним кириллицу
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "rus");
    std::string s;
    int count = 0;
    std::cout << "Программа в заданной строке S находит максимальную по длине подстроку, которая не является палиндромом.\nВведите строку: ";
    std::cin >> s;
    
    amount(s, count);

    std::cout << "\n";
    return 0;
}