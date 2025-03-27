#include<iostream> //подключение библиотеки
using namespace std; //указание пространство имен

int main() {

	setlocale(LC_ALL, "Rus");

	int n, m, x, K, A;
	double Y, D, AK;

	cout << "Введите число К - ";
	cin >> K;

	cout << "Введите числа n и m - ";
	cin >> n >> m;

	cout << "Введите число x - ";
	cin >> x;

	const double z = 1.29;

	A = abs(n + m);
	D = tan(x);
	D *= D;

	AK = (double)K / A;

	Y = z + AK + D;
	cout << "Результат вычесления = " << Y;

	return 0;
};


