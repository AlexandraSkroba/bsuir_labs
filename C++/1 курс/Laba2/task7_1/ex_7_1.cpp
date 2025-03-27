// Лабораторная 2, задача 7. Выполнена: Скроба А.П.

/* Составить программу для решения уравнений трёх видов:
7.1 ax^4 + bx^2 + c = 0; */

#include<iostream>
#include<cmath>

using namespace std;

int main() {

	double a, b, c, d, t1, t2, x;

	cout << "Enter three numbers, please - ";
	cin >> a >> b >> c;

	if (a == 0 && b == 0 && c == 0) {
		cout << "\nx = R" << endl;
		return 0;
	}
	else if (a == 0 && b != 0 && c == 0 || a != 0 && b == 0 && c == 0) {
		cout << "\nx = 0" << endl;

		return 0;
	}
	else if (a == 0 && b == 0 && c != 0 || a == 0 && b > 0 && c > 0 || a == 0 && b < 0 && c < 0 || a > 0 && b == 0 && c > 0 || a < 0 && b == 0 && c < 0) {
		cout << "\nNo solution" << endl;

		return 0;
	}

	if (powl(b, 2) - 4 * a * c < 0) {
		cout << "\nNo solution" << endl;

		return 0;
	}
	else if (powl(b, 2) - 4 * a * c == 0) {
		t1 = -b / 2 * a;

		if (t1 > 0) {
			x = sqrt(t1);

			cout << "\nx1 = " << t1 << ", x2 = " << -t1 << endl;
			return 0;
		}
		else if (t1 < 0)
		{
			cout << "\nNo solution" << endl;
			return 0;
		}
	}
	else if (powl(b, 2) - 4 * a * c > 0) {
		d = powl(b, 2) - 4 * a * c;

		t1 = (-b + sqrt(d)) / (2 * a);
		t2 = (-b - sqrt(d)) / (2 * a);

		if (t1 < 0) {
			x = sqrt(t2);

			cout << "\nx1 = " << x << ", x2 = " << -x << endl;
			return 0;
		}
		else if (t2 < 0) {
			x = sqrt(t1);

			cout << "\nx1 = " << x << ", x2 = " << -x << endl;
			return 0;
		}
		x = sqrt(t1);

		if (x == 0) {
			cout << ", x1 = 0" << endl;
			return 0;
		}

		cout << "\nx1 = " << x << ", x2 = " << -x;

		x = sqrt(t2);

		if (x == 0) {
			cout << ", x3 = 0" << endl;
			return 0;
		}

		cout << ", x3 = " << x << ", x4 = " << -x << endl;

		return 0;
	}
}