// ������������ 6, ������ 6. ���������: ������ �.�.
/* �������� ���������, ������� ������� ���������� ��������� ��������, ������� ����� ���������� a�� ����� �����. */
#include<map>
#include<string>
#include<iostream>
#include<Windows.h>
#include "../static_libs/ststic_libs.h"
using namespace std;

int main() {
    SetConsoleCP(1251); //����� ���������
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "rus");
    std::cout << "��������� ������� ���������� ��������� ��������, ������� ����� ���������� �� �����.\n������� ���� �����: ";
    string word;
    getline(cin, word);
   

    std::cout << "\n���� �����: " << word << std::endl;
    std::cout << "���������� �������� - " << anagrams(word) << std::endl;

    return 0;
}