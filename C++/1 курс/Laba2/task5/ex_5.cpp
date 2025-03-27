// Лабораторная 2, задача 5. Выполнена: Скроба А.П.

/* Составить программу используя условный оператор if */

#include<iostream>
using namespace std;

int main() {

	double a, b, c, d, z;

	cout << "Enter four numbers - ";
	cin >> a >> b >> c >> d;

	if (c >= d && a < d) {
		cout << "Z = a + b / c = " << a + b / c << endl;

		return 0;
	} else if (c < d && a >= d) {
		cout << "Z = a - b / c = " << a + b / c << endl;

		return 0;
	}

	z = 0;
	cout << "Not a single condition came up: Z = " << z << endl;

	return 0;
}