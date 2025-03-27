// ������������ 2, ������ 13. ���������: ������ �.�.

/* ��������� �������� y � ����������� �� ��������� ������� f(x),
�������� ������������ �� ������������� �������. ��������� ��������
������� f(x): 2x, x^3, x/3 (����� �������������� ��������� �������� switch).
������������� ����� ���������, ������������, ��� ����� ������� � � �����
�������� ������������� ���������� y */

#include<iostream>
#include<cmath>

using namespace std;

int main() {

	setlocale(LC_ALL, "Rus");

	int k;
	double z, x, fx, b, a, y, t;

	cout << "������� �������� x - ";
	cin >> x;

	do {
		cout << "�������� �������� ������� (��������� �������� ������� f(x): 2x, x^3, x/3)" << endl;
		cin >> k;
		if (k > 3 || k < 1) cout << "�������� ���� �� �������� ������� ����� 1, 2 ��� 3 - " << endl;
	} while (k > 3 || k < 1);

	cout << "������� ���������� z - ";
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

	cout << "������� ���������� b � a - ";
	cin >> b >> a;

	y = b * fx / cos(x) + a * log(fabs(tan(x / 2)));
	cout << "y = " << y << endl;

	return 0;
}