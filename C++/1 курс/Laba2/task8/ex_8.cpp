// Лабораторная 2, задача 13. Выполнена: Скроба А.П.

/* Вычислить значение y в зависимости от выбранной функции f(x),
аргумент определяется из поставленного условия. Возможные значения
функции f(x): 2x, x^3, x/3 (выбор осуществляется используя оператор switch).
Предусмотреть вывод сообщений, показывающих, при каком условии и с какой
функцией производились вычисления y */

#include<iostream>
#include<cmath>

using namespace std;

int main() {

	setlocale(LC_ALL, "Rus");

	int k;
	double z, x, fx, b, a, y, t;

	cout << "Введите значение x - ";
	cin >> x;

	do {
		cout << "Веберете аргумент функции (возможные значения функции f(x): 2x, x^3, x/3)" << endl;
		cin >> k;
		if (k > 3 || k < 1) cout << "Выберите одно из значений функций вводм 1, 2 или 3 - " << endl;
	} while (k > 3 || k < 1);

	cout << "Введите переменную z - ";
	cin >> z;

	if (z <= 0) {
		x = powl(z, 2) / 2;
	}
	else {
		x = sqrt(z);
	}

	cout << "x = " << x << endl;

	switch (k)
	{
	case 1: 
		fx = 2 * x;
		break;
	case 2:
		fx = powl(x, 3);
		break;
	case 3:
		fx = x / 3;
		break;
	}

	cout << "fx = " << fx << endl;

	cout << "Введите переменную b и a - ";
	cin >> b >> a;

	y = b * fx / cos(x) + a * log(fabs(tan(x / 2)));
	cout << "y = " << y << endl;

	return 0;
}