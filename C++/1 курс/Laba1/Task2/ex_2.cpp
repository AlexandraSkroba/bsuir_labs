// Лабораторная 1, задача 2. Выполнена: Скроба А.П.

/* Разработка программы для реализации 
линейного вычислительного процесса. Составить программу 
на языке С++ для расчета соотношения. Исходные данные 
ввести с клавиатуры. Вариант – номер по журналу */

#include<iostream>
#include <cmath> // подключение библиотеки для использования математических функций
using namespace std; // подключение пространства имен

int main() {

	double n, m, x, k, a, y, d; // переменные с плавующей точкой 

	cout << "Enter number K - "; // вывод текста
	cin >> k; // ввод данных

	do {
		cout << "Enter numbers n and m - ";
		cin >> n >> m;

		a = abs(n + m); // abs - модуль выражения

		if (a == 0) cout << "\nYou cannot divide by zero! Please enter normal numbers!\n" << endl;
	} while (a == 0);

	cout << "Enter number x - ";
	cin >> x;
	
	d = tan(x); // вычесление тангенса

	k = k / a; 

	y = 1.29 + k + powl(d,2);
	cout << "\nThe result = " << y;

	return 0;
}