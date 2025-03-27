// Лабораторная 8, задача 1. Выполнена: Скроба А.П.

/* Информация о сотрудниках содержит ФИО, номер отдела, должность,
стаж работы на предприятии. Вывести список сотрудников заданного отдела,
имеющих стаж работы на предприятии более 20 лет (Шейкер сортировка по возрастанию) */

#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<Windows.h>
#include<string>
using namespace std;

struct EmployeeInformation // определение структуры
{
    string name;
    string surname;
    string patronymic;
    int departmentNumber;
    string post;
    int workExperience;
};

EmployeeInformation* AddStruct(EmployeeInformation* Obj, const int amount); // выделение памяти для элементов массива структур
void setData(EmployeeInformation* Obj, const int amount); // ввод данных в структуру
void showData(const EmployeeInformation* Obj, const int amount); // вывод данных в виде таблицы
EmployeeInformation* Delete(EmployeeInformation* Obj, int amount); // удаление данных структуры
EmployeeInformation* sort(EmployeeInformation* Obj, int amount); // сортировка структуры по стажу роботы

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "rus");

    cout << "Программа предоставляет заполнение и вывод табилцы с информацией о сотрудниках \n(которую пользователь вводит с клавиатуры).\n";
    cout << "Также выводит список сотрудников заданного отдела, имеющих стаж работы на предприятии более 20 лет.\n";
    cout << "Информация о сотрудниках содержит ФИО, номер отдела, должность, стаж работы на предприятии.\n";

    short size = 3;
    short employeeAmount = 0; // счетчик кол-ва структур
    EmployeeInformation* Workers = new EmployeeInformation[size];
    int YesOrNot = 0; //  продолжить или остановить ввод данных

    /* цикл ввода данных */
    while (employeeAmount < size) {
        Workers = AddStruct(Workers, employeeAmount);
        setData(Workers, employeeAmount);

        employeeAmount++;

        cout << "Продолжить ввод данных (1 - да, 0 - нет): ";
        cin >> YesOrNot;
        cin.get();
        if (YesOrNot != 1) break;
    }

    showData(Workers, employeeAmount);
    Workers = sort(Workers, employeeAmount);
    Workers = Delete(Workers, employeeAmount);

    delete[] Workers;
    return 0;
}

EmployeeInformation* AddStruct(EmployeeInformation* Obj, const int amount) // принимает указатель на структуру и кол-во структур
{
    if (amount == 0) {
        Obj = new EmployeeInformation[amount + 1]; // выделение памяти для первой структуры
    }
    else { // блок сохранения данных

        EmployeeInformation* tempObj = new EmployeeInformation[amount + 1]; // создание временного указателя

        for (int i = 0; i < amount; i++) {
            tempObj[i] = Obj[i]; // копируем данные во временный указатель
        }
        delete[] Obj; // освобождаем память Obj

        Obj = tempObj; // записываем в Obj новый адрес
    }

    return Obj; // возвращает указатель на структуру EmployeeInformation
}

void setData(EmployeeInformation* Obj, const int amount) {
    cout << "\nФамилия: ";
    getline(cin, Obj[amount].surname);

    cout << "Имя: ";
    getline(cin, Obj[amount].name);

    cout << "Отчество: ";
    getline(cin, Obj[amount].patronymic);

    cout << "Должность: ";
    getline(cin, Obj[amount].post);

    cout << "Номер отдела: ";
    cin >> Obj[amount].departmentNumber;

    cout << "Стаж работы: ";
    cin >> Obj[amount].workExperience;

    cin.get();
    cout << endl;
}

void showData(const EmployeeInformation* Obj, const int amount) {
    system("cls");
    cout << "№  " << "Фамилия\t" << "Имя\t" << "Отчество\t" << "Номер отдела\t" << "Должность\t" << "Стаж работы\t" << endl;
    cout << "===================================================================================================" << endl;

    for (int i = 0; i < amount; i++) {
        cout << i + 1 << " | " << Obj[i].surname << '\t' << Obj[i].name << '\t' << Obj[i].patronymic << "\t\t" << Obj[i].departmentNumber << '\t' << Obj[i].post << "\t\t" << Obj[i].workExperience << endl;
    }
}

EmployeeInformation* Delete(EmployeeInformation* Obj, int amount) {

    char answer;
    cout << "\nУдалить какой-нибудь элемент? (1 - да, 0 - нет):";
    cin >> answer;

    switch (answer) {
    case '1': break;
    case '0':
        system("cls");
        showData(Obj, amount);
        return Obj;
        break;
    default: "Некорректный ввод. Завершение программы.";
        exit(1);
    }
    short number;
    cout << "Введите номер элемента списка:\t";
    cin >> number;
    if (number > amount || number <= 0) exit(1);
    --number; --amount;
    if (amount) {
        EmployeeInformation* newarray = new EmployeeInformation[amount];

        for (short i = 0, j = 0; i <= amount; ++i, ++j) {
            if (i == number) {
                --j;
                continue;
            }
            newarray[j].name = Obj[i].name;
            newarray[j].surname = Obj[i].surname;
            newarray[j].patronymic = Obj[i].patronymic;
            newarray[j].departmentNumber = Obj[i].departmentNumber;
            newarray[j].post = Obj[i].post;
            newarray[j].workExperience = Obj[i].workExperience;

        }
        delete[] Obj;
        showData(newarray, amount);
        return newarray;
    }
    else {
        exit(1);
    }
}

EmployeeInformation* sort(EmployeeInformation* Obj, int amount) {
    char answer;
    cout << "\nОтсортировать массив по стажу роботы? (1 - да, 0 - нет):";
    cin >> answer;

    switch (answer) {
    case '1': break;
    case '0':
        system("cls");
        showData(Obj, amount);
        return Obj;
        break;
    default: "Некорректный ввод. Завершение программы.";
        exit(1);
    }

    /*EmployeeInformation* newarray = new EmployeeInformation[amount];
    for (int i = 0, j = 0; i < amount; i++) {
        if (Obj[i].workExperience >= 20) {
            newarray[j].name = Obj[i].name;
            newarray[j].surname = Obj[i].surname;
            newarray[j].patronymic = Obj[i].patronymic;
            newarray[j].departmentNumber = Obj[i].departmentNumber;
            newarray[j].post = Obj[i].post;
            newarray[j].workExperience = Obj[i].workExperience;

            j++;
        }
    }*/

    int left = 0, right = amount - 1; // левая и правая границы сортируемой области массива
    int flag = 1;  // флаг наличия перемещений
    // Выполнение цикла пока левая граница не сомкнётся с правой
    // и пока в массиве имеются перемещения
    while ((left < right) && flag > 0)
    {
        flag = 0;
        for (int i = left; i < right; i++)  //двигаемся слева направо
        {
            if (Obj[i].workExperience > Obj[i + 1].workExperience) // если следующий элемент меньше текущего,
            {             // меняем их местами
                double t = Obj[i].workExperience;
                Obj[i].workExperience = Obj[i + 1].workExperience;
                Obj[i + 1].workExperience = t;
                flag = 1;      // перемещения в этом цикле были
            }
        }
        right--; // сдвигаем правую границу на предыдущий элемент
        for (int i = right; i > left; i--)  //двигаемся справа налево
        {
            if (Obj[i - 1].workExperience > Obj[i].workExperience) // если предыдущий элемент больше текущего,
            {            // меняем их местами
                double t = Obj[i].workExperience;
                Obj[i].workExperience = Obj[i - 1].workExperience;
                Obj[i - 1].workExperience = t;
                flag = 1;    // перемещения в этом цикле были
            }
        }
        left++; // сдвигаем левую границу на следующий элемент
    }

    showData(Obj, amount);
    return Obj;
}