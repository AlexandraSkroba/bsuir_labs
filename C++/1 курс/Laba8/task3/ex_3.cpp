// Лабораторная 8, задача 3. Выполнена: Скроба А.П.
//нет удаления
/* Список товаров, имеющихся на складе, включает в себя наименование товара,
количество единиц товара, цену единицы и дату поступления товара на склад. */

#include <iostream>
#include <string>
#include "../static_lib/static_lib.h"
#include <Windows.h>
#include <fstream>
using namespace std;

short Size;
short position;
int pointer;

int main() {

	setlocale(LC_ALL, "RUS");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	string buffer; fstream f; short answer;
	f.open("file2", fstream::in | fstream::out);

	if (!f.is_open()) { cout << "Не удалось открыть файл"; exit(1); }
	short i = 0, j = 0;
	while (!f.eof()) {
		buffer = "";
		getline(f, buffer);
		if (!(i % 4)) cout << '\n';
		++i;
		cout << i << ".\t" << buffer << '\n';
	}

	f.close();
	f.open("file2", fstream::in | fstream::out);
	i = 0;
	ITEM Item;
	List new_item;
	string name, amount, date, cost;
	while (!f.eof()) {
		buffer = "";
		getline(f, buffer);
		++i;

		if (i > 4) {
			Item.Push(new_item, name, amount, cost, date);
			i = 1;
		}

		switch (i) {
		case 1: name = buffer; break;
		case 2: amount = buffer; break;
		case 3: cost = buffer; break;
		case 4: date = buffer; break;
		}
	}
	f.close();
	Item.Push(new_item, name, amount, cost, date);
	Item.Print(new_item);
	Item.Sort(new_item);
	return (0);
}