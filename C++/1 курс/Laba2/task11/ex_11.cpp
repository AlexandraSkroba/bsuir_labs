// Лабораторная 2, задача 11. Выполнена: Скроба А.П.

/* Определить, какая из двух фигур (круг или квадрат) имеет большую
площадь. Известно, что сторона квадрата равна a, радиус круга r. Библиотеку
<cmath> использовать запрещено */

#include<iostream>
using namespace std;

int main() {

	double a, r, sa, sr;
	const double P = 3.14159265;

	cout << "Enter the side of the square - ";
	cin >> a;

	cout << "Enter the radius of the circle - ";
	cin >> r;

	sa = a * a;
	sr = P * r * r;

	if (sa > sr) {
		cout << "\nSquare area = " << sa << "\nCircle area = " << sr << endl;
		cout << "\nThe area of the square is larger than the area of the circle! | sa > sr" << endl;
		return 0;
	}
	else if (sa < sr) {
		cout << "\nSquare area = " << sa << "\nCircle area = " << sr << endl;
		cout << "\nThe area of a square is less than the area of a circle! | sa < sr" << endl;
		return 0;
	}
	else if (sr == sa) {
		cout << "\nSquare area = circle area\n"; 
	}

	return 0;
}
