// ������������ 6, ������ 9. ���������: ������ �.�.
/* � �������� ������, ��������� �� ����, ���� � ������ ��������, ������� ����� ���� �����. */

#include <iostream>
#include <string>
#include <cctype>
#include <cmath>
#include <Windows.h>
#include "../static_libs/ststic_libs.h"

using namespace std;

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "rus");

    long double buff, sum = 0;
    int fraction, ex;
    bool minus, exMinus;

   string input;

   cout << "������� ������: ";
   getline(cin, input);

   cout << "\n\n�����: " << Sum(input) << endl;

    return 0;
}