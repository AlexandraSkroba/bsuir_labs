// Лабораторная 7, задача 1(вариант 10). Выполнена: Скроба А.П.

/* из девятичной в семнадцатеричную (с массивом) */

#include<iostream>

int input_num() {
    while (true) {
        int value;

        std::cin >> value;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(32767, '\n');
            std::cout << "Неккоректный ввод\nВведите число в девятичной системе счисления(цифры от 0 до 9): ";
        }
        else {
            std::cin.ignore(32767, '\n');
            return value;
        }
    }
}

int main() {
	setlocale(LC_ALL, "rus");
	std::cout << "Программа осуществляет перевод чисел из девятичной в семнадцатеричную систему счисления (с массивом).";
    std::cout << "\nВведите число в девятичной системе счисления: ";
    int num = input_num(); //число в девятичной сс
    int n = num;
    int count = 0, add; //кол-во цифр в числе

        int count_1 = 0, ten = 0;;
        do {
            int d = num % 10;
            num /= 10;

            ten += d * powl(9, count_1);

            count_1++;
            count--;
        } while (num);
        std::cout << "Число в десятичной сс: " << ten << std::endl;

        int k1 = 10, k2 = 11, t = 8, z, i, ss = 17;
        char ms[20]; 
        z = ten; 
        ten -= z;
        while (z >= ss) 
        {
            i = z % ss; 
            z /= ss; 
            ms[k1--] = i > 9 ? i - 10 + 'A' : i + '0';
        } 
        ms[k1--] = z > 9 ? z - 10 + 'A' : z + '0';
        ms[k1] = ' ';
        ms[k2++] = '.'; 
        while (ten != 0 && k2 - 11 <= t) {
            ten *= ss;
            i = ten; 
            ms[k2++] = i > 9 ? i - 10 + 'A' : i + '0'; 
            ten -= i;
        }
        std::cout << "\nВаше число:";
        for (i = k1; i < k2; i++)
            std::cout << ms[i]; 


    std::cout << std::endl;

	return 0;
}