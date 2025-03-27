// Лабораторная 2, задача 9. Выполнена: Скроба А.П.

/* Даны действительные положительные числа x, y, z. Выяснить,
существует ли треугольник с длинами сторон x, y, z */

#include<iostream>
using namespace std;

int main() {

	double x, y, z;

	cout << "Enter three numbers (sides of a triangle) - ";
	cin >> x >> y >> z;

	if (x + y > z && x + z > y && y + z > x) {
		cout << "Such a triangle exists!";

		return 0;
	}

	cout << "Such a triangle doesn't exists!" << endl;

	return 0;
}