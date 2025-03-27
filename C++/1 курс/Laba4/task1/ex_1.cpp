// ������������ 4, ������ 1. ���������: ������ �.�.

/* ������� ��� ��������������� ��������� ������� */

#include<iostream>
#define n 6
using namespace std;

int main()
{

	setlocale(LC_ALL, "Rus");

	int mass[n];
	bool flag = false;

	/* �������� ������ ���������� */
	do {
		for (int i = 0; i < n; i++) {
			cout << "[" << i + 1 << "]" << ": ";
			cin >> mass[i];
		}
		/* �������� �� ���� */
		if (cin.fail()) {
			cin.clear();
			cin.ignore();
			cout << "\n������\n������� ����� �����." << endl;
			flag = true;
		}

	} while (flag);

	cout << "\n��� ������: ";

	for (int i = 0; i < n; ++i) {
		cout << mass[i] << " ";
	}

	cout << endl << endl;

	cout << "������ ��� ������������� ���������: ";

	/* �������� �� ���� ��������� ������� */
	for (int i = 0; i < n; ++i) {
		// ������� ������� ������� � ����������
		int currentElementValue = mass[i];
		// ����� �� ������� ������� ��������, ������������� � �������
		// �� ��������� ���
		bool hasEquals = false;

		/* ����� ������� � ���� �� ������� ����� �� �������� */
		for (int r = 0; r < n; ++r) {
			// � ����� � ����� �� ����������, ���������� ��������
			if (i == r) {
				continue;
			}
			// ���� ������� ������� ����� ������� ��������
			if (currentElementValue == mass[r] && i != r) {
				// �� ������������� ����, ��� ����� �������� �����������
				hasEquals = true;
			}
		}

		// ���� � ����� �������� ��� ������������� ��������, �� �������
		if (!hasEquals) {
			cout << currentElementValue << " ";
		}
	}

	cout << endl;

	return 0;
}