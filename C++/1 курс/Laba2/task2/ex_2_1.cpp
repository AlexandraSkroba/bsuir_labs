// ������������ 2, ������ 2. ���������: ������ �.�.

/* ������� �� ���� �������� ���������� ������ ���� � � Y ��������
����, � � ������ �� ��������� - �������� ������ ��� */

#include<iostream>
using namespace std;

int main() {

	int x, y;

	cout << "Enter two integers - ";
	cin >> x >> y;

	if (x < y) {
		x = 0;
		cout << "\nx < y, x = " << x << endl;

		return 0;
	}
	else if (x > y) {
		y = 0;
		cout << "\nx > y, y = " << y << endl;

		return 0;
	}

	x = y = 0;
	cout << "\n x = y, x = " << x << " and y = " << y << endl;

	return 0;
}