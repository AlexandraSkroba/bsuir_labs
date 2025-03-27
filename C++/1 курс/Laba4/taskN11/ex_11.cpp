// ������������ 4, ������ 11. ���������: ������ �.�.

/* ��� ��������� ������������ ������ �������� n^3 ����� ��������������� �����.
���������� ���������� ��������� � ���������� ������ �����. 
��� ������ ���������� ������ ������������ ��������� �����.*/

#include<iostream>
#include<ctime>
using namespace std;

int main() {
        setlocale(LC_ALL, "Rus");

        int size, d1 = 0, d2 = 0, d3 = 0, d4 = 0, max, k, diagonal[4];

        cout << "������� ������ ����: ";
        cin >> size;

        /* ���������� � ���������� ������� */
        int*** arr = new int** [size];
        for (int i = 0; i < size; i++) {
            arr[i] = new int* [size];
            for (int j = 0; j < size; j++) {
                arr[i][j] = new int[size];
            }
        }

        for (int z = 0; z < size; z++)
            for (int y = 0; y < size; y++)
                for (int x = 0; x < size; x++)
                    arr[z][y][x] = rand() % 20;

        for (int z = 0; z < size; z++) {
            cout << "\nslice " << z << endl;
            for (int y = 0; y < size; y++) {
                for (int x = 0; x < size; x++) {
                    cout << arr[z][y][x] << '\t';
                }
                cout << '\n';
            }
        }

        /* ���������� ���� ���������� � �� ���������� */
        k = size;
        for (int i = 0; i < size; i++) {
            d1 += arr[i][i][i];
        }

        for (int i = 0; i < size; i++, k--) {
            d2 += arr[i][i][k - 1];
            d3 += arr[i][k - 1][i];
            d4 += arr[i][k - 1][k - 1];
        }

        diagonal[0] = d1;
        diagonal[1] = d2;
        diagonal[2] = d3;
        diagonal[3] = d4;

        max = diagonal[0];

        for (int k = 1; k < 4; k++) {
            if (max < diagonal[k]) max = diagonal[k];
        }

        cout << "\n���������� ��������� - " << max << endl;

    /* �������� ������� */
    for (int i = 0; i < size; i++)
    {

        for (int j = 0; j < size; j++)
            delete arr[i][j];
    }

    delete[] arr;

	return 0;
}
