// Лабораторная 7, задача 6. Выполнена: Скроба А.П.

#include <iostream>

int main() {
    setlocale(LC_ALL, "rus");

    long long int t;

    std::cout << "Введите кол-во наборов: ";
    std::cin >> t;

    while (t--) {
        long long int x;

        std::cout << "\nВведите число: ";
        std::cin >> x;

        std::cout << (x + 1) / 10 << std::endl;
    }

    return 0;
}