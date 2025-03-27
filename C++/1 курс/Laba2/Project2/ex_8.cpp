// Лабораторная 3, задача 8. Выполнена: Скроба А.П.

/* Числа Армстронга (названные в честь Майкла Ф. Армстронга
(Michael F. Armstrong)), их также называют самовлюбленными числами и
совершенными цифровыми инвариантами, – это числа, равные сумме своих
цифр, возведенных в степень, равную количеству цифр. Например, наименьшее
число Армстронга – 153, которое равно 1^3 + 5^3 + 3^3 . Напишите программу,
которая выводит все числа армстронга меньше 10^6 */

#include <iostream>  
using namespace std;
int main()
{
	setlocale(LC_ALL, "Rus");

    int num = 0;

    cout << "Числа Амстронга: \n";

    while (num != powl(10, 6)) {
        int originalNum, remainder, n = 0, result = 0, power;

        ++num;

        originalNum = num;

        while (originalNum != 0) {
            originalNum /= 10;
            ++n;
        }
        originalNum = num;

        while (originalNum != 0) {
            remainder = originalNum % 10;
            power = round(pow(remainder, n));
            result += power;
            originalNum /= 10;
        }

        if (result == num)  cout << num << endl;
    }

    return 0;
}