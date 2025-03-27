// Лабораторная 3, задача 1. Выполнена: Скроба А.П.

#include<iostream>
#include<cmath>
#include<iomanip>
using namespace std;

int main() {
	setlocale(LC_ALL, "Rus");

	double a, b, n = 0, k;
	int i = 1;

	cout << "Программа высчитывает сумму ряда (ai- bi)^2, \nгде i меняется от 1 до 30 и в зависимости от этого меняются переменные a и b." << endl;

	do {
		if (i % 2 == 0) { // i % 2 == 0 ? a = i / 2 && b = powl(i, 3) : a = i && b = i * i;
			a = i / 2;
			b = i * i * i;
		}
		else {
			a = i;
			b = i * i;
		}

		k = n;
		n = powl((a - b), 2); 
		n = n + k;

		i++;
	
	} while (i <= 30);

	cout << "\nCумма ряда = " << fixed << setprecision(0) << n << endl; 

	return 0;
}