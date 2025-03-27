// ������������ 5, ������ 3_1. ���������: ������ �.�.

/* ��� ��������� ������������ ������ ����� ����� � ������������ n * k .
����������� ������� (n = 5, k = 6) ������ � ����������. �������� ��������� �������
������ � ����������. ������� ������������ ������ �� ���������, ������������� ��
������� ��������� ������� � ������� ������ ��������. ��������� ������������
��������� ������������� �������.
��������� ������ � ��������� ������������ ������� �� �����.
������������ �������. */

#include<iostream>
#include<cstdlib>

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

/* ���������� ������� ������������� ������� */
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

/* ����� ������� ���������� ������������� ������� */
void output_arr(int** arr, int *row, int *col) {
    std::cout << "\n���� �������:" << std::endl;
    for (int i = 0; i < *row; i++) {
        for (int j = 0; j < *col; j++) {
            std::cout << arr[i][j] << "\t";
        }
        std::cout << "\n\n";
    }
}

/* ���������� ������� ������������� ������� */
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

/* ����� ������� ���������� ������������� ������� */
void output_mass(int *mass, int k) {
    std::cout << "������ ������ ��������� ������� ���������: ";
    for (int p = 0; p < k; p++) {
        std::cout << mass[p] << " ";
    }
}

/* ���������� ������� ������� ������� */
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
        if (row != col) std::cout << "������� ��������� ����� ����� ������ � ���������� �������!\n" << std::endl;
    } while (row != col);

    /* �������� � ���������� ������� ������� */
    int** arr = new int* [row];
    for (int i = 0; i < row; i++) {
        arr[i] = new int[col];
    }

    input_arr(arr, &row, &col); //�-� ���������� ������� �������
    output_arr(arr, &row, &col); //�-� ������ ������� �������

    k = compute(&row, &col, arr, k); // ���������� ��������� ������� ��������� 
    if (k == 0) {
        std::cout << "�� ������� ��������� ��� ������ ���������\n";
        return 0;
    }

    /* �������� ������� ������� � ��� ���������� */
    int* mass = new int[k];
    filling_mass(mass, &row, arr); //�-� ���������� �������
    output_mass(mass, k);// ����� ������� �������

    std::cout << "\n������������ ������ ��������� ������� = " << mass_prod(mass, prod, k) << std::endl;

    /* �������� �������� */
    for (int i = 0; i < k; i++) {
        delete[] arr[i];
    }
    delete[] arr;
    delete[] mass;

	return 0;
}