// ������������ 2, ������ 1. ���������: ������ �.�.

/* ������ ��� ����� ����� x � y. ����������, ����� ��, ��� ���� �� ���
������� �� ������ ��� �������, ��� ���. */

#include<iostream>
using namespace std;

int main() {

	int x, y;
	do {
		cout << "Enter two integers - ";
		cin >> x >> y;

		if (y == 0) cout << "\nYou cannot divide by zero! Please enter normal numbers!\n" << endl;
	} while (y == 0);

	if (x % y == 0) {
		cout << "\nNumbers are divisible without remainder\n";
		return 0;
	}

	cout << "\nNumbers are not divisible without remainder\n";

	return 0;
}