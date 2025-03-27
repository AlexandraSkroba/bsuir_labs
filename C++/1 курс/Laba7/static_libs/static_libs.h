#pragma once
#include<string>
#include<iostream>
using namespace std;

//task 1
int nine_to_sev(int num) {
	int n = num;
	int count = 0, add; //кол-во цифр в числе

	int count_1 = 0, ten = 0;;
	do {
		int d = num % 10;
		num /= 10;

		ten += d * powl(9, count_1);

		count_1++;
		count--;
	} while (num);

	int k1 = 10, k2 = 11, t = 8, z, i, ss = 17;
	char ms[20];
	z = ten;
	ten -= z;
	while (z >= ss)
	{
		i = z % ss;
		z /= ss;
		ms[k1--] = i > 9 ? i - 10 + 'A' : i + '0';
	}
	ms[k1--] = z > 9 ? z - 10 + 'A' : z + '0';
	ms[k1] = ' ';
	ms[k2++] = '.';
	while (ten != 0 && k2 - 11 <= t) {
		ten *= ss;
		i = ten;
		ms[k2++] = i > 9 ? i - 10 + 'A' : i + '0';
		ten -= i;
	}

	return ms[20];
}

char* from_ten_to_seventeenfold(double value_10, char* arr) {
	int del = value_10;
	int whole, remains, i, j;

	for (j = 0; del > 0; j++) {
		del = value_10 / 17; //делим
		whole = del * 17; // целая часть от деления
		remains = value_10 - whole; //остаток

		if (remains == 10)
			arr[j] = 'a';
		if (remains == 11)
			arr[j] = 'b';
		if (remains == 12)
			arr[j] = 'c';
		if (remains == 13)
			arr[j] = 'd';
		if (remains == 14)
			arr[j] = 'e';
		if (remains == 15)
			arr[j] = 'f';
		if (remains == 16)
			arr[j] = 'g';
		if (remains < 10)
			arr[j] = remains + '0';
		value_10 /= 14;
	}
	for (int i = j - 1; i >= 0; i--) {
		std::cout << arr[i];
	}
	return arr;
}


//task 2
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

//task 3
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

	return str_1;
}


//task 5
std::string convertToRomanian(int number) {
	std::string num;
	std::string* units = new std::string[]{ "","I","II","III","IV","V","VI","VII","VIII","IX" };
	for (int i = 0; i < number / 1000; i++) num.push_back('M');

	number %= 1000;
	if ((number % 500) / 100 + 5 == 9) {
		num += "CM";
		number %= 900;
	}
	else if (number / 500 > 0) {
		num.push_back('D');
		number %= 500;
	}

	for (int i = 0; i < number / 100; i++) num.push_back('C');

	number %= 100;


	if ((number % 50) / 10 + 5 == 9) {
		num += "XC";
		number %= 90;
	}
	else if (number / 50 > 0) {
		num.push_back('L');
		number %= 50;
	}
	if (number % 10 == 4) {
		num += "XL";
		number %= 40;
	}

	for (int i = 0; i < number / 10; i++) num.push_back('X');

	number %= 10;
	num += units[number];

	return num;
}

//task 6
int interesting_number(long long int x) {
	return (x + 1) / 10;
}

//task 7
bool multiplieByThree(int number) {
	int num = 0;
	for (int i = 0; num < number; i++)
	{
		num = (i << 1) + i;
	}
	if (num == number)
		return true;
	return false;
}

bool multiplieByFourtySeven(int number) {
	int num = 0;
	for (int i = 0; num < number; i++)
	{
		num = (i << 5) + (i << 3) + (i << 2) + (i << 1) + i;
	}
	if (num == number)
		return true;
	return false;
}
bool multiplieByBigValue(int number) {
	int num = 0;
	for (int i = 0; num < number; i++)
	{
		num = (i << 7) + (i << 6) + (i << 2) + i;
	}
	if (num == number)
		return true;
	return false;
}

//task 8
void swap_cod(string& dva) {
	for (int j = 0, j1 = dva.length() - 1; j < dva.length() / 2; j++, j1--)
		swap(dva[j], dva[j1]);
}

string to_dva(string s, string dva, int t, int k, int c) {
	for (;;) {
		for (int u = 0; u < s.length() - 1; u++) {
			if (s[u] == '0') {
				k = 0;
			}
			else {
				k = 1;
				break;
			}
		}
		if (s[s.length() - 1] == '1' && !k) {
			dva += '1';
			break;
		}
		if (s[s.length() - 1] == '0' && !k) {
			dva += '0';
			break;
		}

		for (int e = 0; e < s.length(); e++) {
			c = s[e] - '0';
			if (c % 2) {
				c = (c + t * 10) / 2;
				s[e] = c + '0';
				t = 1;
			}
			else {
				c = (c + t * 10) / 2;
				s[e] = c + '0';
				t = 0;
			}
			if (e == s.length() - 1) {
				if (t) dva += '1';
				else  dva += '0';
				t = 0;
			}
		}
	}

	for (int j = 0, j1 = dva.length() - 1; j < dva.length() / 2; j++, j1--)
		swap(dva[j], dva[j1]);

	return dva;
}

string two_decimal (int ttt) {
	string s, dva, dva2, buf, buf2;

	while (cin.fail() || ttt < 1 || ttt > 10000) {
		cin.clear();
		cin.ignore(9999, '\n');
		cout << "incorrect value, t = ";
		cin >> ttt;
	}
	s = to_string(ttt);

	if (ttt == 1) {
		cout << 1;
		return 0;
	}
	int h, h2;
	dva = to_dva(s, dva, 0, 0, 0);
	buf = dva;
	buf2 = s;
	swap_cod(buf);
	swap_cod(buf2);
	h = dva.length();
	h2 = s.length();
	buf.erase(h2, h);
	if (buf2 != buf) {
		cout << dva;
		return 0;
	}

	dva = to_dva(dva, dva2, 0, 0, 0);
	swap_cod(dva);
	dva.erase(0, h2);
	dva.erase(h, dva.length());
	swap_cod(dva);
	while (dva[0] == '0') dva.erase(0, 1);

	return dva;
}

//task 9
std::string func(int num) {
    std::string s = "";
    while (num >= 3) {
        s.push_back((num % 3) + 48);
        num /= 3;
    }
    s.push_back(num + 48);
    reverse(s.begin(), s.end());
    return s;
}

//task 10
int bad_barrel(int n, int time) {
	int barrel;

	switch (n)
	{
	case 1:
		time /= 30;
		barrel = time;
		break;
	case 2:
		time /= 30;
		barrel = time + 48;
		break;
	case 3:
		time /= 30;
		barrel = time + 96;
		break;
	case 4:
		time /= 30;
		barrel = time + 144;
		break;
	case 5:
		time /= 30;
		barrel = time + 192;
		break;
	}

	return barrel;
}