// Лабораторная 6, задача 1(вариант 10). Выполнена: Скроба А.П.
/* Дана строка символов, состоящая из цифр, разделенных пробелами. Вывести четные числа этой строки */
#include<iostream>
#include<stdio.h>
#include<string.h>
#include<Windows.h>

int main() {
    SetConsoleCP(1251); //чиним кириллицу
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "rus");
    char str[80];
    char* p = str;
    
    std::cout << "Программа выводит четные числа вашей строки.\nВведите строку: ";
    std::cin.getline(str, '.');
   //std::cout << str << std::endl;

    p = strtok(str, " ");
    std::cout << "Четные числа вашей строки: ";
    while (p) {
        if (p[strlen(p) - 1] % 2 == 0) {
            std::cout << p << " ";
        }
        p = strtok(NULL, " ");
    }
    std::cout << '\n';
    return 0;
}