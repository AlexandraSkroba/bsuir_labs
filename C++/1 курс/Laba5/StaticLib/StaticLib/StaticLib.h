#pragma once
#include<iostream>
#include<vector>
#define e 2.718281
#define p 3.141592

int input() {
    while (true) {
        int array_size;

        std::cin >> array_size;

        if (std::cin.fail() || array_size < 0) {
            std::cin.clear();
            std::cin.ignore(32767, '\n');
            std::cout << "Error\nPlease enter a positive number: ";
        }
        else {
            std::cin.ignore(32767, '\n');
            return array_size;
        }
    }
}


/* функция вывода массива */
void arr_output(std::vector<double>& arr_num, int arr_size) {
    for (int i = 0; i < arr_num.size(); i++) {
        std::cout << arr_num[i] << " ";
    }
}

/* функция вычисления массива */
void arr_num_math(std::vector<double>& arr_num, int arr_size) {
    double n;
    std::cout << "Your array: ";

    for (int i = 0; i < arr_num.size(); i++) {
        n = -0.5 * i - 2 * p;
        arr_num[i] = pow(e, n) - atan(i + 0.1);
    }
    arr_output(arr_num, arr_size);
}

/* функция модификации массива */
void arr_num_change(std::vector<double>& arr_num, int arr_size) {
    std::cout << "\nModified array: ";
    for (int i = 0; i < arr_num.size(); i++) {
        if (arr_num[i] > 0) arr_num[i] = 0.1;
        if (arr_num[i] < 0) arr_num[i] += 0.5;
    }
    arr_output(arr_num, arr_size);
}