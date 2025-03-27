// ������������ 4, ������ 2. ���������: ������ �.�.

/* ���������� ����� ���������, ������������� �� ������� ��������� �������,
� ������������ ���������, ������������� �� �������� ��������� ������� */

#include<iostream>
using namespace std;

int main() {
	setlocale(LC_ALL, "Rus");

	const int ROW = 3, COL = 3;
	int arr[ROW][COL]{};
	int sum = 0, q = ROW, mult = 1;
	bool flag = false;

	cout << "������� �������� ������� " << ROW << " �� " << COL << ": ";

	do {
		for (int i = 0; i < ROW; i++) {
			for (int j = 0; j < COL; j++) {
				cin >> arr[i][j];
			}
		}

		if (cin.fail()) {
			cin.clear();
			cin.ignore();
			cout << "\n������, �����.\n" << endl;
			flag = true;
		}

	} while (flag);

	cout << "��������-�����������: " << endl;

	for (int i = 0; i < ROW; i++) {
		for (int j = 0; j < COL; j++) {
			cout << arr[i][j] << "\t";
		}
		cout << endl << endl;
	}

	for (int i = 0; i < ROW; i++) {
		sum += arr[i][i];
	}

	cout << "\nC���� ���������, ������������� �� ������� ��������� ������� = " << sum << endl;

	for (int i = 0; i < ROW; i++) {
		q -= 1;
		mult *= arr[i][q];
	}

	cout << "������������ ���������, ������������� �� �������� ��������� ������� = " << mult << endl;

	return 0;
}