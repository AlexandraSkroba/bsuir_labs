// ������������ 1, ������ 9. ���������: ������ �.�.

/* �� ���� ���� b1 - ������ ���� �������������� ����������. 
���������� ��������� ����� ���� ������ ��������� �������������� ����������, 
��� ����������� ���������� q ����� 1/(n+1), ��� n - ��� ����� � �������*/

#include<iostream>
using namespace std;

int main() {

	double b1, q, s;

	cout << "Enter the first term of a geometric progression - ";
	cin >> b1;

	q = 1.0 / 26;

	s = b1 / (1 - q);
	cout << "\nThe sum of the progression = " << s << endl;

	return 0;
}