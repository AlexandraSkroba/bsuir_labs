// Лабораторная 3, задача 2. Выполнена: Скроба А.П.

#include<iostream>
#include<cmath>
#include<iomanip>
using namespace std;

int main() {

	double d, n = 1, sum = 0;

	do{
		d = pow((1 / 2.), n) + pow((1 / 3.), n);
		sum += d;
		++n;
	} while (d > 0.0001*1e-4);

	cout << fixed << setprecision(12) << sum << endl;

	return 0;
}