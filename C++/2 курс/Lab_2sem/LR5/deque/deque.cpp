#include <iostream>
#include "deque.h"
#include <deque>
#include <iterator>

int main() {
	std::deque<int> a;
	for (int i = 0; i < 15; i++) {
		a.push_back(i);
	}

	auto it = std::deque<int>::iterator(a.begin());
	std::cout << *it <<"\n";

	a.resize(500, 5);
	std::cout << *it << "\n";
}
