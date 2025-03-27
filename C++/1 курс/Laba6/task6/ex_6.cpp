// Лабораторная 6, задача 6. Выполнена: Скроба А.П.
/* Напишите программу, которая выводит количество различных анаграмм, которые могут получиться aиз этого слова. */
#include<map>
#include<string>
#include<iostream>
#include<Windows.h>
#include "../static_libs/ststic_libs.h"
using namespace std;

int main() {
    SetConsoleCP(1251); //чиним кириллицу
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "rus");
    std::cout << "Программа выводит количество различных анаграмм, которые могут получиться из слова.\nВведите ваше слово: ";
    string word;
    getline(cin, word);
   

    std::cout << "\nВаше слово: " << word << std::endl;
    std::cout << "Колчисетво анаграмм - " << anagrams(word) << std::endl;

    return 0;
}