// ������������ 4, ������ 5. ���������: ������ �.�.

#include<iostream>
#include<ctime>
using namespace std;

int main() {
	setlocale(LC_ALL, "Rus");
	srand(time(0));

	int row, col, n;

	do {
		cout << "������� ���������� ����� �������: ";
		cin >> row;

		if (row <= 0) cout << "\n������ ������� ����� ���� ������ �������������!" << endl;
	} while (row <= 0);

	do {
		cout << "������� ���������� �������� �������: ";
		cin >> col;

		if (col <= 0) cout << "\n������ ������� ����� ���� ������ �������������!" << endl;
	} while (col <= 0);
	cout << endl;

	cout << "�������� ��� �� ������ ��������� ������:\n1.��������\n2.�������\n";
	do
	{
		cin >> n;
		if (n < 1 || n > 2) cout << "�������� ������ ��� ������ �����!";
	} while (n < 1 || n > 2);

	/* ���������� � ���������� ������� ������� */
	long double** arr = new long double* [row];
	for (int i = 0; i < row; i++) {
		arr[i] = new long double[col];
	}

	switch (n)
	{
	case 1:
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++) {
				arr[i][j] = rand() % 10;
			}
		}
		break;
	case 2:
		for (int i = 0; i < row; i++)
		{
			for (int k = 0; k < col; k++)
			{
				cout << "A" << i << k << " ";
				cin >> arr[i][k];
			}
		}
		break;
	}

	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			cout << arr[i][j] << "\t";
		}
		cout << endl;
	}

	/* ���������� ������� ������� */
	long double** mass = new long double* [row];
	for (int i = 0; i < row; i++) {
		mass[i] = new long double[col];
	}

	/* ����������� ������� */
	mass[0][0] = (arr[0][1] + arr[1][0]) / 2;
	mass[0][col - 1] = (arr[0][col - 2] + arr[1][col - 1]) / 2;
	mass[row - 1][0] = (arr[row - 2][0] + arr[row - 1][1]) / 2;
	mass[row - 1][col - 1] = (arr[row - 2][col - 1] + arr[row - 1][col - 2]) / 2;

	for (int j = 1; j < col - 1; j++) {
		int k = 0;
		int g = j;
		mass[0][j] = (arr[k][g - 1] + arr[k][g + 1] + arr[k + 1][g]) / 3;

		k = row - 1;
		g = j;
		mass[row - 1][j] = (arr[k][g - 1] + arr[k][g + 1] + arr[k - 1][g]) / 3;
	}

	for (int i = 1; i < row - 1; i++) {
		int k = i;
		int g = 0;
		mass[i][0] = (arr[k - 1][g] + arr[k + 1][g] + arr[k][g + 1]) / 3;

		k = i;
		g = col - 1;
		mass[i][col - 1] = (arr[k - 1][g] + arr[k + 1][g] + arr[k][g - 1]) / 3;
	}

	for (int i = 1; i < row - 1; i++) {
		for (int j = 1; j < col - 1; j++) {
			int k = i;
			int g = j;
			mass[i][j] = (arr[k][g - 1] + arr[k][g + 1] + arr[k - 1][g] + arr[k + 1][g]) / 4;
		}
	}

	cout << "\n���������� ������:" << endl;
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			cout << mass[i][j] << "\t";
		}
		cout << endl;
	}


	/* �������� ������� ������� */
	for (int i = 0; i < row; i++) {
		delete[] arr[i];
	}

	delete[] arr;

	/* �������� ������� ������� */
	for (int i = 0; i < row; i++) {
		delete[] mass[i];
	}

	delete[] mass;
	return 0;
}