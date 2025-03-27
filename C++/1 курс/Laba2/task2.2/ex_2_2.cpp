// Лабораторная 2, задача 2. Выполнена: Скроба А.П.

/* Наибольшее из трёх различных значений переменных вещественного типа А, В и С уменьшите на K.
K вводится с клавиатуры */

#include<iostream>
using namespace std;

int main() {

	double a, b, c, k;

	do {
		cout << "Enter three numbers - ";
		cin >> a >> b >> c;

		if (a == b || b == c || c == a) cout << "\nEnter three differents numbers!\n" << endl;
	} while (a == b || b == c || c == a);

	cout << "Enter number K - ";
	cin >> k;

	if (a < c && b < c) {
		cout << c << " - is the largest number! | " << "c - k = " << c - k << endl;
	}
	else if (a < b && c < b) {
		cout << b << " - is the largest number! | " << "b - k = " << b - k << endl;
	}
	else if (c < a && b < a) {
		cout << a << " - is the largest number! | " << "a - k = " << a - k << endl;
	} 

	return 0;
}