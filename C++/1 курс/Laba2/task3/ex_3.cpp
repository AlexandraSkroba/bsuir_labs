// Лабораторная 2, задача 3. Выполнена: Скроба А.П.

/* Написать программу нахождения максимального из двух
вещественных чисел X и Y с использованием тернарной операции. Написать
два варианта программы. С использованием переменной логического типа для
определения условия и без неё. */

#include<iostream>
using namespace std;

int main() {

	double x, y;

	cout << "Enter two numbers - ";
	cin >> x >> y;

	bool k;
	k = x > y ? 1 : 0;

	if (k) {
		cout << "\nThe biggest one = " << x << endl;
	}
	else cout << "\nThe biggest one = " << y << endl;

	double m;
	m = x > y ? x : y;
	cout << "The biggest one = " << m << endl;

	return 0;
}