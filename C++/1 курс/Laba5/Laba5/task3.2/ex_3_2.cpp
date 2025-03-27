// ������������ 5, ������ 3_2. ���������: ������ �.�.

/* ������� ��������� ������������ ������ ������������ �����. ����������,
����������� �� ����� ��� �������� � ������� ���������. ���� ����������� �����
��������, �� ���������� �� ������� � ����� ����������. ����������� �������� �����
������� � �������� ������� � ������� �� �����.
������������ �������. */

#include<iostream>
using namespace std;

/* �������� �� ���� */
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

/* ���������� � ����� ������� */
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

    std::cout << "\n��� ������: \n";
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            std::cout << arr[i][j] << "\t";
        }
        std::cout << "\n\n";
    }
}

/* ���������� ������� ��������� ������� */
void arr_null(double **arr, int row, int col, int count) {
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            if (arr[i][j] == 0) {
                count++;
                std::cout << "������ " << count << " �������� �������� ������� - " << "[" << i << "]" << "[" << j << "]\n";
            }
        }
    }
    if (count > 0) std::cout << "���������� ������� ��������� � �������: " << count << std::endl;
    else std::cout << "� ������� ��� ������� ���������" << std::endl;
}

/* ����� ������� � �������� ������� */
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
    cout << "������� ���������� ����� �������: ";
    row = input();
    cout << "������� ���������� �������� �������: ";
    col = input();

    double** arr = new double* [row];
    create_arr(arr, row, col); // �������� � ���������� ������� 
    arr_null(arr, row, col, count); // ���������� ������� ��������� �������
 
    std::cout << "\n������ ��������: \n";
    arr_reverse(arr, row, col); // ����� ������� � �������� �������

    /* �������� �������� */
    for (int i = 0; i < row; i++) {
        delete[] arr[i];
    }
    delete[] arr;

	return 0;
}