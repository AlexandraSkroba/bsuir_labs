// Лабораторная 1, задача 9. Выполнена: Скроба А.П.

/* На вход дано b1 - первый член геометрической прогрессии. 
Необходимо вычислить сумму всех членов убывающей геометрической прогрессии, 
где знаменатель прогрессии q равен 1/(n+1), где n - ваш номер в журнале*/

#include<iostream>
using namespace std;

int main() {

	double b1, q, s;

	cout << "Enter the first term of a geometric progression - ";
	cin >> b1;

	q = 1.0 / 26;

	s = b1 / (1 - q);
	cout << "\nThe sum of the progression = " << s << endl;

	return 0;
}