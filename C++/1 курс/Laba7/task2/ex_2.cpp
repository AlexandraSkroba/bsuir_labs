// ������������ 7, ������ 2(������� 10). ���������: ������ �.�.

/* �� ������� ���� � �������������� */

#include<iostream>
#include<string>
#include<bitset>
#include<stdlib.h>
using namespace std;

string dop_code(string str) {

	int count = 7, count_1 = 0;
	if (str[count] == '0') {
		str[count] = '1';
	}
	else if (str[count] == '1') {
		while (str[count] != '0') {
		str[count] = '0';
		count--;
		count_1++;
	}
		str[count_1 + 1] = '1';
	}

	return str;
}

	int main() {
		setlocale(LC_ALL, "rus");
		int num_1; char sign_1;

		cout << "������� ���� ����� (+ ��� -): ";
		cin >> sign_1;
		cout << "������� ����� � ���������� ��: ";
		cin >> num_1;
		bitset<8> byte_1(num_1);

		// ������������� ������� bitset � ������-������
		string str_1 = byte_1.to_string<char, char_traits<char>, allocator<char> >();

		cout << "������ ����� � �������� ��: " << str_1 << endl;

		// �������������� � �������� ��� � ��������������
		if (sign_1 == '-') {
			string str_1 = byte_1.flip().to_string<char, char_traits<char>, allocator<char> >();
			//cout << "\n������ ����� �������������, �������� ���: " << str_1 << endl;
			str_1 = dop_code(str_1);
			cout << "������ ����� � �������������� ����: " << str_1 << endl;
		}
		else if (sign_1 == '+') {
			cout << "������ ����� � �������������� ����: " << str_1 << endl;
		}
		
		return 0;
	}