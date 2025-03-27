// Лабораторная 2, задача 7. Выполнена: Скроба А.П.

/* Составить программу для решения уравнений трёх видов:
7.3 x^3 + px + q = 0 */

#include<iostream>
#include<cmath>
using namespace std;

int main() {

	double x, p, q, z, Q, r, s, f, ch, sh, a, x1;
	double P = 3.1415926,  e = 2.718281;

	cout << "Enter two numbers - ";
	cin >> p >> q;

	if (p == 0) {
		x = powl(q, 1./3.);
		cout << "\nx = " << x << endl;

		return 0;
	}
	else if (q == 0) {
		if (p < 0) {
			cout << "\nx = 0" << endl;
			return 0;
		}
		else if (p > 0) {
			cout << "\nx1 = 0, x2 = " << sqrt(p) << ", x3 = " << -sqrt(p) << endl;
			return 0;
		}
	}
	
	cout << "\np = " << p << ", q = " << q << endl;

	Q = -p / 3.;
	cout << "\nQ = " << Q << endl;
	r = q / 2.;
	cout << "\nr = " << r << endl;
	s = powl(Q, 3) - powl(r, 2);
	cout << "\ns = " << s << endl;

	if (s > 0) {
		f = 1 / 3. * acos(r / sqrt(powl(Q, 3)));
		x = -2 * sqrt(Q) * cos(f);
		cout << "\nx1 = " << x;
		x = -2 * sqrt(Q) * cos(f + 2 / 3. * P);
		cout << ", x2 = " << x;
		x = -2 * sqrt(Q) * cos(f - 2 / 3. * P);
		cout << ", x3 = " << x << endl;
	}
	else if (s < 0) {
		if (Q > 0) {
			z = abs(r) / sqrt(powl(Q, 3)); // 1 <= z < беск.
			f = log(z + sqrt(z * z - 1)); // 0 <= f < беск.
			f = 1 / 3. * f;
			ch = (exp(f) + exp(-f)) / 2;
			sh = (exp(f) - exp(-f)) / 2;

			if (r == 0) r = 0;
			else if (r > 0) r = 1;
			else if (r < 0) r = -1;

			x = -2 * r * sqrt(Q) * ch;
			cout << "\nx1 = " << x;
			x = r * r * Q * ch - 3 * Q * sh * sh;
			cout << ", x2 = " << x;
			x = r * r * Q * ch + 3 * Q * sh * sh;
			cout << ", x3 = " << x << endl;

			return 0;
		}
		else if (Q < 0) {
			z = abs(r) / sqrt(powl(abs(Q), 3)); // 1 <= z < беск.
			f = 1 / 3. * asinh(z);

			ch = (exp(f) + exp(-f)) / 2;
			sh = (exp(f) - exp(-f)) / 2;


			if (r == 0) {
				r = 0;
			}
			else if (r > 0) {
				r = 1;
			}
			else if (r < 0) {
				r = -1;
			}

			cout << "\nsgn(r) = " << sh << endl;

			x = -2 * r * sqrt(abs(Q)) * sh;
			cout << "\nx1 = " << x;
			x = r * r * abs(Q) * sh - 3 * abs(Q) * ch * ch;
			cout << ", x2 = " << x;
			x = r * r * abs(Q) * sh + 3 * abs(Q) * ch * ch;
			cout << ", x3 = " << x << endl;

			return 0;
		}
		else if (Q == 0) {
			x1 = -powl(q, 1 / 3.);
			cout << "\nx1 = " << x1;
			x = x1 * x1 / 4 + 0.25 * abs((-3 * x1) * x1 - 4 * p);
			cout << ", x2 = " << x;
			x = x1 * x1 / 4 - 0.25 * abs((-3 * x1) * x1 - 4 * p);
			cout << ", x3 = " << x << endl;
		}
	}

	return 0;
}