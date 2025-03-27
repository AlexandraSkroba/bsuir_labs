// Лабораторная 5, задача 3_3. Выполнена: Скроба А.П.

/* Дан двумерный динамический массив целых чисел. Значения элементов данного
массива ввести с клавиатуры. Создать динамический массив из элементов,
расположенных в четных столбцах данного массива и имеющих нечетное значение.
Вычислить среднее арифметическое элементов динамического массива.
Вывести результат на экран.
Использовать функции. */

#include<iostream>

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

        if (std::cin.fail() || element - (int)element != 0) {
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

/* создание и заполнение массива */
void create_arr(long int** arr, int row, int col) {
    for (int i = 0; i < row; i++) {
        arr[i] = new long int[col];
    }
    std::cout << "Enter value of matrix: \n";
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            //std::cout << "[" << i << "]" << "[" << j << "] ";
            //arr[i][j] = input_arr();
            arr[i][j] = rand() % 9;
        }
    }
}

/* вывод массива */
void output_arr(long int **arr, int row, int col) {
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            std::cout << arr[i][j] << "\t";
        }
        std::cout << "\n\n";
    }
}

/* нахождение четных элементов массива в нечетных столбцах */
int odd_elements_even_columns(long int** arr, int row, int col, int count) {
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            if (arr[i][j] % 2 != 0) {
                count++;
            }
            j++;
        }
    }
    return count;
}

/* вывод четных элементов массива в нечетных столбцах */
void output_odd_elements_even_columns(long int **arr, double *mass, int row, int col, int count) {
    for (int i = 0, num = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            if (arr[i][j] % 2 != 0) {
                mass[num++] = arr[i][j];
            }
            j++;
        }
    }

    for (int i = 0; i < count; i++) {
        std::cout << mass[i] << " ";
    }
}

/* среднее арифметическое */
int average(double *mass, int num, int count) {
    for (int i = 0; i < count; i++) {
        num += mass[i];
    }
    return num;
}

int main() {
    setlocale(LC_ALL, "rus");
    int row, col, count = 0, num = 0;
    std::cout << "Введите количество строк массива - ";
    row = input();
    std::cout << "Введите количество столбцов массива - ";
    col = input();

    /* создание и заполнение массива */
    long int** arr = new long int* [row];
    create_arr(arr, row, col);

    std::cout << "\nВаш массив: \n";
    output_arr(arr, row, col);

    std::cout << "Нечетные элементы четных столбцов:";
    count = odd_elements_even_columns(arr, row, col, count);

    double* mass = new double[count];
    output_odd_elements_even_columns(arr, mass, row, col, count);

    /* среднее арифметическое */
    average(mass, num, count);
    num = average(mass, num, count);
    std::cout << "\nСреднее арифметическое элементов массива - " << (double)num / (double)count << std::endl;

    /* удаление массивов */
    for (int i = 0; i < row; i++) {
        delete[] arr[i];
    }
    delete[] arr;

	return 0;
}