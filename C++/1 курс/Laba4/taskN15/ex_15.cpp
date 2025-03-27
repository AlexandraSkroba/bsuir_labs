// Лабораторная 4, задача 15. Выполнена: Скроба А.П.

/* Таблица заполняется по следующему алгоритму: В таблицу вносятся все натуральные числа по порядку.
1 становится в левую верхнюю ячейку, затем выбирается самая левая незаполненная ячейка в самой первой 
строке таблицы и заполняется. Затем, пока у последней заполненной ячейки сосед слева существует и заполнен, 
опускаемся вниз и заполняем очередную ячейку. Когда же не окажется соседа слева, то начинается заполнение 
клеток справа налево. После того как будет заполнена ячейка в первом столбце, После этого алгоритм заполнения повторятся. 
Необходимо вывести строку и столбец в котором будет находится число, введенное с клавиатуры */


#include <iostream>
#include <cmath>

int input() {
    while (true) {
        int value;

        std::cin >> value;

        if (std::cin.fail() || value < 1) {
            std::cin.clear();
            std::cin.ignore(32767, '\n');
            std::cout << "Error\nEnter the number: ";
        } else {
            std::cin.ignore(32767, '\n');
            return value;
        }
    }
}

int main() {
    int size, order = 1, num, row = 0, col = 0;

    std::cout << "Enter the number: ";
    num = input();

    size = sqrt(num) + 1;

    int** arr = new int* [size];

    for (int i = 0; i < size; i++) {
        arr[i] = new int[size];
    }

    arr[0][0] = order;

    if (order != num) {
        col++;
        order++;
        while (order != num) {
            if (row < col) {
                arr[row][col] = order;
                row++;
            } else if (row >= col && col != 0) {
                arr[row][col] = order;
                col--;
            } else if (col == 0) {
                arr[row][col] = order;
                col = row + 1;
                row = 0;
            } order++;
        }
    }

    std::cout << "Line - " << row << ", column - " << col;

    for (int i = 0; i < size; i++) {
        delete[] arr[i];
    }

    delete[] arr;
}