// Лабораторная 8, задача 2. Выполнена: Скроба А.П.

/* Информация об участниках спортивных соревнований содержит: 
наименование страны, название команды, Ф.И.О. игрока, игровой номер, 
возраст, рост, вес */

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
		cout << '\n' << "Что вы хотите сделать?: " << '\n';
		cout << "1 - вывести таблицу в консоль\n2 - редактировать список\n3 - добавить элемент\n4 - удалить элемент\n5 - закрыть и сохранить файл" << '\n';

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
	file << "Имя";
	file.width(20);
	file << "Фамилия";
	file.width(20);
	file << "Отчество";
	file.width(20);
	file << "Игровой номер";
	file.width(20);
	file << "Страна";
	file.width(20);
	file << "Название команды";
	file.width(20);
	file << "Возраст";
	file.width(20);
	file << "Рост";
	file.width(20);
	file << "Вес" << '\n';
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
	cout << "Какое количество спортсменов вы хотите добавить - ";

	size = inputInt(0, 20);

	Sportsman* sportsman = (Sportsman*)calloc(size, sizeof(Sportsman));
	return choiceOfFilling(sportsman, size, 0, size);

}

void inputSportsmanInformation(Sportsman& sportsman, const int& index) {
	cout << "";
	sportsman.empty = inputCharStr(20);
	cout << "Введите имя: ";
	sportsman.firstName = inputCharStr(20);
	cout << "Фамилия: ";
	sportsman.secondName = inputCharStr(20);
	cout << "Отчество: ";
	sportsman.patronymic = inputCharStr(20);
	cout << "Игровой номер спортсмена: ";
	sportsman.number = inputCharStr(20);
	cout << "Название команды: ";
	sportsman.teamName = inputCharStr(20);
	cout << "Страна: ";
	sportsman.country = inputCharStr(20);
	cout << "Возраст: ";
	sportsman.age = inputInt(0, 200);
	cout << "Рост(в см): ";
	sportsman.height = inputDoub(0, 300);
	cout << "Вес(в кг): ";
	sportsman.weight = inputDoub(0, 200);

}

Sportsman* createArrayOfSportsman(Sportsman* sportsman, int& size, const int& index, const int& startIndex, const int& endIndex) {

	for (int i = startIndex; i < endIndex; i++)
	{
		inputSportsmanInformation(sportsman[i], index);

		if (i != size - 1) {
			cout << "Хотите добавить еще одного спортсмена(1 - да, 2 - нет)" << '\n';
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

	cout << "№ " << setw(5) << "Имя" << setw(20) << "Фамилия" << setw(20) << "Отчество" << setw(20)
		<< "Игровой номер" << setw(20) << "Страна" << setw(20) << "Название команды" << setw(20)
		<< "Возраст" << setw(20) << "Рост" << setw(20) << "Вес" << '\n';
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
	cout << "Какие количество элементов вы хотите добавить - ";

	int amountAddElements = inputInt(0, 10), oldSize = size;
	size += amountAddElements;
	Sportsman* newSportsman = (Sportsman*)calloc(size, sizeof(Sportsman));

	for (int i = 0; i < oldSize; i++)
		newSportsman[i] = sportsman[i];

	return choiceOfFilling(newSportsman, size, oldSize, size);

}

Sportsman* deleteElementOfSportsman(Sportsman* sportsman, int& size)
{
	cout << "Какой элемент вы хотите удалить - ";

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
	cout << "Редактировать весь элемент? (1 - да, 2 - нет) - ";
	int answer = inputInt(0, 3);

	cout << "Введите элемент который вы хотите редактировать - ";
	int index = inputInt(0, size + 1) - 1;

	if (answer == 1) {
		inputSportsmanInformation(sportsman[index], 0);
	}
	else {
		cout << "Введите поле, которое вы хотите изменить\n(1 - Имя, 2 - Фамилия, 3 - Отчество, 4 - Игровой номер, 5 - Название команды, 6 - Страна, 7 - Возраст, 8 - Рост, 9 - Вес)" << '\n';
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
