// ������������ 4, ������ 13. ���������: ������ �.�.

/* � ���� � ��������� ����� ���� 1 �������. ���� ��������� ��� �������������, 
���� ����� N ����������� �����, ��� i-� ���������� ����� a[i] ������. 
���������, ������� ������� ��������� � ����, ���� �� ���������� �������� ����������?*/

#include<iostream>

int main() {
	int size;

	do {
		std::cout << "Enter the number of extension cords: ";
		std::cin >> size;

		if (std::cin.fail()) {
			std::cin.clear();
			std::cin.ignore();
			std::cout << "\nInvalid input.\n" << std::endl;
		}

		if (size <= 0) std::cout << "The size of the array cannot be <= 0.\n";
	} while (size <= 0);

	int sock = 1, num = 0;
	int* arr = new int[size];
	for (int i = 0; i < size; i++) {
		arr[i] = i+1;
		sock += num;
		num = arr[i];
	}

	std::cout << "Number of sockets: " << sock << std::endl;

	return 0;
}