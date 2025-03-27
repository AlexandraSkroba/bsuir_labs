// ������������ 6, ������ 2(������� 10). ���������: ������ �.�.
/* � ������ ����� � ������� �� ����� ��� ����� ������������ � ����������� �����. */
#include<iostream>
#include<Windows.h>

int main() {
	SetConsoleCP(1251); //����� ���������
	SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "rus");
	std::cout << "��������� ������� �� ����� ��� ����� ������������ � ����������� �����.\n������� ������:";
	int maxN = 2;
	char* str = (char*)malloc(maxN * sizeof(char));
	int length;
	for (length = 0; '\n' - (str[length] = getchar()); ++length) {
		if (length == maxN - 1) {
			str = (char*)realloc(str, (maxN *= 2) * sizeof(char));
		}
	}
	str = (char*)realloc(str, (length + 1) * sizeof(char));
	str[length] = '\0';
	int maxLength = 0, counter = 0, minLength = 1e9;

	for (int i = 0; i < length; i++) {
		if (str[i] != ' ')
			++counter;
		else {
			if (counter > maxLength)
				maxLength = counter;
			if (counter > 0 && counter < minLength)
				minLength = counter;
			counter = 0;
		}
	}
	if (counter > maxLength)
		maxLength = counter;
	if (counter > 0 && counter < minLength)
		minLength = counter;

	int temp = 0, start = 0;

	std::cout << std::endl;
	std::cout << "������������ �����: ";

	for (int i = 0; i < length; i++) {
		if (!start || str[i - 1] == ' ') {
			temp = 0;
			for (int j = i; str[j] != ' ' && str[j] != '\0'; j++) {
				++temp;
			}
		}
		if (temp == maxLength) {
			std::cout << str[i];
		}
		++start;
	}
	start = 0;

	std::cout << std::endl;
	std::cout << "����������� �����: ";

	for (int i = 0; i < length; i++) {
		if (!start || str[i - 1] == ' ') {
			temp = 0;
			for (int j = i; str[j] != ' ' && str[j] != '\0'; j++) {
				++temp;
			}
		}
		if (temp == minLength) {
			std::cout << str[i];
		}
		++start;
	}
	std::cout << "\n";

	free(str);
	return 0;
}