// Лабораторная 7, задача 5. Выполнена: Скроба А.П.

/* Перевести число из арабской системы записи чисел в римскую. */

#include<iostream>
#include<string>
#include "../static_libs/static_libs.h"

int inputInt(int minValue, int maxValue) {

	double x;
	while (true) {
		std::cin >> x;
		if (!std::cin.fail() && x <maxValue && x > minValue)
			return (int)x;
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << "Enter corect value" << std::endl;
	}
}

int main() {
	setlocale(LC_ALL, "rus");
	std::cout << "Программа переводит число из арабской системы записи чисел в римскую.\nВведите число: ";
	std::cout << "Ваше число в римской сс: " << convertToRomanian(inputInt(0, 4000)) << std::endl;
}