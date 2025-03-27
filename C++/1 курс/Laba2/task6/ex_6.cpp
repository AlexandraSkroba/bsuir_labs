// Лабораторная 2, задача 6. Выполнена: Скроба А.П.

/* Составить программу используя переключатель switch */

#include<iostream>
#include<cmath>
using namespace std;

int main() {

	double a, b, c, y;
	int n;

	cout << "Enter number N - ";
	cin >> n;

	cout << "\nEnter three numbers - ";
	cin >> a >> b >> c; // -13.8 8.9 25

	switch (n)
	{
	case 2:
		cout << "\ny = b * c - a^2 = " << b * c - a * a << endl;
		break;
	case 56:
		cout << "\ny = b * c = " << b * c << endl;
		break;
	case 7:
		cout << "\ny = a^2 + c = " << a * a + c << endl;
		break;
	case 3:
		cout << "\ny = a - b * c = " << a - b * c << endl;
		break;
		return 0;
	default:
		y = powl((a+b), 3);
		cout << "\ny = " << y << endl;
		break;
	}

	return 0;
}