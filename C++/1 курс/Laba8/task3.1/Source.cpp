// ������������ 8, ������ 3. ���������: ������ �.�.

/* ������ �������, ��������� �� ������, �������� � ���� ������������ ������, 
���������� ������ ������, ���� ������� � ���� ����������� ������ �� �����. */

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
	f.open("������ ���������.txt", fstream::in | fstream::out);

	cout << "��������� ������������ �� ���� ������ �������, ��������� �� ������, ������� �������� � ���� ������������ ������,"
		<< "���������� ������ ������, ���� ������� � ���� ����������� ������ �� ����� ";

	if (!f.is_open()) { cout << "�� ������� ������� ����"; exit(1); }
	short i = 0, j = 0;
	while (!f.eof()) {
		buffer = "";
		getline(f, buffer);
		if (!(i % 4)) cout << '\n';
		++i;
		cout << i << ". " << buffer << '\n';
	}
	f.close();
	cout << "\n�������� ��������: 1 - �������� ����, 2 - ������� ����, 3 - ������� � ��������� ����\n";
	cin >> answer;

	if (answer == 3) return (0);

	cout << "������� ����� ����: "; cin >> position;

	string empty = " ";

	f.open("������ ���������.txt", fstream::in | fstream::out);

	while (!(f.eof())) {
		--position;
		if (position == 0) break;
		buffer = "";
		getline(f, buffer);
		pointer = pointer + 2 + buffer.length();
	}

	f.close();

	f.open("������ ���������.txt", fstream::in | fstream::out | fstream::binary);

	f.seekp(0);
	f.seekp(pointer);
	getline(f, buffer);

	if (empty.length() < buffer.length()) empty.resize(buffer.length(), ' ');

	f.seekp(0);
	f.seekp(pointer);

	f.write(empty.c_str(), empty.length());

	if (answer == 1) {
		cout << "������� ��������: "; cin >> empty;
		f.seekp(0);
		f.seekp(pointer);
		f.write(empty.c_str(), empty.length());
	}

	f.close();

	f.open("������ ���������.txt", fstream::in | fstream::out);

	f.seekp(0);
	i = 0;

	while (!f.eof()) {
		buffer = "";
		getline(f, buffer);
		if (!(i % 4)) cout << '\n';
		++i;
		cout << i << ". " << buffer << '\n';
	}

	cout << "\n��� ��������� ������� ��������� � txt �����!\n";
	f.close();
	return (0);
}