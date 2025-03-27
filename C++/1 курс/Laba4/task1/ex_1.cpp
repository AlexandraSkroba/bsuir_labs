// Лабораторная 4, задача 1. Выполнена: Скроба А.П.

/* Вывести все неповторяющиеся элементся массива */

#include<iostream>
#define n 6
using namespace std;

int main()
{

	setlocale(LC_ALL, "Rus");

	int mass[n];
	bool flag = false;

	/* Заполним массив значениями */
	do {
		for (int i = 0; i < n; i++) {
			cout << "[" << i + 1 << "]" << ": ";
			cin >> mass[i];
		}
		/* Проверка на ввод */
		if (cin.fail()) {
			cin.clear();
			cin.ignore();
			cout << "\nОшибка\nВведите целое число." << endl;
			flag = true;
		}

	} while (flag);

	cout << "\nВаш массив: ";

	for (int i = 0; i < n; ++i) {
		cout << mass[i] << " ";
	}

	cout << endl << endl;

	cout << "Массив без повторяющихся элементов: ";

	/* Проходим по всем элементам массива */
	for (int i = 0; i < n; ++i) {
		// Вынесем текущий элемент в переменную
		int currentElementValue = mass[i];
		// Имеет ли текущий элемент значение, встречающееся в массиве
		// по умолчанию нет
		bool hasEquals = false;

		/* Берем элемент и ищем по массиву такое же значение */
		for (int r = 0; r < n; ++r) {
			// С самим с собой не сравниваем, пропускаем итерацию
			if (i == r) {
				continue;
			}
			// Если текущий элемент равен другому элементу
			if (currentElementValue == mass[r] && i != r) {
				// То устанавливаем флаг, что такое значение встречалось
				hasEquals = true;
			}
		}

		// Если у этого элемента нет встречающихся значений, то выводим
		if (!hasEquals) {
			cout << currentElementValue << " ";
		}
	}

	cout << endl;

	return 0;
}