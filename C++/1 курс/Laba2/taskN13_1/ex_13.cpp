// ������������ 2, ������ 13. ���������: ������ �.�.

/* ������ �� ��� ������� R ������ � ������������� ���������
�������� P � ������ ����� Q? */

#include<iostream>
#include<cmath>
#define P 3.14159265

using namespace std;

int main() {

	setlocale(LC_ALL, "Rus");

	double r, p, q;

	cout << "������� ������ ���������� - ";
	cin >> r;

	cout << "\n������� ������� ����� - ";
	cin >> p;

	do {
		cout << "\n������� ���� ����� � �������� - ";
		cin >> q;

		if (q > 90 || q < 0) cout << "���� ����� ������ ���� ������! ������� ���� ��������, ���������, ����� ��������� :(\n";
	} while (q > 90 || q < 0);

	if ( r <= p * sin(q) / 2) {
		cout << "���������� ������� � �������� �����!" << endl;

		return 0;
	}

	cout << "\n���������� �� ������� � �������� �����!" << endl;

	return 0;
}