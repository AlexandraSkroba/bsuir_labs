// Лабораторная 5, задача дополнительная 2 :/. Выполнена: Скроба А.П.

#include<iostream>
#include<cmath>
#include "../../Libs for add/StaticLib_add1/StaticLib_add2/StaticLib_add2.h"

long main() {
	setlocale(LC_ALL, "rus");
	int cs = 1;
	long long int k = 1, n = 1, t = 1, res;

	while (k + n + t > 0) {
		std::cout << "Введите три числа: ";
		do {
			std::cin >> k;
			if (k < 0 || k > pow(10, 19)) std::cout << "\nЧисло k должно быть больше нуля и меньше десяти в девятнадцатой степени\n";
		} while (k < 0 || k > pow(10, 19));
		do {
			std::cin >> n;
			if (n < 0 || n > pow(10, 19)) std::cout << "\nЧисло n должно быть больше нуля и меньше десяти в девятнадцатой степени\n";
		} while (n < 0 || n > pow(10, 19));
		do {
			std::cin >> t;
			if (t < 0 || t > 10) std::cout << "\nЧисло t должно быть больше нуля и меньше десяти в девятнадцатой степени\n";
		} while (t < 0 || t > 10);

		if (k == 0 && n == 0 && t == 0) break;

		int m = power(t);
		res = calculations(k, n, m);

		std::cout << "Case #" << cs++ << ": " << res << std::endl << std::endl;
	}

	return 0;
}