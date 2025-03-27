// Лабораторная 6, задача 8. Выполнена: Скроба А.П.
#include <iostream>
#include "../static_libs/ststic_libs.h"

int main() {
	setlocale(LC_ALL, "rus");
	std::cout << "Введите количество наборов входных данных:" << std::endl;
	const int size = 11;
	int n;
	std::cin >> n;
	std::cout << "Введите две строки (s и t): ";
	while (n > 0) {
		char s[size], t[size];
		std::cin >> s >> t;
		std::cout << result(s, t);
		-n;
	}
	return 0;
}