// ������������ 8, ������ 1. ���������: ������ �.�.

/* ���������� � ����������� �������� ���, ����� ������, ���������,
���� ������ �� �����������. ������� ������ ����������� ��������� ������,
������� ���� ������ �� ����������� ����� 20 ��� (������ ���������� �� �����������) */

#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<Windows.h>
#include<string>
using namespace std;

struct EmployeeInformation // ����������� ���������
{
    string name;
    string surname;
    string patronymic;
    int departmentNumber;
    string post;
    int workExperience;
};

EmployeeInformation* AddStruct(EmployeeInformation* Obj, const int amount); // ��������� ������ ��� ��������� ������� ��������
void setData(EmployeeInformation* Obj, const int amount); // ���� ������ � ���������
void showData(const EmployeeInformation* Obj, const int amount); // ����� ������ � ���� �������
EmployeeInformation* Delete(EmployeeInformation* Obj, int amount); // �������� ������ ���������
EmployeeInformation* sort(EmployeeInformation* Obj, int amount); // ���������� ��������� �� ����� ������

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "rus");

    cout << "��������� ������������� ���������� � ����� ������� � ����������� � ����������� \n(������� ������������ ������ � ����������).\n";
    cout << "����� ������� ������ ����������� ��������� ������, ������� ���� ������ �� ����������� ����� 20 ���.\n";
    cout << "���������� � ����������� �������� ���, ����� ������, ���������, ���� ������ �� �����������.\n";

    short size = 3;
    short employeeAmount = 0; // ������� ���-�� ��������
    EmployeeInformation* Workers = new EmployeeInformation[size];
    int YesOrNot = 0; //  ���������� ��� ���������� ���� ������

    /* ���� ����� ������ */
    while (employeeAmount < size) {
        Workers = AddStruct(Workers, employeeAmount);
        setData(Workers, employeeAmount);

        employeeAmount++;

        cout << "���������� ���� ������ (1 - ��, 0 - ���): ";
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

EmployeeInformation* AddStruct(EmployeeInformation* Obj, const int amount) // ��������� ��������� �� ��������� � ���-�� ��������
{
    if (amount == 0) {
        Obj = new EmployeeInformation[amount + 1]; // ��������� ������ ��� ������ ���������
    }
    else { // ���� ���������� ������

        EmployeeInformation* tempObj = new EmployeeInformation[amount + 1]; // �������� ���������� ���������

        for (int i = 0; i < amount; i++) {
            tempObj[i] = Obj[i]; // �������� ������ �� ��������� ���������
        }
        delete[] Obj; // ����������� ������ Obj

        Obj = tempObj; // ���������� � Obj ����� �����
    }

    return Obj; // ���������� ��������� �� ��������� EmployeeInformation
}

void setData(EmployeeInformation* Obj, const int amount) {
    cout << "\n�������: ";
    getline(cin, Obj[amount].surname);

    cout << "���: ";
    getline(cin, Obj[amount].name);

    cout << "��������: ";
    getline(cin, Obj[amount].patronymic);

    cout << "���������: ";
    getline(cin, Obj[amount].post);

    cout << "����� ������: ";
    cin >> Obj[amount].departmentNumber;

    cout << "���� ������: ";
    cin >> Obj[amount].workExperience;

    cin.get();
    cout << endl;
}

void showData(const EmployeeInformation* Obj, const int amount) {
    system("cls");
    cout << "�  " << "�������\t" << "���\t" << "��������\t" << "����� ������\t" << "���������\t" << "���� ������\t" << endl;
    cout << "===================================================================================================" << endl;

    for (int i = 0; i < amount; i++) {
        cout << i + 1 << " | " << Obj[i].surname << '\t' << Obj[i].name << '\t' << Obj[i].patronymic << "\t\t" << Obj[i].departmentNumber << '\t' << Obj[i].post << "\t\t" << Obj[i].workExperience << endl;
    }
}

EmployeeInformation* Delete(EmployeeInformation* Obj, int amount) {

    char answer;
    cout << "\n������� �����-������ �������? (1 - ��, 0 - ���):";
    cin >> answer;

    switch (answer) {
    case '1': break;
    case '0':
        system("cls");
        showData(Obj, amount);
        return Obj;
        break;
    default: "������������ ����. ���������� ���������.";
        exit(1);
    }
    short number;
    cout << "������� ����� �������� ������:\t";
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
    cout << "\n������������� ������ �� ����� ������? (1 - ��, 0 - ���):";
    cin >> answer;

    switch (answer) {
    case '1': break;
    case '0':
        system("cls");
        showData(Obj, amount);
        return Obj;
        break;
    default: "������������ ����. ���������� ���������.";
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

    int left = 0, right = amount - 1; // ����� � ������ ������� ����������� ������� �������
    int flag = 1;  // ���� ������� �����������
    // ���������� ����� ���� ����� ������� �� �������� � ������
    // � ���� � ������� ������� �����������
    while ((left < right) && flag > 0)
    {
        flag = 0;
        for (int i = left; i < right; i++)  //��������� ����� �������
        {
            if (Obj[i].workExperience > Obj[i + 1].workExperience) // ���� ��������� ������� ������ ��������,
            {             // ������ �� �������
                double t = Obj[i].workExperience;
                Obj[i].workExperience = Obj[i + 1].workExperience;
                Obj[i + 1].workExperience = t;
                flag = 1;      // ����������� � ���� ����� ����
            }
        }
        right--; // �������� ������ ������� �� ���������� �������
        for (int i = right; i > left; i--)  //��������� ������ ������
        {
            if (Obj[i - 1].workExperience > Obj[i].workExperience) // ���� ���������� ������� ������ ��������,
            {            // ������ �� �������
                double t = Obj[i].workExperience;
                Obj[i].workExperience = Obj[i - 1].workExperience;
                Obj[i - 1].workExperience = t;
                flag = 1;    // ����������� � ���� ����� ����
            }
        }
        left++; // �������� ����� ������� �� ��������� �������
    }

    showData(Obj, amount);
    return Obj;
}