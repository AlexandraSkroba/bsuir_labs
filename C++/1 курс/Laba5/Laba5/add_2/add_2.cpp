// ������������ 5, ������ �������������� 2 :/. ���������: ������ �.�.

#include<iostream>
#include<cmath>
#include "../../Libs for add/StaticLib_add1/StaticLib_add2/StaticLib_add2.h"

long main() {
	setlocale(LC_ALL, "rus");
	int cs = 1;
	long long int k = 1, n = 1, t = 1, res;

	while (k + n + t > 0) {
		std::cout << "������� ��� �����: ";
		do {
			std::cin >> k;
			if (k < 0 || k > pow(10, 19)) std::cout << "\n����� k ������ ���� ������ ���� � ������ ������ � ������������� �������\n";
		} while (k < 0 || k > pow(10, 19));
		do {
			std::cin >> n;
			if (n < 0 || n > pow(10, 19)) std::cout << "\n����� n ������ ���� ������ ���� � ������ ������ � ������������� �������\n";
		} while (n < 0 || n > pow(10, 19));
		do {
			std::cin >> t;
			if (t < 0 || t > 10) std::cout << "\n����� t ������ ���� ������ ���� � ������ ������ � ������������� �������\n";
		} while (t < 0 || t > 10);

		if (k == 0 && n == 0 && t == 0) break;

		int m = power(t);
		res = calculations(k, n, m);

		std::cout << "Case #" << cs++ << ": " << res << std::endl << std::endl;
	}

	return 0;
}