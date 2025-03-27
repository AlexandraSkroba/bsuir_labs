// Лабораторная 1, задача 8. Выполнена: Скроба А.П.

/* На вход даны а1 и a100, первый и сотый член арифметической прогрессии. Необходимо вычислить:
1. Разность арифметической прогрессии;
2. Сумму первых n+10 членов арифметической прогрессии, где n - ваш номер в журнале */

#include<iostream>
using namespace std;

int main() {

	double a1, a100, a35, d, s;

	cout << "Enter the first term of the arithmetic progression - ";
	cin >> a1;

	cout << "Enter the hundredth term of the arithmetic progression - ";
	cin >> a100;

	d = (a100 - a1) / 99;
	cout << "\nDifference of arithmetic progression = " << d << endl;

	a35 = a1 + d * 34;
	s = (a1 + a35) * 35 / 2;
	cout << "The sum of the progression = " << s;

	return 0;
}