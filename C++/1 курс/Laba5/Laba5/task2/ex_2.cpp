// Лабораторная 5, задача 2. Выполнена: Скроба А.П.

#include<iostream>
#include<cmath>
#include<ctime>
#include<Windows.h>

/* проверка на ввод */
int input() {
	while (true) {
		int value;

		std::cin >> value;

		if (std::cin.fail() && value < 0) {
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

int main() {
	setlocale(LC_ALL, "rus");
	srand(time(0));

	HINSTANCE load;
	load = LoadLibrary(L"D:/С++/Laba5/StaticLib/Debug/DynamicLib.dll"); // помещение модуля библиотеки в память процессора
	typedef int (*Account) (int*, int, double); //тип указателя на ф-ю
	Account account;
	account = (Account)GetProcAddress(load, "account"); //получение адресов ф-ий

	int size, i = 0;
	double one_third, two_third;
	
	std::cout << "Введите размер массива: ";
	std::cin >> size;

	int* arr = new int[size];
	std::cout << "Введите целочисленные(!) элементы массива: \n";
	for (int i = 0; i < size; i++) {
		//std::cout << "[" << i + 1 << "]" << " ";
		//arr[i] = input();
		//std::cin >> arr[i];
		arr[i] = rand() % 50 - 30;
	}

	std::cout << "\nВаш массив: ";
	for (int i = 0; i < size; i++) {
		std::cout << arr[i] << " ";
	}

	one_third = (double)size / 3.;
	//if (one_third > (int)one_third + 0.5) one_third += 1;
	two_third = 2. * (double)size / 3.;
	//if (two_third > (int)two_third + 0.5) two_third += 1;

	std::cout << "\nЭлементы удовлетворяющие условию: ";
	i = account(arr, i, one_third);
	account(arr, i, two_third);
	std::cout << std::endl;

	FreeLibrary(load);
	delete[] arr;
	return 0;
}