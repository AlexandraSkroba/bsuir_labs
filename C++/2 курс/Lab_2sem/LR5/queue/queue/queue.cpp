#include <iostream>
#include <queue>
#include "queue.h"
#include <deque>

int main() {
	std::deque<int> deq;
	queue<int> a;
	a.push(1);
	a.push(2);
	a.push(3);
	auto it = queue<int>::Iterator(a.front());
	it++;
	a.pop();
	std::cout << *it;
	return 0;
}