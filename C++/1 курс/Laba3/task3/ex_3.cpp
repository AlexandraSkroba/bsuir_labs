// Лабораторная 3, задача 3. Выполнена: Скроба А.П.

#include<iostream>
#include<cmath>
#include<iomanip>
#define p 3.1415926535
using namespace std;

int main() {
	setlocale(LC_ALL, "Rus");

	double a = 0, b, m = 20, y, h = 10 * p, x;

	for (int i = 0; i != 21; ++i) {
		x = i * p / 40;
		y = sin(x) - cos(x);
		cout << "y" << i << " = " << fixed << setprecision(0) << y << endl;
	}

	return 0;
}