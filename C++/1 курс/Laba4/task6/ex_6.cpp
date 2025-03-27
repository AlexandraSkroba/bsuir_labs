// ������������ 4, ������ 6. ���������: ������ �.�.

#include<iostream>
#include<cstdlib>
using namespace std;

int main() {
	setlocale(LC_ALL, "Rus");
	//srand(time(0));

	int row, col, g = 1, i = 0, j = 0, m;
	bool flag = false;

	do {
		cout << "������� ���������� ����� �������: ";
		cin >> row;

		if (row <= 0) cout << "\n������ ������� ����� ���� ������ �������������!" << endl;

		if (cin.fail()) {
			cin.clear();
			cin.ignore();
			cout << "\n����������� ����.\n" << endl;
			flag = true;
		}

	} while (row <= 0 || flag);

	do {
		cout << "������� ���������� �������� �������: ";
		cin >> col;

		if (cin.fail()) {
			cin.clear();
			cin.ignore();
			cout << "\n����������� ����.\n" << endl;
			flag = true;
		}

		if (col <= 0) cout << "\n������ ������� ����� ���� ������ �������������!" << endl;
	} while (col <= 0 || flag);

	cout << endl;

	long int** arr = new long int* [row];
	for (int i = 0; i < row; i++) {
		arr[i] = new long int[row];
	}

	//////////////////////////////

	cout << "������� �������� �������: ";
	for (int i = 0; i < row; i++) {
		cout << "\n\n������ " << i + 1 << " ������\n";
		for (int j = 0; j < col; j++) {
			//arr[i][j] = rand() % 10;
				cin >> arr[i][j];
		}
	}

	cout << "\n���� �������: " << endl;

	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			cout << arr[i][j] << '\t';
		}
		cout << endl;
	}

	while (i < row && g < row) {
		for (int j = 0; j < col; j++) {
			if (arr[i][j] > arr[g][j]) arr[g][j] = arr[i][j];
		}

		i++; g++;
	}

	cout << endl;

	/*for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			cout << arr[i][j] << '\t';
		}
		cout << endl;
	}*/

	i = 0;
	g = 1;

	while (j < col && g < col) {
		for (int i = 0; i < row; i++) {
			if (arr[i][j] > arr[i][g]) arr[i][g] = arr[i][j];
		}

		j++; g++;
	}

	cout << endl;

	cout << "���� ������� ����� ���������: " << endl;

	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			cout << arr[i][j] << '\t';
		}
		cout << endl;
	}

	/////// d e l e t e //////////
	for (int i = 0; i < row; i++) {
		delete[] arr[i];
	}

	delete[] arr;

	return 0;
}