// ������������ 7, ������ 6. ���������: ������ �.�.

#include <iostream>

int main() {
    setlocale(LC_ALL, "rus");

    long long int t;

    std::cout << "������� ���-�� �������: ";
    std::cin >> t;

    while (t--) {
        long long int x;

        std::cout << "\n������� �����: ";
        std::cin >> x;

        std::cout << (x + 1) / 10 << std::endl;
    }

    return 0;
}