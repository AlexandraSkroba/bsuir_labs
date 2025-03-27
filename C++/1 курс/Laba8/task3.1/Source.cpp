// Лабораторная 8, задача 3. Выполнена: Скроба А.П.

/* Список товаров, имеющихся на складе, включает в себя наименование товара, 
количество единиц товара, цену единицы и дату поступления товара на склад. */

#include <iostream>
#include <string>
#include <Windows.h>
#include <fstream>
using namespace std;

short position;
int pointer;

int main() {

	setlocale(LC_ALL, "RUS");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	string buffer; fstream f; short answer;
	f.open("список продуктов.txt", fstream::in | fstream::out);

	cout << "Программа представляет из себя список товаров, имеющихся на складе, которые включает в себя наименование товара,"
		<< "количество единиц товара, цену единицы и дату поступления товара на склад ";

	if (!f.is_open()) { cout << "Не удалось открыть файл"; exit(1); }
	short i = 0, j = 0;
	while (!f.eof()) {
		buffer = "";
		getline(f, buffer);
		if (!(i % 4)) cout << '\n';
		++i;
		cout << i << ". " << buffer << '\n';
	}
	f.close();
	cout << "\nВыберите действие: 1 - изменить поле, 2 - удалить поле, 3 - закрыть и сохранить файл\n";
	cin >> answer;

	if (answer == 3) return (0);

	cout << "Введите номер поля: "; cin >> position;

	string empty = " ";

	f.open("список продуктов.txt", fstream::in | fstream::out);

	while (!(f.eof())) {
		--position;
		if (position == 0) break;
		buffer = "";
		getline(f, buffer);
		pointer = pointer + 2 + buffer.length();
	}

	f.close();

	f.open("список продуктов.txt", fstream::in | fstream::out | fstream::binary);

	f.seekp(0);
	f.seekp(pointer);
	getline(f, buffer);

	if (empty.length() < buffer.length()) empty.resize(buffer.length(), ' ');

	f.seekp(0);
	f.seekp(pointer);

	f.write(empty.c_str(), empty.length());

	if (answer == 1) {
		cout << "Введите значение: "; cin >> empty;
		f.seekp(0);
		f.seekp(pointer);
		f.write(empty.c_str(), empty.length());
	}

	f.close();

	f.open("список продуктов.txt", fstream::in | fstream::out);

	f.seekp(0);
	i = 0;

	while (!f.eof()) {
		buffer = "";
		getline(f, buffer);
		if (!(i % 4)) cout << '\n';
		++i;
		cout << i << ". " << buffer << '\n';
	}

	cout << "\nВсе изменения успешно сохранены в txt файле!\n";
	f.close();
	return (0);
}