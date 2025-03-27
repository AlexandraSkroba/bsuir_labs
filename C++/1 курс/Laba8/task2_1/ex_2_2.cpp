// Лабораторная 8, задача 3. Выполнена: Скроба А.П.

/* Различные цеха завода выпускают продукцию нескольких наименований. Сведения о выпущенной продукции включают наименование, количество, номер цеха */

#include <iostream> 
#include <fstream> 
#include <regex> 
using namespace std;

class Production {
    string name;
    string quantity;
    string number;

public:
    void ShellSort(int n, Production* mass, fstream& file) {
        short k = 0, counter = 0;
        string buf;
        while (!file.eof()) {
            if (counter == 3) {
                counter = 0;
                ++k;
                continue;
            }
            if (k == 3) break;

            buf = "";
            file >> buf;
            if (buf == "") continue;

            switch (counter) {
            case 0: mass[k].name = buf; break;
            case 1: mass[k].quantity = buf; break;
            case 2: mass[k].number = buf;
            }
            ++counter;
        }
        int i, j, step, tmp2;
        string tmp1, tmp3;

        for (int i = 2; i >= 0; --i) {
            cout << mass[i].name; putchar('\t');
            cout << mass[i].quantity; putchar('\t');
            cout << mass[i].number; putchar('\n');
        }
    }

    void redact_structure(Production* arr, short& size) {

        for (short i = 0; i < size; ++i)
            cout << i + 1 << ".\t" << arr[i].name << '\t' << arr[i].number << '\t' << arr[i].quantity << '\n';

        short answer1, answer2;
        cout << "Изменить какое-нибудь поле?(1 - да, 0 - нет): ";
        cin >> answer1;
        if (answer1 != 1) return;

        do {
            cout << "Укажите номер структуры: ";
            cin >> answer1;
        } while (answer1 < 1 || answer1 > size);

        if (answer1 < 1 || answer1 > size) return;
        --answer1;
        cout << "1. " << arr[answer1].name << " 2. " << arr[answer1].number << "\t3. " << arr[answer1].quantity << '\n';

        do {
            cout << "Укажите номер поля: ";
            cin >> answer2;
        } while (answer2 < 1 || answer2 > 3);

        string temp;
        cout << "Введите новое значение: "; cin >> temp;
        switch (answer2) {
        case 1: arr[answer1].name = temp; break;
        case 2: arr[answer1].number = temp; break;
        case 3: arr[answer1].quantity = temp;
        }

        redact_structure(arr, size);

    }
};
void redaction();

int main() {
    setlocale(0, "");
    short size = 3, i = 0, counter = 0;
    Production* arr = new Production[size];
    fstream file;
    file.open("ourProduction.txt", fstream::in | fstream::out | fstream::app);
    if (!file.is_open()) cout << "Ошибка открытия файла\n";

    arr[0].ShellSort(size, arr, file);
    putchar('\n');
    arr[0].redact_structure(arr, size);

    //redaction(); 
    file.close();


    delete[] arr;
    return 0;
}
void redaction() {
    short position;
    int pointer = 0;

    fstream file;
    string buffer; short answer;
    file.open("ourProduction.txt", fstream::in | fstream::out);

    if (!file.is_open()) {
        cout << "Ошибка открытия файла";
        exit(1);
    }

    short i = 0, j = 0;
    while (!file.eof()) {
        buffer = "";
        getline(file, buffer);
        if (!(i % 4)) cout << '\n';
        ++i;
        cout << i << ".\t" << buffer << '\n';
    }
    file.close();
    cout << "\nВыберите действие:\n1 - изменить поле\n2 - удалить поле\n";
    cin >> answer;

    //if (answer == 3); 

    cout << "Введите номер поля: ";
    cin >> position;

    string empty = "";

    file.open("ourProduction.txt", fstream::in | fstream::out);

    while (!(file.eof())) {
        --position;
        if (position == 0) break;
        buffer = "";
        getline(file, buffer);
        pointer = pointer + 2 + buffer.length();
    }

    file.close();

    file.open("ourProduction.txt", fstream::in | fstream::out | fstream::binary);

    file.seekp(0);
    file.seekp(pointer);
    getline(file, buffer);

    if (empty.length() < buffer.length()) empty.resize(buffer.length(), ' ');

    file.seekp(0);
    file.seekp(pointer);

    file.write(empty.c_str(), empty.length());

    if (answer == 1) {
        cout << "Введите значение: ";
        cin >> empty;

        file.seekp(0);
        file.seekp(pointer);
        file.write(empty.c_str(), empty.length());
    }
    file.close();

    file.open("ourProduction.txt", fstream::in | fstream::out);

    file.seekp(0);
    i = 0;

    while (!file.eof()) {
        buffer = "";
        getline(file, buffer);
        if (!(i % 4)) cout << '\n';
        ++i;
        cout << i << ". " << buffer << '\n';
    }
    file.close();
}