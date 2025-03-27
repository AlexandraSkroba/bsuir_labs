// Лабораторная 2, задача 1. Выполнена: Скроба А.П.

/* Заданы два целых числа x и y. Определите, верно ли, что одно из них
делится на другое без остатка, или нет. */

#include<iostream>
using namespace std;

int main() {

	int x, y;
	do {
		cout << "Enter two integers - ";
		cin >> x >> y;

		if (y == 0) cout << "\nYou cannot divide by zero! Please enter normal numbers!\n" << endl;
	} while (y == 0);

	if (x % y == 0) {
		cout << "\nNumbers are divisible without remainder\n";
		return 0;
	}

	cout << "\nNumbers are not divisible without remainder\n";

	return 0;
}