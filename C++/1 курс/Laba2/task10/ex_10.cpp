// ������������ 2, ������ 10. ���������: ������ �.�.

/* �� �������, ������������ ����������� a = sinx, b = cosx, c = ln|x|
��� �������� �, ���������� � ������� �� ����� ������� �����������
��������. ���������� <cmath> ������������ ��������� */

#include<iostream>
#include<cmath>

using namespace std;

int main() {

	setlocale(LC_ALL, "Rus");

	double x, a, f, x1, z, n, b, c, x2;

	cout << "������� ����� x - ";
	cin >> x;

	x2 = x;

	while (x >= 2 * 3.14159265)
	{
		x -= 3.14159265;
	}

	while (x <= 2 * -3.14159265) {
		x += 3.14159265;
	}

	cout << "\n� ����������� cmath sin(x) = " << sin(x) << endl;

	x1 = x;
	f = 1;
	a = 0;
	n = 1;
	z = 1;

	while (x1 / f != 0)
	{
		a = a + z * x1 / f;
		x1 = x1 * x * x;
		n = n + 2;
		f = f * (n - 1) * n;
		z = z * (-1);
	}

	cout << "sin(x) = " << a << endl;

	cout << "\n� ����������� cmath cos(x) = " << cos(x) << endl;

	x1 = x * x;
	f = 2;
	b = 1;
	n = 2;
	z = -1;

	while (x1 / f != 0)
	{
		b = b + z * x1 / f;
		x1 = x1 * x * x;
		n = n + 2;
		f = f * (n - 1) * n;
		z = z * (-1);
	}

	cout << "cos(x) = " << b << endl;

	double i = 1, ln = 0, v, p = 1, y;

	if (x <= 0)
	{
		cout << "\n����������� �������� ��� x <= 0 �� ���������!" << endl;
		return 0;
	}

	if (x == 1) {
		cout << "\n� ����������� cmath ln(x) = " << log(x);
		cout << "\nln(x) = " << 0 << endl;
		return 0;
	}

	x1 = x;

	v = (x + 1) / (x - 1);

	double s = ((x - 1) * (x - 1)) / ((x + 1) * (x + 1));

	while (i <= 150) {
		v *= s;
		y = (1 / p) * v;
		ln = ln + y;
		p = p + 2;
		i++;
	}

	cout << "\n� ����������� cmath ln(x) = " << log(x1);
	cout << "\nln(x) = " << 2 * ln << endl;

	return 0;
} 