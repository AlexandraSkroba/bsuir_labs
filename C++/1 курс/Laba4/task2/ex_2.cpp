// Лабораторная 4, задача 2. Выполнена: Скроба А.П.

/* Определить сумму элементов, расположенных на главной диагонали матрицы,
и произведение элементов, расположенных на побочной диагонали матрицы */

#include<iostream>
using namespace std;

int main() {
	setlocale(LC_ALL, "Rus");

	const int ROW = 3, COL = 3;
	int arr[ROW][COL]{};
	int sum = 0, q = ROW, mult = 1;
	bool flag = false;

	cout << "Введите элементы матрицы " << ROW << " на " << COL << ": ";

	do {
		for (int i = 0; i < ROW; i++) {
			for (int j = 0; j < COL; j++) {
				cin >> arr[i][j];
			}
		}

		if (cin.fail()) {
			cin.clear();
			cin.ignore();
			cout << "\nБалбес, меняй.\n" << endl;
			flag = true;
		}

	} while (flag);

	cout << "Получите-распишитесь: " << endl;

	for (int i = 0; i < ROW; i++) {
		for (int j = 0; j < COL; j++) {
			cout << arr[i][j] << "\t";
		}
		cout << endl << endl;
	}

	for (int i = 0; i < ROW; i++) {
		sum += arr[i][i];
	}

	cout << "\nCумма элементов, расположенных на главной диагонали матрицы = " << sum << endl;

	for (int i = 0; i < ROW; i++) {
		q -= 1;
		mult *= arr[i][q];
	}

	cout << "Произведение элементов, расположенных на побочной диагонали матрицы = " << mult << endl;

	return 0;
}