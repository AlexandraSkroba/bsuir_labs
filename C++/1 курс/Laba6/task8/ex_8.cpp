// ������������ 6, ������ 8. ���������: ������ �.�.
#include <iostream>
#include "../static_libs/ststic_libs.h"

int main() {
	setlocale(LC_ALL, "rus");
	std::cout << "������� ���������� ������� ������� ������:" << std::endl;
	const int size = 11;
	int n;
	std::cin >> n;
	std::cout << "������� ��� ������ (s � t): ";
	while (n > 0) {
		char s[size], t[size];
		std::cin >> s >> t;
		std::cout << result(s, t);
		-n;
	}
	return 0;
}