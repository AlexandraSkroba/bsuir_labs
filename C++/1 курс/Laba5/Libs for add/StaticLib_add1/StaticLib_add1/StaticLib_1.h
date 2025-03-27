#pragma once
long compute(long p) {
    long n = p % 10;
    if (p == 0) return 0;
    return n * (1 + n) / 2 + p / 10 * 45 + compute(p / 10);
}

long sum(long p, long q) {
    return compute(q) - compute(p - 1);
}