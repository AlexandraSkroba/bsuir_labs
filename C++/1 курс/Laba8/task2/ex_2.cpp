// ������������ 8, ������ 2. ���������: ������ �.�.

/* ���������� �� ���������� ���������� ������������ ��������: 
������������ ������, �������� �������, �.�.�. ������, ������� �����, 
�������, ����, ��� */

#include<Windows.h>
#include<iostream>
#include<fstream>
#include<string>
#include<iomanip>
using namespace std;

void correctValue() {
	cin.clear();
}

short inputInt(short minValue, short maxValue) {
	float x;
	while (true)
	{
		cin >> x;
		if (!cin.fail() && x > minValue && x < maxValue) {
			correctValue();
			return x;
		}
		correctValue();
		cout << "Enter correct value! " << endl;
	}
}

char* inputCharStr(int maxValue) {
	char* n = (char*)calloc(100, sizeof(char));
	while (true)
	{
		std::cin.getline(n, 100);
		if (!std::cin.fail() && strlen(n) < maxValue)
			return n;
		n = (char*)calloc(100, sizeof(char));
		cout << "Enter correct value! " << endl;
	}
}

double inputDoub(int minValue, int maxValue) {
	double x;
	while (true)
	{
		cin >> x;
		if (!cin.fail() && x > minValue && x < maxValue) {
			correctValue();
			return x;
		}
		correctValue();
		cout << "Enter correct value! " << endl;
	}
}

struct Sportsman
{
	char* empty = (char*)calloc(20, sizeof(char));
	char* country = (char*)calloc(20, sizeof(char));
	char* teamName = (char*)calloc(20, sizeof(char));
	char* firstName = (char*)calloc(20, sizeof(char));
	char* secondName = (char*)calloc(20, sizeof(char));
	char* patronymic = (char*)calloc(20, sizeof(char));
	char* number;
	int age = 0;
	int height = 0;
	double weight = 0;

};

Sportsman* createArray(int& siz);
Sportsman* createArrayOfSportsman(Sportsman* sportsman, int& size, const int& index, const int& startIndex, const int& endIndex);
void inputSportsmanInformation(Sportsman& sportsman, const int& index);
void printString(Sportsman* sportsman, const int& i);
void printData(Sportsman* sportsman, int& size);
void writeData(Sportsman* sportsman, ofstream& file, const int& size);
Sportsman* addElementsOfSportsman(Sportsman* sportsman, int& size);
Sportsman* choiceOfFilling(Sportsman* sportsman, int& size, const int& startIndex, const int& endIndex);
Sportsman* deleteElementOfSportsman(Sportsman* sportsman, int& size);
void editElement(Sportsman* sportsman, int& size);
void writeColumns(ofstream& file);

int main() {
	setlocale(LC_ALL, "1251");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "rus");
	ofstream file("inform_about_sportsmens.txt", ios::trunc);
	Sportsman* sportsman;
	int answer, size;

	sportsman = createArray(size);

	while (true) {
		cout << '\n' << "��� �� ������ �������?: " << '\n';
		cout << "1 - ������� ������� � �������\n2 - ������������� ������\n3 - �������� �������\n4 - ������� �������\n5 - ������� � ��������� ����" << '\n';

		answer = inputInt(0, 7);

		if (answer == 1) printData(sportsman, size);
		else if (answer == 2) editElement(sportsman, size);
		else if (answer == 3) sportsman = addElementsOfSportsman(sportsman, size);
		else if (answer == 4) sportsman = deleteElementOfSportsman(sportsman, size);
		else if (answer == 5) break;
	}
	writeColumns(file);

	for (int i = 0; i < size; i++)
	{
		writeData(sportsman, file, i);
	}

	file.close();
	free(sportsman);
}

void writeColumns(ofstream& file) {

	file.width(20);
	file << "���";
	file.width(20);
	file << "�������";
	file.width(20);
	file << "��������";
	file.width(20);
	file << "������� �����";
	file.width(20);
	file << "������";
	file.width(20);
	file << "�������� �������";
	file.width(20);
	file << "�������";
	file.width(20);
	file << "����";
	file.width(20);
	file << "���" << '\n';
}

void writeData(Sportsman* sportsman, ofstream& file, const int& i) {
	file << i + 1;
	file << " " << sportsman[i].firstName;
	file.width(20);
	file << sportsman[i].secondName;
	file.width(20);
	file << " " << sportsman[i].patronymic;
	file.width(20);
	file << sportsman[i].number;
	file.width(20);
	file << sportsman[i].country;
	file.width(20);
	file << sportsman[i].teamName;
	file.width(20);
	file << " " << sportsman[i].age;
	file.width(20);
	file << sportsman[i].height;
	file.width(20);
	file << sportsman[i].weight << '\n';
	file.flush();
}

Sportsman* createArray(int& size) {
	cout << "����� ���������� ����������� �� ������ �������� - ";

	size = inputInt(0, 20);

	Sportsman* sportsman = (Sportsman*)calloc(size, sizeof(Sportsman));
	return choiceOfFilling(sportsman, size, 0, size);

}

void inputSportsmanInformation(Sportsman& sportsman, const int& index) {
	cout << "";
	sportsman.empty = inputCharStr(20);
	cout << "������� ���: ";
	sportsman.firstName = inputCharStr(20);
	cout << "�������: ";
	sportsman.secondName = inputCharStr(20);
	cout << "��������: ";
	sportsman.patronymic = inputCharStr(20);
	cout << "������� ����� ����������: ";
	sportsman.number = inputCharStr(20);
	cout << "�������� �������: ";
	sportsman.teamName = inputCharStr(20);
	cout << "������: ";
	sportsman.country = inputCharStr(20);
	cout << "�������: ";
	sportsman.age = inputInt(0, 200);
	cout << "����(� ��): ";
	sportsman.height = inputDoub(0, 300);
	cout << "���(� ��): ";
	sportsman.weight = inputDoub(0, 200);

}

Sportsman* createArrayOfSportsman(Sportsman* sportsman, int& size, const int& index, const int& startIndex, const int& endIndex) {

	for (int i = startIndex; i < endIndex; i++)
	{
		inputSportsmanInformation(sportsman[i], index);

		if (i != size - 1) {
			cout << "������ �������� ��� ������ ����������(1 - ��, 2 - ���)" << '\n';
			if (inputInt(0, 3) == 1) {
				continue;
			}
			else {
				size = i + 1;
				break;
			}

		}
	}

	return sportsman;
}

void printData(Sportsman* sportsman, int& size) {

	cout << "� " << setw(5) << "���" << setw(20) << "�������" << setw(20) << "��������" << setw(20)
		<< "������� �����" << setw(20) << "������" << setw(20) << "�������� �������" << setw(20)
		<< "�������" << setw(20) << "����" << setw(20) << "���" << '\n';
	cout << "==========================================================================================================================================================================\n";

	for (int i = 0; i < size; i++)
	{
		printString(sportsman, i);
	}
}

void printString(Sportsman* sportsman, const int& i) {
	cout << i + 1 << " " << sportsman[i].firstName << setw(20) << sportsman[i].secondName << setw(20)
		<< sportsman[i].patronymic << setw(20) << sportsman[i].age << setw(20) << sportsman[i].number << setw(20)
		<< sportsman[i].country << setw(20) << sportsman[i].teamName << setw(20) << sportsman[i].age << setw(20)
		<< sportsman[i].height << setw(20) << sportsman[i].weight << '\n';

}

Sportsman* choiceOfFilling(Sportsman* sportsman, int& size, const int& startIndex, const int& endIndex) {

	return createArrayOfSportsman(sportsman, size, 0, startIndex, endIndex);
}

Sportsman* addElementsOfSportsman(Sportsman* sportsman, int& size) {
	cout << "����� ���������� ��������� �� ������ �������� - ";

	int amountAddElements = inputInt(0, 10), oldSize = size;
	size += amountAddElements;
	Sportsman* newSportsman = (Sportsman*)calloc(size, sizeof(Sportsman));

	for (int i = 0; i < oldSize; i++)
		newSportsman[i] = sportsman[i];

	return choiceOfFilling(newSportsman, size, oldSize, size);

}

Sportsman* deleteElementOfSportsman(Sportsman* sportsman, int& size)
{
	cout << "����� ������� �� ������ ������� - ";

	int deleteIndex = inputInt(0, size + 1), index = 0;
	Sportsman* newSportsman = new Sportsman[size - 1];

	for (int i = 0; i < size; i++)
	{
		if (deleteIndex - 1 != i) {
			newSportsman[index] = sportsman[i];
			index++;
		}
	}
	size -= 1;

	return newSportsman;
}

void editElement(Sportsman* sportsman, int& size) {
	cout << "������������� ���� �������? (1 - ��, 2 - ���) - ";
	int answer = inputInt(0, 3);

	cout << "������� ������� ������� �� ������ ������������� - ";
	int index = inputInt(0, size + 1) - 1;

	if (answer == 1) {
		inputSportsmanInformation(sportsman[index], 0);
	}
	else {
		cout << "������� ����, ������� �� ������ ��������\n(1 - ���, 2 - �������, 3 - ��������, 4 - ������� �����, 5 - �������� �������, 6 - ������, 7 - �������, 8 - ����, 9 - ���)" << '\n';
		answer = inputInt(0, 10);
		if (answer == 1) sportsman[index].firstName = inputCharStr(20);
		if (answer == 2) sportsman[index].secondName = inputCharStr(20);
		if (answer == 3) sportsman[index].patronymic = inputCharStr(20);
		if (answer == 4) sportsman[index].number = inputCharStr(20);
		if (answer == 5) sportsman[index].teamName = inputCharStr(20);
		if (answer == 6) sportsman[index].country = inputCharStr(20);
		if (answer == 7) sportsman[index].age = inputInt(0, 200);
		if (answer == 8) sportsman[index].height = inputDoub(0, 300);
		if (answer == 9) sportsman[index].weight = inputDoub(0, 200);
	}
}
