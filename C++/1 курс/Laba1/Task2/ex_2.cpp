// ������������ 1, ������ 2. ���������: ������ �.�.

/* ���������� ��������� ��� ���������� 
��������� ��������������� ��������. ��������� ��������� 
�� ����� �++ ��� ������� �����������. �������� ������ 
������ � ����������. ������� � ����� �� ������� */

#include<iostream>
#include <cmath> // ����������� ���������� ��� ������������� �������������� �������
using namespace std; // ����������� ������������ ����

int main() {

	double n, m, x, k, a, y, d; // ���������� � ��������� ������ 

	cout << "Enter number K - "; // ����� ������
	cin >> k; // ���� ������

	do {
		cout << "Enter numbers n and m - ";
		cin >> n >> m;

		a = abs(n + m); // abs - ������ ���������

		if (a == 0) cout << "\nYou cannot divide by zero! Please enter normal numbers!\n" << endl;
	} while (a == 0);

	cout << "Enter number x - ";
	cin >> x;
	
	d = tan(x); // ���������� ��������

	k = k / a; 

	y = 1.29 + k + powl(d,2);
	cout << "\nThe result = " << y;

	return 0;
}