// Лабораторная 2, задача 7. Выполнена: Скроба А.П.

/* Составить программу для решения уравнений трёх видов:
7.1 ax^4 + bx^2 + c = 0;
7.2 ax^4 + bx^3 + cx^2 + bx + a = 0
7.3 x^3 + px + q = 0 */

#include<iostream>
#include<cmath>
using namespace std;

int main() {

	double a, b, c, d, t1, t2, x;
	cout << "Enter three numbers, please - ";
	cin >> a >> b >> c;

		if (a < 0) {
			if (b < 0) {
				if (c < 0) {
					d = b * b - 4 * a * c;
					cout << "Zalupa - " << d << endl;
					if (d < 0) {
						cout << "No solution!\n";
					}
					else if (d == 0 || d > 0) {
						t1 = (-b + sqrt(d)) / (2 * a);
						cout << "Zal2 - " << t1 << endl;
						t2 = (-b - sqrt(d)) / (2 * a);
						cout << "Zal3 - " << t2 << endl;
						x = sqrt(t1);
						cout << "The ftrst x = " << abs(x) << endl;
						x = sqrt(t2);
						cout << "The second x = " << x << endl;
					}
				} else if (c == 0) {

				} else if (c > 0) {

				}
			} else if (b == 0) {
				if (c < 0) {

				} else if (c == 0) {

				} else if (c > 0) {

				}
			} else if (b > 0) {
				if (c < 0) {

				}
				else if (c == 0) {

				}
				else if (c > 0) {

				}
			}
		} else if (a == 0 ) {
			if (c == 0 && b == 0) {
				cout << "x = R \n";
			}
			else {
				cout << "No solution!" << endl;
			}
		}
		else if (a > 0) {
			if (b < 0) {
				if (c < 0) {

				}
				else if (c == 0) {

				}
				else if (c > 0) {

				}
			}
			else if (b == 0) {
				if (c < 0) {

				}
				else if (c == 0) {

				}
				else if (c > 0) {

				}
			}
			else if (b > 0) {
				if (c < 0) {

				}
				else if (c == 0) {

				}
				else if (c > 0) {

				}
				return 0;
			}
		}