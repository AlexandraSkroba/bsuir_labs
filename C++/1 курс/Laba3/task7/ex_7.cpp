// ������������ 3, ������ 7. ���������: ������ �.�.

/* ����� ����������� �����, ���������� ��� ���������, ��� ���
����� ��� ���� ����� �������� ������ �����. */

#include<iostream>
#include<cmath>

using namespace std;

int main() {
	setlocale(LC_ALL, "Rus");

	int a, b;

	cout << "��������� ������� ����� ����������� ����� ��� ��� ����� ��� ���� ����� �������� ������ �����." << endl;

	for (int i = 10; i <= 99; ++i) {
		a = i / 10;
		b = i - a * 10; 
		if (powl((a + b), 3) == powl(i, 2)) {
			cout << "\n�� ����� ����� �����!\n��� - " << i << "!" << endl;
		}
	}

	return 0;
}