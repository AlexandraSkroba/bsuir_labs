// Лабораторная 4, задача 5. Выполнена: Скроба А.П.

#include<iostream>
#include<ctime>
using namespace std;

int main() {
	setlocale(LC_ALL, "Rus");
	srand(time(0));

	int row, col, n;

	do {
		cout << "Введите количество строк массива: ";
		cin >> row;

		if (row <= 0) cout << "\nРазмер массива может быть только положительным!" << endl;
	} while (row <= 0);

	do {
		cout << "Введите количество столбцов массива: ";
		cin >> col;

		if (col <= 0) cout << "\nРазмер массива может быть только положительным!" << endl;
	} while (col <= 0);
	cout << endl;

	cout << "Выберите как вы хотите заполнить массив:\n1.Рандомом\n2.Вручную\n";
	do
	{
		cin >> n;
		if (n < 1 || n > 2) cout << "Выберите первый или второй пункт!";
	} while (n < 1 || n > 2);

	/* объявление и заполнение первого массива */
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

	/* объявление второго массива */
	long double** mass = new long double* [row];
	for (int i = 0; i < row; i++) {
		mass[i] = new long double[col];
	}

	/* сглаживание массива */
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

	cout << "\nПолученный массив:" << endl;
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			cout << mass[i][j] << "\t";
		}
		cout << endl;
	}


	/* удаление первого массива */
	for (int i = 0; i < row; i++) {
		delete[] arr[i];
	}

	delete[] arr;

	/* удаление второго массива */
	for (int i = 0; i < row; i++) {
		delete[] mass[i];
	}

	delete[] mass;
	return 0;
}