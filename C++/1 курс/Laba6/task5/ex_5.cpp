#include<iostream>
#include<string>
#include"../static_libs/ststic_libs.h"

int main() {
	int counter = inputInt(0, 101);
	while (counter > 0)
	{
		int L = inputInt(0, 10e9 + 1), m = inputInt(0, 10e4 + 1);
		std::string s1, s2;
		std::cin.ignore(32767, '\n');
		std::getline(std::cin, s1);
		std::getline(std::cin, s2);

		std::cout << findWordAmount(L, m, s1, s2);
		--counter;
	}
}