// ������������ 3, ������ 8. ���������: ������ �.�.

/* ����� ���������� (��������� � ����� ������ �. ����������
(Michael F. Armstrong)), �� ����� �������� ��������������� ������� �
������������ ��������� ������������, � ��� �����, ������ ����� �����
����, ����������� � �������, ������ ���������� ����. ��������, ����������
����� ���������� � 153, ������� ����� 1^3 + 5^3 + 3^3 . �������� ���������,
������� ������� ��� ����� ���������� ������ 10^6 */

#include <iostream>  
using namespace std;
int main()
{
	setlocale(LC_ALL, "Rus");

    int num = 0;

    cout << "����� ���������: \n";

    while (num != powl(10, 6)) {
        int originalNum, remainder, n = 0, result = 0, power;

        ++num;

        originalNum = num;

        while (originalNum != 0) {
            originalNum /= 10;
            ++n;
        }
        originalNum = num;

        while (originalNum != 0) {
            remainder = originalNum % 10;
            power = round(pow(remainder, n));
            result += power;
            originalNum /= 10;
        }

        if (result == num)  cout << num << endl;
    }

    return 0;
}