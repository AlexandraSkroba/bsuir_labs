// Лабораторная 8, задача 2. Выполнена: Скроба А.П.

/* Информация об участниках спортивных соревнований содержит:
наименование страны, название команды, Ф.И.О. игрока, игровой номер,
возраст, рост, вес */

#include <iostream>
#include <string>
#include <cstdio>
#include <fstream>
#include <Windows.h>

using namespace std;

struct Sportsman
{
    char surname[80];
    char name[80];
    char patronymic[80];
    char country[80];
    char teamName[80];
    int number;
    int age;
    int height;
    double weight;
};

void inputSportsmanInformation(Sportsman* arr, int size); // считывание данных из файла
void deleteData(Sportsman* arr, int size, int position);
void printData(Sportsman* arr, int size);
void menu(Sportsman* arr, int size);
void read_from_text(char element);
void Final_Answer(Sportsman* arr, int position);
void read_from_text_Digit(int element);

//////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "Rus");

    int size;
    cout << "Введите количество спортсменов: ";
    cin >> size;

    read_from_text_Digit(size);

    Sportsman* sportsman = (Sportsman*)calloc(size, sizeof(Sportsman));

    inputSportsmanInformation(sportsman, size);
    menu(sportsman, size);

    free(sportsman);
    return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////

void inputSportsmanInformation(Sportsman* arr, int size)
{
    fstream fs;
    fs.open("inform_sport.txt", fstream::in | fstream::out | ofstream::app);

    for (int i = 0; i < size; i++)
    {
        fs >> arr[i].surname;
        fs >> arr[i].name;
        fs >> arr[i].patronymic;
        fs >> arr[i].country;
        fs >> arr[i].teamName;
        fs >> arr[i].number;
        fs >> arr[i].age;
        fs >> arr[i].height;
        fs >> arr[i].weight;

    }
    fs.close();
}
void AddArray(Sportsman* arr, int size, int newsize)
{
    Sportsman* temp = (Sportsman*)calloc(size, sizeof(Sportsman));

    for (int i = 0; i < size; i++)
    {
        temp[i] = arr[i];
    }
    free(arr);

    size += newsize;

    arr = (Sportsman*)calloc(size, sizeof(Sportsman));

    for (int i = 0; i < size; i++)
    {
        arr[i] = temp[i];
    }
    free(temp);

    fstream fs;
    fs.open("inform_sport.txt", ofstream::app);

    for (int i = size - newsize; i < size; i++)
    {
        cout << "Фамилия: ";
        cin >> arr[i].surname;
        cout << "Имя: ";
        cin >> arr[i].name;
        cout << "Отчество: ";
        cin >> arr[i].patronymic;
        cout << "Страна: ";
        cin >> arr[i].country;
        cout << "Название команды: ";
        cin >> arr[i].teamName;
        cout << "Номер игрока: ";
        cin >> arr[i].number;
        cout << "Возраст: ";
        cin >> arr[i].age;
        cout << "Рост: ";
        cin >> arr[i].height;
        cout << "Вес: ";
        cin >> arr[i].weight;

        if (!fs.is_open())
        {
            cout << "Ошибка открытия файла!" << endl;
        }
        else
        {
            fs << arr[i].surname << "  ";
            fs << arr[i].name << "  ";
            fs << arr[i].patronymic << "  ";
            fs << arr[i].country << "  ";
            fs << arr[i].teamName << "  ";
            fs << arr[i].number << "  ";
            fs << arr[i].age << "  ";
            fs << arr[i].height << "  ";
            fs << arr[i].weight << "\n\n";

        }
    }
    fs.close();
    menu(arr, size);
}
void deleteData(Sportsman* arr, int size, int position)
{
    if (position > size - 1) return;

    Sportsman* temp = (Sportsman*)calloc(size, sizeof(Sportsman));

    for (int i = 0; i < size; i++)
    {
        temp[i] = arr[i];
    }
    free(arr);

    size -= 1;

    arr = (Sportsman*)calloc(size, sizeof(Sportsman));

    int j = 0;

    for (int i = 0; i < size + 1; i++)
    {
        if (i != position)
        {
            arr[j] = temp[i];
            j++;
        }
    }
    free(temp);
    menu(arr, size);
}
void printData(Sportsman* arr, int size)
{
    for (int i = 0; i < size; i++)
    {
        cout << "\n" << i + 1 << ". " << arr[i].surname << " " << arr[i].name << " " << arr[i].patronymic << " " << arr[i].country << " " << arr[i].teamName << " " << arr[i].number << " " << arr[i].age << " " << arr[i].height << " " << arr[i].weight << "\n";
    }
    menu(arr, size);
}
void menu(Sportsman* arr, int size)
{
    char n;
    cout << "\nВыберите, что вы хотите сделать далее:\n";
    cout << "1 - вывести элементы на экран\n";
    cout << "2 - добавить элемент\n";
    cout << "3 - удалить элемент\n";
    cout << "4 - закрыть и сохранить изменения в файл\n";
    cin >> n;
    read_from_text(n);

    switch (n)
    {
    case '1': printData(arr, size);
        break;

    case '2': int newsize;
        cout << "\nВведите количество элментов, которое вы хотите добавить: ";
        cin >> newsize;
        read_from_text_Digit(newsize);
        AddArray(arr, size, newsize);
        break;

    case '3':  int position;
        cout << "\nВведите позицию элемента, который хотите удалить: ";
        cin >> position;
        read_from_text_Digit(position);
        deleteData(arr, size, position);
        break;

    case '4': Final_Answer(arr, (size - 1));
        break;

    default: return;
    }
}
void read_from_text(char element)
{
    ofstream fs;
    fs.open("inform_sport.txt", ofstream::app);

    if (!fs.is_open())
    {
        cout << "Ошибка открытия файла!" << endl;
    }
    else
    {
        fs << element << "\n\n";
    }
    fs.close();
}
void read_from_text_Digit(int element)
{
    ofstream fs;
    fs.open("inform_sport.txt", ofstream::app);

    if (!fs.is_open())
    {
        cout << "Ошибка открытия файла!" << endl;
    }
    else
    {
        fs << element << "\n\n";
    }
    fs.close();
}
void Final_Answer(Sportsman* arr, int position)
{
    ofstream fout2;
    fout2.open("inform_sport_final.txt", ofstream::app);

    if (!fout2.is_open())
    {
        cout << "Ошибка открытия файла!" << endl;
    }
    else
    {
        fout2 << arr[position].surname << "  ";
        fout2 << arr[position].name << "  ";
        fout2 << arr[position].patronymic << "  ";
        fout2 << arr[position].country << "  ";
        fout2 << arr[position].teamName << "  ";
        fout2 << arr[position].number << "  ";
        fout2 << arr[position].age << "  ";
        fout2 << arr[position].height << "  ";
        fout2 << arr[position].weight << "\n\n";
    }
    fout2.close();
}