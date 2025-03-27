// ������������ 7, ������ 7. ���������: ������ �.�.

/* ���������� ����������� ���������, ������� ���������, 
������� �� ��������� ������������� ����� �� �������� �������. 
��������� �� ������ ��������� �������� ���������, �������, ��������� (� ��� ����� ������ ������� �� �������) */

#include<iostream>
#include<string>
#include<iomanip>

bool multiplieByThree(int number) {
	int num = 0;
	for (int i = 0; num < number; i++)
	{
		num = (i << 1) + i;
	}
	if (num == number)
		return true;
	return false;
}

int inputInt(int minValue, int maxValue) {

	double x;
	while (true)
	{
		std::cin >> x;
		if (!std::cin.fail() && x <maxValue && x > minValue)
			return (int)x;
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << "Enter corect value" << std::endl;
	}
}

bool multiplieByFourtySeven(int number) {
	int num = 0;
	for (int i = 0; num < number; i++)
	{
		num = (i << 5) + (i << 3) + (i << 2) + (i << 1) + i;
	}
	if (num == number)
		return true;
	return false;
}
bool multiplieByBigValue(int number) {
	int num = 0;
	for (int i = 0; num < number; i++)
	{
		num = (i << 7) + (i << 6) + (i << 2) + i;
	}
	if (num == number)
		return true;
	return false;
}

int main() {
	setlocale(LC_ALL, "rus");

	std::cout << "��������� ��������� ������� �� ��������� ������������� ����� �� 3, 47, 197.\n������� �����: ";
	int number = inputInt(0, INT_MAX);

	std::cout << std::boolalpha << "\n������� �� 3 - " << multiplieByThree(number) << "\n������� �� 47 - " << multiplieByFourtySeven(number) << "\n������� �� 197 - " << multiplieByBigValue(number) << std::endl;
	return 0;
}