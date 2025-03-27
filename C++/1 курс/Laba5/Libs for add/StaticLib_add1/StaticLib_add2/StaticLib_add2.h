#pragma once
#include<cmath>

unsigned long long power(unsigned long long t) {
	int m = 1; for (int i = 0; i < t; i++) m *= 10;
	return m;
}

unsigned long long calculations(unsigned long long k, unsigned long long n, unsigned long long m) {
	k = k % m;
	if (!n) return 1;
	if (n & 1) return (k * calculations((k * k) % m, n / 2, m)) % m;
	return calculations((k * k) % m, n / 2, m);
}
