#include<iostream> //����������� ����������
using namespace std; //�������� ������������ ����

int main() {

	setlocale(LC_ALL, "Rus");

	int n, m, x, K, A;
	double Y, D, AK;

	cout << "������� ����� � - ";
	cin >> K;

	cout << "������� ����� n � m - ";
	cin >> n >> m;

	cout << "������� ����� x - ";
	cin >> x;

	const double z = 1.29;

	A = abs(n + m);
	D = tan(x);
	D *= D;

	AK = (double)K / A;

	Y = z + AK + D;
	cout << "��������� ���������� = " << Y;

	return 0;
};


