// ������������ 4, ������ 8. ���������: ������ �.�.

/*�������� ������ ��� ��������, ������� ��������� � ������� ����� ����������� � ������������
���������� (�� ������� ��). ���������� ��� �������� � ������� ���������. 
���� ����� ������� �������� ������� ����� ������� ����� ��������� ����, �� 
������� ��� ������� �������� �� ������� (c ����������� ������� ���������� ��������� ���������).*/

#include<iostream>
#include<cstdlib>

int main() {
	int a, i = 0, minIndex, maxIndex, dif, arrIndex, size = 0;
	//srand(time(0));

	std::cout << "Enter a: ";
	std::cin >> a;

	int* arr = new int[a];

	std::cout << "Enter array: ";
	for (int i = 0; i < a; i++) {
		//	std::cin >> arr[i];
		arr[i] = rand() % 10;
	}
	std::cout << std::endl;

	std::cout << "Your array: ";
	for (int i = 0; i < a; i++) {
		std::cout << arr[i] << " ";
	}
	std::cout << std::endl;

	int max = arr[0];
	for (int i = 0; i < a; i++) {
		if (arr[i] > max) {
			max = arr[i];
		}
	}
	std::cout << "max = " << max << std::endl;

	int min = arr[0];
	for (int i = 0; i < a; i++) {
		if (arr[i] < min) {
			min = arr[i];
		}
	}
	std::cout << "min = " << min << std::endl;

	/* ������� ������� min � max */
	while (i < a) {
		if (arr[i] == min) minIndex = i;
		i++;
	}

	i = 0;
	while (i < a) {
		if (arr[i] == max) maxIndex = i;
		i++;
	}

	/* �������������� ������ */
	if (minIndex < maxIndex) {
		dif = maxIndex - minIndex - 1;
		for (int i = 0; i < a; i++) {
			arrIndex = i;
			if (arrIndex <= minIndex + dif && arrIndex > minIndex) arr[i] = 0;
		}
	} else {
		dif = minIndex - maxIndex - 1;
		for (int i = 0; i < a; i++) {
			arrIndex = i;
			if (arrIndex <= maxIndex + dif && arrIndex > maxIndex) arr[i] = 0;
		}
	}

	std::cout << "\nYour array: ";
	for (int i = 0; i < a; i++) {
		std::cout << arr[i] << " ";
		if (arr[i] == 0) size++;
	}

	/* ���������� ������ ������� */
	if (size > a / 2) {
		std::cout << "\nYour new array (without zeros): ";
		for (int i = 0; i < a; i++) {
			if (arr[i] != 0) std::cout << arr[i] << " ";
		}
	}
	std::cout << std::endl;

	delete[] arr;
	return 0;
}