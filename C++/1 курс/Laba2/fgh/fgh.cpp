// ������������ 2, ������ 10. ���������: ������ �.�.

/* �� �������, ������������ ����������� a = sinx, b = cosx, c = ln|x|
��� �������� �, ���������� � ������� �� ����� ������� �����������
��������. ���������� <cmath> ������������ ��������� */

#include<iostream>
#include<cmath>

using namespace std;

int main() {

	setlocale(LC_ALL, "Rus");

	double x, f, x1, z, c;

	cout << "������� ����� x - ";
	cin >> x;

	cout << "\n� ����������� cmath ln(x) = " << log(x) << endl;

	x1 = x;
	f = 1;
	c = 0;
	z = 1;

	if (x1 < 0) {
		x1 *= -1;
	}

	if (x1 == 0) {
		cout << "������������ ��������� ���� �� ����������" << endl;

		cout << "\n� ����������� cmath ln(x) = " << log(x) << endl;

		x1 = x;
		f = 1;
		c = 0;
		z = 1;

		if (x1 < 0) {
			x1 *= -1;
		}

		if (x1 == 0) {
			cout << "������������ ��������� ���� �� ����������" << endl;

			return 0;
		}

		while ( 0 < (x1 / f) < 1)
		{
			c = c + z * x1 / f;
			x1 = x1 * x;
			f = f + 1;
			z = z * (-1);
		}

		cout << "ln(x) = " << c << endl;

		return 0;
	}