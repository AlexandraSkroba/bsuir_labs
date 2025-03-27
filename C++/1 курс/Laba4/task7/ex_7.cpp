// Лабораторная 4, задача 7. Выполнена: Скроба А.П.

/* Дано натуральное число n. Требуется подсчитать количество цифр числа 
и определить, какая цифра стоит в разряде с номером i 
(разряды нумеруются с конца, т.е. разряд единиц имеет номер 0) */

#include<iostream>

int main() {

	int x, y, n = 1, i;
	double d;
	bool flag = false;

	do {
		std::cout << "Enter a natural number x: ";
		std::cin >> d;

		x = d;
		if (d - (int)d != 0) std::cout << "Please enter an integer!" << '\n' << '\n';

		if (std::cin.fail()) {
			std::cin.clear();
			std::cin.ignore();
			std::cout << "\nInvalid input.\n" << std::endl;
			flag = true;
		}

	} while (d - (int)d != 0 || flag);
	

	y = x;

	while ((y /= 10) > 0) n++;

	std::cout << "\nNumber of digits of a number - " << n << std::endl << '\n';

	do {
	std::cout << "Enter the digit of the number you want i: ";
	std::cin >> i;

	if (i > n - 1 || i < 0) std::cout << "There is no such discharge. Please enter a number from 0 to " << n - 1 << std::endl << '\n';
	} while (i > n - 1 || i < 0);

	long int* arr = new long int[n];

	for (int i = 0; i < n; ++i) {
		y = x % 10;
		arr[i] = y;
		x = (x - y) / 10;
	}

	std::cout << std::endl;

	std::cout << "Digit in place with number " << i << " - " << arr[i] << std::endl;

	delete[] arr;
	return 0;
}