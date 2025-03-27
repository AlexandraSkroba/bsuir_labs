// Лабораторная 5, задача 3_1. Выполнена: Скроба А.П.

/* Дан двумерный динамический массив целых чисел А размерностью n * k .
Размерность массива (n = 5, k = 6) ввести с клавиатуры. Значения элементов массива
ввести с клавиатуры. Создать динамический массив из элементов, расположенных на
главной диагонали матрицы и имеющих четное значение. Вычислить произведение
элементов динамического массива.
Созданный массив и результат произведения вывести на экран.
Использовать функции. */

#include<iostream>
#include<cstdlib>

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

/* заполнение первого динамического массива */
void input_arr(int** arr, int* row, int* col) {
    std::cout << "Enter value of matrix: \n";
    for (int i = 0; i < *row; i++) {
        for (int j = 0; j < *col; j++) {
            std::cout << "[" << i << "]" << "[" << j << "] ";
            //arr[i][j] = input();
            arr[i][j] = rand() % 50;
        }
    }
}

/* вывод первого двумерного динамического массива */
void output_arr(int** arr, int *row, int *col) {
    std::cout << "\nВаша матрица:" << std::endl;
    for (int i = 0; i < *row; i++) {
        for (int j = 0; j < *col; j++) {
            std::cout << arr[i][j] << "\t";
        }
        std::cout << "\n\n";
    }
}

/* заполнение второго динамического массива */
void filling_mass(int *mass, int *row, int **arr) {
    for (int i = 0, num = 0, p = 0; i < *row; i++)
    {
        for (int j = 0; j < *row; j++) {
            if (i == j && arr[i][j] % 2 == 0) {
                mass[num++] = arr[i][j];
            }
        }
    }
}

/* вывод второго двумерного динамического массива */
void output_mass(int *mass, int k) {
    std::cout << "Массив четных элементов главной диагонали: ";
    for (int p = 0; p < k; p++) {
        std::cout << mass[p] << " ";
    }
}

/* вычисление размера второго массива */
int compute(int* row, int* col, int** arr, int k) {
    for (int i = 0; i < *row; i++) {
        for (int j = 0; j < *col; j++) {
            if (i == j && arr[i][j] % 2 == 0) k++;
        }
    }
    return k;
}

int mass_prod(int *mass, int prod, int k) {
    for (int i = 0; i < k; i++) {
        prod *= mass[i];
    }
    return prod;
}

int main() {
    setlocale(LC_ALL, "rus");
    //srand(time(0));
    int row, col, k = 0, prod = 1;
	
    do {
        std::cout << "Enter rows of the matrix: ";
        row = input();

        std::cout << "Enter colums of the matrix: ";
        col = input();
        if (row != col) std::cout << "Главную диагональ можно найти только у квадратной матрицы!\n" << std::endl;
    } while (row != col);

    /* создание и заполнение первого массива */
    int** arr = new int* [row];
    for (int i = 0; i < row; i++) {
        arr[i] = new int[col];
    }

    input_arr(arr, &row, &col); //ф-я заполнения первого массива
    output_arr(arr, &row, &col); //ф-я вывода первого массива

    k = compute(&row, &col, arr, k); // нахождение элементов главной диагонали 
    if (k == 0) {
        std::cout << "На главной диагонали нет четных элементов\n";
        return 0;
    }

    /* создание второго массива и его заполнение */
    int* mass = new int[k];
    filling_mass(mass, &row, arr); //ф-я заполнения массива
    output_mass(mass, k);// вывод второго массива

    std::cout << "\nПроизведение четных элементов массива = " << mass_prod(mass, prod, k) << std::endl;

    /* удаление массивов */
    for (int i = 0; i < k; i++) {
        delete[] arr[i];
    }
    delete[] arr;
    delete[] mass;

	return 0;
}