// ������������ 5, ������ �������������� 1 :/. ���������: ������ �.�.

#include<iostream>
#include "../../Libs for add/StaticLib_add1/StaticLib_add1/StaticLib_1.h"

/* �������� �� ���� */
long input() {
    while (true) {
        long double value;

        std::cin >> value;

        if (std::cin.fail() || value - (long int)value != 0) {
            std::cin.clear();
            std::cin.ignore(32767, '\n');
            std::cout << "\n������\n������� ����� ����������� ����� - ";
        }
        else {
            std::cin.ignore(32767, '\n');
            return value;
        }
    }
}

long main() {
    setlocale(LC_ALL, "rus");
    int p, q;
    
    std::cout << "������� ��� ����� ������������� �����(p � q, ��� p <= q) � ��� ������������� ���� ������ ��������� ���������: \n";
	while (true) {
        do {
           std::cin >> p;
            std::cin >> q;

            if (std::cin.fail()) {
                std::cin.clear();
                std::cin.ignore();
                std::cout << "\nInvalid input.\n" << std::endl;
                std::cin.clear();
            }

            if ((p < 0 && q >= 0) || (q < 0 && p >= 0) || (p > q)) std::cout << "\n��� ����� ������ ���� �������������� (��� ��������������, ���� �� ������ ����� �� ���������)\n� p ������ ���� ������ ��� ��������� q\n";
        } while ((p < 0 && q >= 0) || (q < 0 && p >= 0) || (p > q));
        if (p < 0 && q < 0) break;

        compute(p);
        std::cout << "��������� ���������� = " << sum(p, q) << std::endl;
	}

	return 0;
}