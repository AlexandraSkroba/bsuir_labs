// Лабораторная 2, задача 13. Выполнена: Скроба А.П.

/* Сможет ли шар радиуса R пройти в ромбообразное отверстие
стороной P и острым углом Q? */

#include<iostream>
#include<cmath>
#define P 3.14159265
using namespace std;

int main() {

	double r, p, q, sr, sp;

	cout << "Enter the radius of the circle - ";
	cin >> r;

	cout << "\nEnter the side of the rhombus - ";
	cin >> p;

	do {
		cout << "\nEnter the sharp corner angle of the rhombus in radians! - ";
		cin >> q;

		if (q <= 0) cout << "The angle in a rhombus cannot be 0 radians! Please enter another numbers!\n" << endl;
	} while (q <= 0 || q >= 1.5708);

	sr = P * powl(r, 2);
	sp = powl(p, 2) * sin(q);

	if (sp < 0) {
		sp *= -1;
	}

	if (sr < sp) {
		cout << "\nThe ball will be able to pass into the hole of the rhombus" << endl;
	}
	else if (sr > sp) {
		cout << "\nThe ball will not be able to pass into the hole of the rhombus" << endl;
		return 0;
	}

	return 0;
}