// ������������ 2, ������ 16. ���������: ������ �.�.

/* ������� ��� �����. �������� �� ��� � ��� */

#include<iostream>
using namespace std;

int main() {
	setlocale(LC_ALL, "Rus");

	int x, y, x1, y1;

	do {
		cout << "������� ��� ����� - ";
		cin >> x >> y;
		if (x == 0 || y == 0) cout << "Enter a normal number, please!\n";
	} while (x == 0 || y == 0);

	x1 = x;
	y1 = y;

	if (x == y) {
		cout << "\n��� ����� (" << x << ", " << y << ") = " << x;
		cout << "\n��� ����� (" << x << ", " << y << ") = " << x << endl;
		return 0;
	}

	cout << "\n��� ����� (" << x << ", " << y << ") = ";

	while (x != y) {
		if (x > y) {
			x -= y;
		}
		else {
			y -= x;
		}
	} cout << x;

	cout << "\n��� ����� (" << x1 << ", " << y1 << ") = ";
	cout << x1 * y1 / x << endl;

	return 0;
}