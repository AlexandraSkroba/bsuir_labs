// Лабораторная 7, задача 3(вариант 10). Выполнена: Скроба А.П.

/* Найдите сумму двоичных чисел, заданных в естественной форме. 
Сложение выполните в дополнительном коде. Ответ выразите в естественной форме */

#include <iostream>
#include <string>
#include <bitset>
using namespace std;

string sum(string str_1, string str_2) {
	int meter = 7;
	while (meter > 0) {
		if ((str_1[meter] == '1' && str_2[meter] == '0') || (str_1[meter] == '0' && str_2[meter] == '1')) {
			str_1[meter] = '1';
		}
		else if (str_1[meter] == '1' && str_2[meter] == '1') {
			while (str_1[meter] != '0' && str_2[meter] != '0') {
				str_1[meter] = '0';
			}
			str_1[meter - 1] = '1';
		}
		meter--;
	}

	cout << "\nРезультат сложения чисел: " << str_1 << endl;
	return str_1;
}

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
	int num_1, num_2;

	char sign_1, sign_2;
	cout << "Введите знак первого числа (+ или -): ";
	cin >> sign_1;
	cout << "Введите первое число в десятичной сс: ";
	cin >> num_1;
	bitset<8> byte_1(num_1);

	cout << "\nВведите знак второго числа (+ или -): ";
	cin >> sign_2;
	cout << "Введите второе число в десятичной сс: ";
	cin >> num_2;
	bitset<8> byte_2(num_2);

	// преобразовать объекты bitset в строку-объект
	string str_1 = byte_1.to_string<char, char_traits<char>, allocator<char> >();
	string str_2 = byte_2.to_string<char, char_traits<char>, allocator<char> >();

	cout << "Первое число в двоичной сс: " << str_1 << endl;
	cout << "Второе число в двоичной сс: " << str_2 << endl;

	if (num_1 == num_2 && ((sign_1 == '+' && sign_2 == '-') || (sign_1 == '-' && sign_2 == '+'))) {
		cout << "\nРезультат сложения чисел: " << "00000000" << endl;
		return 0;
	}

	// преобразование в обратный код и дополнительный
	if (sign_1 == '-' && sign_2 == '-') {
		string str_1 = byte_1.flip().to_string<char, char_traits<char>, allocator<char> >();
		//cout << "\nПервое число отрицательное, обратный код: " << str_1 << endl;
		str_1 = dop_code(str_1);

		string str_2 = byte_2.flip().to_string<char, char_traits<char>, allocator<char> >();
		//cout << "\nВторое число отрицательное, обратный код: " << str_2 << endl;
		str_2 = dop_code(str_2);

		sum(str_1, str_2);
	}
	if (sign_1 == '-') {
		string str_1 = byte_1.flip().to_string<char, char_traits<char>, allocator<char> >();
		//cout << "\nПервое число отрицательное, обратный код: " << str_1 << endl;
		str_1 = dop_code(str_1);
		//cout << "Первое число в дополнительном коде: " << str_1 << endl;
		sum(str_1, str_2);
	}
	if (sign_2 == '-') {
		string str_2 = byte_2.flip().to_string<char, char_traits<char>, allocator<char> >();
		//cout << "\nВторое число отрицательное, обратный код: " << str_2 << endl;
		str_2 = dop_code(str_2);
		//cout << "Второе число в дополнительном коде: " << str_2 << endl;
		sum(str_1, str_2);
	}
	if (sign_1 == '+' && sign_2 == '+') {
		sum(str_1, str_2);
	}

	return 0;
}