// Лабораторная 5, задача 3_2. Выполнена: Скроба А.П.

/* Создать двумерный динамический массив вещественных чисел. Определить,
встречаются ли среди них элементы с нулевым значением. Если встречаются такие
элементы, то определить их индексы и общее количество. Переставить элементы этого
массива в обратном порядке и вывести на экран.
Использовать функции. */

#include<iostream>
using namespace std;

/* проверка на ввод */
int input() {
    while (true) {
        int value;

        std::cin >> value;

        if (std::cin.fail() || value < 1) {
            std::cin.clear();
            std::cin.ignore(32767, '\n');
            std::cout << "Error\nEnter the number: ";
        }
        else {
            std::cin.ignore(32767, '\n');
            return value;
        }
    }
}

/* проверка на ввод элементов массива */
int input_arr() {
    while (true) {
        double element;

        std::cin >> element;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(32767, '\n');
            std::cout << "Error\nEnter the number: ";
        }
        else {
            std::cin.ignore(32767, '\n');
            return element;
        }
    }
}

/* заполнение и вывод массива */
void create_arr (double **arr, int row, int col) {
    for (int i = 0; i < row; i++) {
        arr[i] = new double[col];
    }

    std::cout << "Enter value of matrix: \n";
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            std::cout << "[" << i << "]" << "[" << j << "] ";
            //arr[i][j] = input_arr();
            arr[i][j] = INT16_MAX;
        }
    }

    std::cout << "\nВаш массив: \n";
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            std::cout << arr[i][j] << "\t";
        }
        std::cout << "\n\n";
    }
}

/* нахождение нулевых элементов массива */
void arr_null(double **arr, int row, int col, int count) {
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            if (arr[i][j] == 0) {
                count++;
                std::cout << "Индекс " << count << " нулевого значения массива - " << "[" << i << "]" << "[" << j << "]\n";
            }
        }
    }
    if (count > 0) std::cout << "Количество нулевых элементов в массиве: " << count << std::endl;
    else std::cout << "В массиве нет нулевых элементов" << std::endl;
}

/* вывод матрицы в обратном порядке */
void arr_reverse(double **arr, int row, int col) {
    for (int i = row - 1; i >= 0; i--) {
        for (int j = col - 1; j >= 0; j--) {
            std::cout << arr[i][j] << "\t";
        }
        std::cout << "\n\n";
    }
}

int main() {
    setlocale(LC_ALL, "rus");
    int row, col, count = 0;
    cout << "Введите количество рядов массива: ";
    row = input();
    cout << "Введите количество столбцов массива: ";
    col = input();

    double** arr = new double* [row];
    create_arr(arr, row, col); // создание и заполнение массива 
    arr_null(arr, row, col, count); // нахождение нулевых элементов массива
 
    std::cout << "\nМассив наоборот: \n";
    arr_reverse(arr, row, col); // вывод матрицы в обратном порядке

    /* удаление массивов */
    for (int i = 0; i < row; i++) {
        delete[] arr[i];
    }
    delete[] arr;

	return 0;
}