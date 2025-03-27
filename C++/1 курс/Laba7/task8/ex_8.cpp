// Лабораторная 7, задача 8. Выполнена: Скроба А.П.

/* Натуральное число называется двудесятичным, если его десятичное представление является суффиксом его двоичного представления; 
и двоичное и десятичное представление рассматривается без ведущих нулей. Например, 1010 = 10102, так что 10 двудесятичное число.
Числа 101010 = 11111100102 и 4210 = 1010102 не являются двудесятичными.
Сначала Брюс хочет создать список двудесятичных чисел. Помогите ему найти n-ое наименьшее двудесятичное число*/

#include <iostream>
#include <string>
using namespace std;

void swap_cod(string& dva) {
	for (int j = 0, j1 = dva.length() - 1; j < dva.length() / 2; j++, j1--)
		swap(dva[j], dva[j1]);
}

string to_dva(string s, string dva, int t, int k, int c) {
	for(;;) {
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

int main() {
	setlocale(LC_ALL, "rus");
	string s, dva, dva2, buf, buf2;
	cout << "Программа выводит число - n-ое наименьшее двудесятичное число в десятичном представлении\n";
	cout << "Введите одно целое число: ";

	int ttt;
	cin >> ttt;
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
	cout << "\nn - ое наименьшее двудесятичное число в десятичном представлении: ";
	cout << dva << endl;

	return 0;
}
