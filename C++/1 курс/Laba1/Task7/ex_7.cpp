// ������������ 1, ������ 7. ���������: ������ �.�.

/* ���������� ��������� ������ ������� ���� ������������� 
����� ������ ��� ������������� �������������� ������.*/

#include<iostream> 
using namespace std; 

int main() {

	int a, b;
	cout << "Enter the number a = ";
	cin >> a;
	cout << "Enter the number b = ";
	cin >> b;

	a = a ^ b;
	b = a ^ b;
	a = a ^ b;

	cout << "\na = " << a << "\nb = " << b << endl;

	return 0;
}