// ������������ 6, ������ 7. ���������: ������ �.�.

/* � �������� ������ S ����� ������������ �� ����� ���������, ������� �� �������� ����������� */

#include <iostream>
#include<Windows.h>
#include "../static_libs/ststic_libs.h"

int main() {
    SetConsoleCP(1251); //����� ���������
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "rus");
    std::string s;
    int count = 0;
    std::cout << "��������� � �������� ������ S ������� ������������ �� ����� ���������, ������� �� �������� �����������.\n������� ������: ";
    std::cin >> s;
    
    amount(s, count);

    std::cout << "\n";
    return 0;
}