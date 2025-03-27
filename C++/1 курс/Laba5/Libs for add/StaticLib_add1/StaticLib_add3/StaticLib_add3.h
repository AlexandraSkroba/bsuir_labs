#pragma once
long function(long n) {
    long long k = (n + 1) / 2;
    if (n == 0) return 0;
    return k * k + function(n / 2);
}