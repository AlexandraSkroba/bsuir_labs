// Лабораторная 7, задача 2(вариант 10). Выполнена: Скроба А.П.

/* Из прямого кода в дополнительный */

#include<iostream>
#include<string>
#include<bitset>
#include<stdlib.h>
using namespace std;

string dop_code(string str) {

	int count = 7, count_1 = 0;
	if (str[count] == '0') {
		str[count] = '1';
	}
	else if (str[count] == '1') {
		while (str[count] != '0') {
		str[count] = '0';
		count--;
		count_1++;
	}
		str[count_1 + 1] = '1';
	}

	return str;
}

	int main() {
		setlocale(LC_ALL, "rus");
		int num_1; char sign_1;

		cout << "Введите знак числа (+ или -): ";
		cin >> sign_1;
		cout << "Введите число в десятичной сс: ";
		cin >> num_1;
		bitset<8> byte_1(num_1);

		// преобразовать объекты bitset в строку-объект
		string str_1 = byte_1.to_string<char, char_traits<char>, allocator<char> >();

		cout << "Первое число в двоичной сс: " << str_1 << endl;

		// преобразование в обратный код и дополнительный
		if (sign_1 == '-') {
			string str_1 = byte_1.flip().to_string<char, char_traits<char>, allocator<char> >();
			//cout << "\nПервое число отрицательное, обратный код: " << str_1 << endl;
			str_1 = dop_code(str_1);
			cout << "Первое число в дополнительном коде: " << str_1 << endl;
		}
		else if (sign_1 == '+') {
			cout << "Первое число в дополнительном коде: " << str_1 << endl;
		}
		
		return 0;
	}