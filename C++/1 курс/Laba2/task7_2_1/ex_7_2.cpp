// Лабораторная 2, задача 7. Выполнена: Скроба А.П.

/* Составить программу для решения уравнений трёх видов:
7.2 ax^4 + bx^3 + cx^2 + bx + a = 0 (уравнение четвертой степени)*/

#include<iostream>
#include<cmath>

using namespace std;

int main() {
	
	double a, b, c, d, x, y1, y2;

	cout << "Enter three numbers, please - ";
	cin >> a >> b >> c;

	if (a == 0 && b == 0 && c == 0) {
		cout << "\nNo solution" << endl;

		return 0;
	}

	if (b * b - 4 * a * (c - 2 * a) > 0) {
		d = b * b - 4 * a * (c - 2 * a);
		
		y1 = (-b + sqrt(d)) / (2 * a);
		y2 = (-b - sqrt(d)) / (2 * a);

		if (y1 * y1 - 4 > 0) {

			d = y1 * y1 - 4;

			x = (y1 + sqrt(d)) / 2;
			cout << "\nx1 = " << x;

			x = (y1 - sqrt(d)) / 2;
			cout << ", x2 = " << x;
		}
		else if (y1 * y1 - 4 == 0) {
			x = y1 / 2;
			cout << "x1 = " << x << endl;
		}

		if (y2 * y2 - 4 > 0) {

			d = y2 * y2 - 4;

			x = (y2 + sqrt(d)) / 2;
			cout << " x3 = " << x;

			x = (y2 - sqrt(d)) / 2;
			cout << ", x4 = " << x;
		}
		else if (y2 * y2 - 4 == 0) {
			x = y2 / 2;
			cout << "x2 = " << x << endl;
		}

		return 0;
	}
	else if (b * b - 4 * a * (c - 2 * a) < 0) {
		cout << "\nNo solution" << endl;

		return 0;
	}
	else if (b * b - 4 * a * (c - 2 * a) == 0) {
		d = b * b - 4 * a * (c - 2 * a);

		y1 = -b / (2 * a);
		if (y1 * y1 - 4 > 0) {
			d = y1 * y1 - 4;

			x = (y1 + sqrt(d)) / 2;
			cout << "\nx1 = " << x;

			x = (y1 - sqrt(d)) / 2;
			cout << ", x2 = " << x;

			return 0;
		}
		else if (y1 * y1 - 4 == 0) {
			d = y1 * y1 - 4;

			x = y1 / 2;
			cout << "\nx = " << x << endl;

			return 0;
		}
		else if (y1 * y1 < 0) {
			cout << "\nNo solution" << endl;

			return 0;
		}
	}

	return 0;
}