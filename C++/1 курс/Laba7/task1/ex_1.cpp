// ������������ 7, ������ 1(������� 10). ���������: ������ �.�.

/* �� ���������� � ���������������� (� ��������) */

#include<iostream>

int input_num() {
    while (true) {
        int value;

        std::cin >> value;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(32767, '\n');
            std::cout << "������������ ����\n������� ����� � ���������� ������� ���������(����� �� 0 �� 9): ";
        }
        else {
            std::cin.ignore(32767, '\n');
            return value;
        }
    }
}

int main() {
	setlocale(LC_ALL, "rus");
	std::cout << "��������� ������������ ������� ����� �� ���������� � ���������������� ������� ��������� (� ��������).";
    std::cout << "\n������� ����� � ���������� ������� ���������: ";
    int num = input_num(); //����� � ���������� ��
    int n = num;
    int count = 0, add; //���-�� ���� � �����

        int count_1 = 0, ten = 0;;
        do {
            int d = num % 10;
            num /= 10;

            ten += d * powl(9, count_1);

            count_1++;
            count--;
        } while (num);
        std::cout << "����� � ���������� ��: " << ten << std::endl;

        int k1 = 10, k2 = 11, t = 8, z, i, ss = 17;
        char ms[20]; 
        z = ten; 
        ten -= z;
        while (z >= ss) 
        {
            i = z % ss; 
            z /= ss; 
            ms[k1--] = i > 9 ? i - 10 + 'A' : i + '0';
        } 
        ms[k1--] = z > 9 ? z - 10 + 'A' : z + '0';
        ms[k1] = ' ';
        ms[k2++] = '.'; 
        while (ten != 0 && k2 - 11 <= t) {
            ten *= ss;
            i = ten; 
            ms[k2++] = i > 9 ? i - 10 + 'A' : i + '0'; 
            ten -= i;
        }
        std::cout << "\n���� �����:";
        for (i = k1; i < k2; i++)
            std::cout << ms[i]; 


    std::cout << std::endl;

	return 0;
}