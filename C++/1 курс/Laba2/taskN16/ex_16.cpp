// Лабораторная 2, задача 16. Выполнена: Скроба А.П.

/* Введены два числа. Выведите их НОД и НОК */

#include<iostream>
using namespace std;

int main() {
	setlocale(LC_ALL, "Rus");

	int x, y, x1, y1;

	do {
		cout << "Введите два числа - ";
		cin >> x >> y;
		if (x == 0 || y == 0) cout << "Enter a normal number, please!\n";
	} while (x == 0 || y == 0);

	x1 = x;
	y1 = y;

	if (x == y) {
		cout << "\nНОК чисел (" << x << ", " << y << ") = " << x;
		cout << "\nНОД чисел (" << x << ", " << y << ") = " << x << endl;
		return 0;
	}

	cout << "\nНОД чисел (" << x << ", " << y << ") = ";

	while (x != y) {
		if (x > y) {
			x -= y;
		}
		else {
			y -= x;
		}
	} cout << x;

	cout << "\nНОК чисел (" << x1 << ", " << y1 << ") = ";
	cout << x1 * y1 / x << endl;

	return 0;
}