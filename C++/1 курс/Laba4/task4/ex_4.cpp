// Лабораторная 4, задача 4. Выполнена: Скроба А.П.

#include<iostream>
#include<ctime>
using namespace std;

int main() {
	setlocale(LC_ALL, "Rus");
	srand(3);

	int row, col, min = 0, g, k, n;

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

	long int** arr = new long int* [row];
	for (int i = 0; i < row; i++) {
		arr[i] = new long int[col];
	}

	/////////////////////////////////////////
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
			for (int k = 0; k < col;k++)
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

	if (arr[0][0] < arr[0][1] && arr[0][0] < arr[1][0]) min++;
	if (arr[0][row - 1] < arr[0][col - 2] && arr[0][col - 1] < arr[1][col - 1]) min++;
	if (arr[row - 1][0] < arr[row - 2][0] && arr[row - 1][0] < arr[row - 1][1]) min++;
	if (arr[row - 1][col - 1] < arr[row - 2][col - 1] && arr[row - 1][col - 1] < arr[row - 1][col - 2]) min++;

	for (int j = 1; j < col - 1; j++) {
		k = 0;
		g = j;
		if (arr[0][j] < arr[k][g - 1] && arr[0][j] < arr[k][g + 1] && arr[0][j] < arr[k + 1][g]) min++;

		k = row - 1;
		g = j;
		if (arr[row - 1][j] < arr[k][g - 1] && arr[row - 1][j] < arr[k][g + 1] && arr[row - 1][j] < arr[k - 1][g]) min++;
	}

	for (int i = 1; i < row - 1; i++) {
		k = i;
		g = 0;
		if (arr[i][0] < arr[k - 1][g] && arr[i][0] < arr[k + 1][g] && arr[i][0] < arr[k][g + 1]) min++;

		k = i;
		g = col - 1;

		if (arr[i][col - 1] < arr[k - 1][g] && arr[i][col - 1] < arr[k + 1][g] && arr[i][col - 1] < arr[k][g - 1]) min++;
	}

	for (int i = 1; i < row - 1; i++) {
		for (int j = 1; j < col - 1; j++) {
			k = i;
			g = j;
			if (arr[i][j] < arr[k][g - 1] && arr[i][j] < arr[k][g + 1] && arr[i][j] < arr[k - 1][g] && arr[i][j] < arr[k + 1][g]) min++;
		}
	}

	cout << "\nЛокальных минимумов - " << min << endl;

	/////// d e l e t e //////////
	for (int i = 0; i < row; i++) {
		delete[] arr[i];
	}

	delete[] arr;
	return 0;
}