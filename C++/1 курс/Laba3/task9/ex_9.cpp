// Лабораторная 3, задача 9. Выполнена: Скроба А.П.

#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
using namespace std;

int main() {

    srand(time(0));

    long long int n, a, sum = 0;

    cout << "Enter n: ";
    cin >> n;

    for (int i = 0; i < n; i++) {

        a = rand()%2+1;

        sum += pow(2, i) * pow(-1, i) * a;
    }

    cout << "sum = " << sum;;
}