#pragma once
#include<map>
#include<string>
#include<iostream>
#include<Windows.h>

using namespace std;
int factorial(int i) {
    if (i == 0) return 1;
    else return i * factorial(i - 1);
}

int findWordAmount(const int& L, const int& m, std::string s1, std::string s2) {
	int  indexFirstPref = 0, indexSecondPref = 0, amount = 0;
	for (int i = 0; i < s1.length(); i++) {
		if (s1[i] == s2[indexFirstPref]) {
			for (int j = i; j < s1.length(); j++)
			{
				if (s1[j] == s2[indexFirstPref])
				{
					++indexFirstPref;
				}
				else {
					indexFirstPref = 0;
					break;
				}
			}
		}
	}

	double length = L - (s1.length() + s2.length() - indexFirstPref);
	if (length > 0)
		amount = pow(26, length) * 2;
	else if (length == 0)
		amount = 1;
	else
		amount = 0;
	return amount % m;
}

int inputInt(int minValue, int maxValue) {
	int x;
	while (true)
	{
		std::cin >> x;
		if (x < maxValue && x > minValue)
			return x;
		std::cin.clear();
		std::cin.ignore(32000, '\n');
		std::cout << "Enter correct word" << std::endl;
	}
}

int result(char* s, char* t) {
	const int size = 11;
	char  s_new[size];
	short start = 0, j = 0;
	for (short i = 0; s[i] != '\0'; ++i) {
		if (s[i] != t[0]) {
			++start;
			continue;
		}
		s_new[0] = s[i];
		break;
	}
	for (short i = 1; t[i] != '\0'; ++i) {
		++start;
		if (s[start] == '\0' || s[start] != t[i])
			break;
		++j;
		s_new[j] = s[start];
	}
	++j; start -= 2;
	for (short i = start; i >= 0; --i) {
		if (t[j] == '\0')
			break;
		if (s[i] == t[j]) s_new[j] = s[i];
		++j;
	}
	s_new[j] = '\0';
	if (strcmp(s_new, t)) {
		//std::cout << "NO" << std::endl;
		char no[3] = "NO";
		return *no;
	}
	else {
		//std::cout << "YES" << std::endl;
		char yes[4] = "YES";
		return *yes;
	}
}

int anagrams(std::string word) {
    int length = word.size();
    //int* prod = new int[length];
    int* prod = (int*)calloc(length, sizeof(int));
    int n = factorial(length); //факториал(числитель)
    map<char, int> charCount;
    for (unsigned int i = 0; i < word.size(); i++)
        charCount[word[i]]++;

    int i = 0;
    for (map<char, int>::iterator it = charCount.begin(); it != charCount.end(); ++it) {
        prod[i] = it->second;
        i++;
    }

    int sum = 1;
    for (int i = 0; i < length; i++) {
        prod[i] = factorial(prod[i]);
        sum *= prod[i];
    }

    free(prod);

    int anagramm;
    anagramm = n / sum;

    return anagramm;
}


bool eqchar(std::string s) {     // ѕроверка, €вл€етс€ ли строка множеством одинаковых символов
    for (int i = 0; i < s.length(); i++) {
        if (s[i] != s[0]) return false;
    }
    return true;
}

bool ispal(std::string s) {      // ѕроверка, €вл€етс€ ли строка палиндромом
    for (int i = 0; i < s.length() / 2; i++) {
        if (s[i] != s[s.length() - i - 1])  return false;
    }
    return true;
}

int amount(std::string s, int count) {
    if (eqchar(s)) std::cout << "-1";
    else {
        std::cout << "\n–азмер максимальной подстроки, котора€ не €вл€етс€ палиндромом: ";
        if (!ispal(s))  std::cout << s.length();
        else {
            if (s[0] < s[1]) {
                count = s.length() - 1;
                std::cout << count;
            }
            else {
                count = s.length() - 1;
                std::cout << count;
            }
        }
    }
    return count;
}


long double Sum(std::string input) {
    int count = 0;
    long double buff, sum = 0;
    int fraction, ex;
    bool exMinus;

    while (count < input.length()) {
        bool minus = false;

        if (isdigit(input[count])) {
            if (input[count - 1] == '-') {
                buff = input[count] - '0';

                minus = true;
            }
            else {
                buff = input[count] - '0';
            }

            ++count;

            while (isdigit(input[count])) {
                buff = buff * 10 + (input[count] - '0');

                ++count;
            }

            fraction = 1;

            if (input[count] == '.' && isdigit(input[count + 1])) {
                ++count;

                while (isdigit(input[count])) {
                    fraction *= 10;

                    buff = buff + (long double)(input[count] - '0') / fraction;

                    ++count;
                }
            }

            if ((input[count] == 'e' || input[count] == 'E') && (isdigit(input[count + 1]) || (input[count + 1] == '+' && isdigit(input[count + 2])) || (input[count + 1] == '-' && isdigit(input[count + 2])))) {
                exMinus = false;

                ++count;

                if (input[count] == '-') {
                    exMinus = true;
                    ++count;
                }
                else if (input[count] == '+') {
                    ++count;
                }

                ex = input[count] - '0';

                ++count;

                while (isdigit(input[count])) {
                    ex = ex * 10 + (input[count] - '0');

                    ++count;
                }

                if (exMinus) {
                    ex *= -1;
                }

                buff *= pow(10, ex);
            }

            if (minus) {
                buff *= -1;
            }

            std::cout << '\n' << buff;

            sum += buff;
        }

        ++count;
    }
    return sum;
}