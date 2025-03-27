// Лабораторная 4, задача 12. Выполнена: Скроба А.П.

/* Написать функцию которая будет удалять дубликаты элементов из массива. 
Входные параметры: массив, длинна массива. Выходные параметры: новый массив, новый размер.*/

#include<iostream>

void del_arr(int arr[], int n) {
	int n1 = 0;
	for (int i = 0; i < n; ++i) {
		int currentElementValue = arr[i];
		bool hasEquals = false;

		for (int r = 0; r < n; ++r) {
			if (i == r) {
				arr[i] = 0;
				continue;
			}
			if (currentElementValue == arr[r] && i != r) {
				hasEquals = true;
			}
		}

		if (!hasEquals) {
			std::cout << currentElementValue << " ";
			n1++;
		}
	}

	std::cout << "\nThe length of the new array: " << n1 << std::endl;
}

int main() {
	int n; 

	do {
		std::cout << "Enter the size of the array: ";
		std::cin >> n;

		if (std::cin.fail()) {
			std::cin.clear();
			std::cin.ignore();
			std::cout << "\nInvalid input.\n" << std::endl;
		}

		if (n <= 0) std::cout << "The size of the array cannot be <= 0.\n";
	} while (n <= 0);


	std::cout << "Enter " << n << " elements of the array: ";
	int *arr = new int [n];
	for (int i = 0; i < n; i++) {
		std::cin >> arr[i];
	}

	std::cout << "\nArray without repeating elements: ";
	del_arr(arr, n);

	delete[] arr;
	return 0;
}