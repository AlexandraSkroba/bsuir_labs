// ������������ 2, ������ 15. ���������: ������ �.�.

/* ��� �������� ����� � ���������� ����� "�� ����� � ������ � ����",
���������� ��������� ����� "����" � ������ � */

#include<iostream>
#include<iomanip>
using namespace std;

int main() {

	setlocale(LC_ALL, "Rus");

	double k;
	
	do {
		cout << fixed << setprecision(0);
		cout << "������� ���������� ������ - ";
		cin >> k;

		if (k < 0) cout << "������� ������������� �����!\n" << endl;
	} while (k < 0);

	if ( k - int(k) == 0) {
		if ( k != 111 && int(k) % 10 == 1) {
			cout << "\n�� ����� " << k << " ���� � ����!\n";

			return 0;
		}
		else if ( k < 110 && k > 120 ) {
			if ( int(k) % 10 == 2 || int(k) % 10 == 3 || int(k) % 10 == 4) {
				cout << "\n�� ����� " << k << " ����� � ����!\n";

				return 0;
			}
		}
		else if ( k == 111 || k == 112 || k == 113 ||k == 114 || int(k) % 10 == 5 || int(k) % 10 == 6 || int(k) % 10 == 7 || int(k) % 10 == 8|| int(k) % 10 == 9 || int(k) % 10 == 0) {
			cout << "\n�� ����� " << k << " ������ � ����!\n";

			return 0;
		}
	}

	cout << "\n�� ����� " << k << " ����� � ����!\n";

	return 0;
}