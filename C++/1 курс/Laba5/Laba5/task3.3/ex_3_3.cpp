// ������������ 5, ������ 3_3. ���������: ������ �.�.

/* ��� ��������� ������������ ������ ����� �����. �������� ��������� �������
������� ������ � ����������. ������� ������������ ������ �� ���������,
������������� � ������ �������� ������� ������� � ������� �������� ��������.
��������� ������� �������������� ��������� ������������� �������.
������� ��������� �� �����.
������������ �������. */

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

/* �������� �� ���� ��������� ������� */
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

/* �������� � ���������� ������� */
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

/* ����� ������� */
void output_arr(long int **arr, int row, int col) {
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            std::cout << arr[i][j] << "\t";
        }
        std::cout << "\n\n";
    }
}

/* ���������� ������ ��������� ������� � �������� �������� */
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

/* ����� ������ ��������� ������� � �������� �������� */
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

/* ������� �������������� */
int average(double *mass, int num, int count) {
    for (int i = 0; i < count; i++) {
        num += mass[i];
    }
    return num;
}

int main() {
    setlocale(LC_ALL, "rus");
    int row, col, count = 0, num = 0;
    std::cout << "������� ���������� ����� ������� - ";
    row = input();
    std::cout << "������� ���������� �������� ������� - ";
    col = input();

    /* �������� � ���������� ������� */
    long int** arr = new long int* [row];
    create_arr(arr, row, col);

    std::cout << "\n��� ������: \n";
    output_arr(arr, row, col);

    std::cout << "�������� �������� ������ ��������:";
    count = odd_elements_even_columns(arr, row, col, count);

    double* mass = new double[count];
    output_odd_elements_even_columns(arr, mass, row, col, count);

    /* ������� �������������� */
    average(mass, num, count);
    num = average(mass, num, count);
    std::cout << "\n������� �������������� ��������� ������� - " << (double)num / (double)count << std::endl;

    /* �������� �������� */
    for (int i = 0; i < row; i++) {
        delete[] arr[i];
    }
    delete[] arr;

	return 0;
}