// Лабораторная 7, задача 7. Выполнена: Скроба А.П.

/* Необходимо разработать программу, которая проверяет, 
делится ли введенное пользователем число на заданное простое. 
Программа не должна содержать операций умножения, деления, вычитания (в том числе взятия остатка от деления) */

#include<iostream>
#include<string>
#include<iomanip>

bool multiplieByThree(int number) {
	int num = 0;
	for (int i = 0; num < number; i++)
	{
		num = (i << 1) + i;
	}
	if (num == number)
		return true;
	return false;
}

int inputInt(int minValue, int maxValue) {

	double x;
	while (true)
	{
		std::cin >> x;
		if (!std::cin.fail() && x <maxValue && x > minValue)
			return (int)x;
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << "Enter corect value" << std::endl;
	}
}

bool multiplieByFourtySeven(int number) {
	int num = 0;
	for (int i = 0; num < number; i++)
	{
		num = (i << 5) + (i << 3) + (i << 2) + (i << 1) + i;
	}
	if (num == number)
		return true;
	return false;
}
bool multiplieByBigValue(int number) {
	int num = 0;
	for (int i = 0; num < number; i++)
	{
		num = (i << 7) + (i << 6) + (i << 2) + i;
	}
	if (num == number)
		return true;
	return false;
}

int main() {
	setlocale(LC_ALL, "rus");

	std::cout << "Программа проверяет делится ли введенное пользователем число на 3, 47, 197.\nВведите число: ";
	int number = inputInt(0, INT_MAX);

	std::cout << std::boolalpha << "\nДеление на 3 - " << multiplieByThree(number) << "\nДеление на 47 - " << multiplieByFourtySeven(number) << "\nДеление на 197 - " << multiplieByBigValue(number) << std::endl;
	return 0;
}