// ������������ 6, ������ 1(������� 10). ���������: ������ �.�.
/* ���� ������ ��������, ��������� �� ����, ����������� ���������. ������� ������ ����� ���� ������ */
#include<iostream>
#include<stdio.h>
#include<string.h>
#include<Windows.h>

int main() {
    SetConsoleCP(1251); //����� ���������
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "rus");
    char str[80];
    char* p = str;
    
    std::cout << "��������� ������� ������ ����� ����� ������.\n������� ������: ";
    std::cin.getline(str, '.');
   //std::cout << str << std::endl;

    p = strtok(str, " ");
    std::cout << "������ ����� ����� ������: ";
    while (p) {
        if (p[strlen(p) - 1] % 2 == 0) {
            std::cout << p << " ";
        }
        p = strtok(NULL, " ");
    }
    std::cout << '\n';
    return 0;
}