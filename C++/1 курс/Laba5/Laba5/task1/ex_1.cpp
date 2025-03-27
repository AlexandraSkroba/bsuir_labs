// Лабораторная 5, задача 1. Выполнена: Скроба А.П.

#include<iostream>
#include<cmath>
#include<vector>
#include "../../StaticLib/StaticLib/StaticLib.h";

int main() {
    int arr_size;
    std::cout << "Enter array size: ";
    arr_size = input() + 1;

    std::vector<double> arr_num(arr_size);

    for (int i = 0; i < arr_num.size(); i++) {
        arr_num[i] = i;
    }
    std::cout << "\n";

    arr_num_math(arr_num, arr_size);
    arr_num_change(arr_num, arr_size); std::cout << "\n";

    return 0;
}