// ������������ 2, ������ 3. ���������: ������ �.�.

/* �������� ��������� ���������� ������������� �� ����
������������ ����� X � Y � �������������� ��������� ��������. ��������
��� �������� ���������. � �������������� ���������� ����������� ���� ���
����������� ������� � ��� ��. */

#include<iostream>
using namespace std;

int main() {

	double x, y;

	cout << "Enter two numbers - ";
	cin >> x >> y;

	bool k;
	k = x > y ? 1 : 0;

	if (k) {
		cout << "\nThe biggest one = " << x << endl;
	}
	else cout << "\nThe biggest one = " << y << endl;

	double m;
	m = x > y ? x : y;
	cout << "The biggest one = " << m << endl;

	return 0;
}