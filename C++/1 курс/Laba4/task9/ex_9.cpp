// Лабораторная 4, задача 9. Выполнена: Скроба А.П.

/*В качестве входных данных поступают две целочисленные матрицы A и B, 
которые имеют размер N и соответственно. Требуется найти произведение матриц A*B. 
Выделение памяти через функции языка С.*/

#include <iostream>
#include <stdlib.h>

int input() {
	while (true) {
		int value;

		std::cin >> value;

		if (std::cin.fail() || value < 1) {
			std::cin.clear();
			std::cin.ignore(32767, '\n');
			std::cout << "Error\nEnter the number: ";
		}
		else {
			std::cin.ignore(32767, '\n');
			return value;
		}
	}
}

int main() 
{
	int n;
	std::cout << "size_all_matrix: ";
	std::cin >> n;
	
	int** arr = (int**)calloc(n, sizeof(int*));
	std::cout << "\nEnter the values of the first matrix" << std::endl;
	for ( int i = 0; i < n; i++){
		arr[i] = (int*)calloc(n, sizeof(int));
		for (int j = 0; j < n; j++) {
			arr[i][j] = input();
		}
	}

	std::cout << "\nMatrix 1" << std::endl;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			std::cout << arr[i][j] << '\t';
		}
		std::cout << std::endl;
	}

	std::cout << "\nEnter the values of the second matrix" << std::endl;
	int** ptr = (int**)calloc(n, sizeof(int*));
	for (int i = 0; i < n; i++) {
		ptr[i] = (int*)calloc(n, sizeof(int));
		for (int j = 0; j < n; j++) {
			 ptr[i][j] = input();
		}
	}

	std::cout << "\nMatrix 2" << std::endl;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			std::cout << ptr[i][j] << '\t';
		}
		std::cout << std::endl;
	}

	int** result = (int**)calloc(n, sizeof(int*));
	for (int i = 0; i < n; i++){
		result[i] = (int*)calloc(n, sizeof(int));
		for (int j = 0; j < n; j++) {
			result[i][j] = 0;
			for (int r = 0; r < n; r++)
				result[i][j] += arr[i][r] * ptr[r][j];
		}
	}

	std::cout << "\nMultiplied matrix";
	std::cout << std::endl;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			std::cout << result[i][j] << '\t';
		}
		std::cout << std::endl;
	}

	free(arr);
	free(ptr);
	free(result);
	return 0;
}