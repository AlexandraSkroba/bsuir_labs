// Ћабораторна€ 6, задача 4. ¬ыполнена: —кроба ј.ѕ.

/* ¬о-первых, из алфавита уберут четыре буквы C, Q, W и X (на клавиатуре компьютера вместо них будут клавиши, вызывающие программы Word, eXcel и другие).
¬место c перед буквами e, i, y нужно будет писать букву s, а в остальных случа€х Ц букву k. ¬место буквы q нужно будет писать букву k, вместо сочетани€
qu Цkv, вместо x Ц ks, а вместо w Ц v. ¬о-вторых, сочетание букв ph будет записыватьс€ как f, you и oo Ц как u, ee Ц как i, th Ц как z. 
 роме того, все двойные согласные (включа€ образовавшиес€ после замен), вызывающие большие трудности у учащихс€, станут одинарными, 
например, apple после реформы нужно писать как aple. */

#include <iostream> 

int main() {
	int size = 101;
	char* text = new char[size];
	std::cin.getline(text, size);
	size = strlen(text);
	for (int i = 0; i < size; ++i) {
		if (text[i] == 'c') {
			if (text[i + 1] == 'e' || text[i + 1] == 'i' || text[i + 1] == 'y') text[i] = 's';
			else text[i] = 'k';
		}
		if (text[i] == 'C') {
			if (text[i + 1] == 'e' || text[i + 1] == 'i' || text[i + 1] == 'y') text[i] = 'C';
			else text[i] = 'K';
		}
		if (text[i] == 'q') {
			text[i] = 'k';
			if (text[i + 1] == 'u') text[i + 1] = 'v';
		}
		if (text[i] == 'Q') {
			text[i] = 'K';
			if (text[i + 1] == 'u') text[i + 1] = 'v';
		}

		if (text[i] == 'x') {
			for (int k = size - 1; k > i; --k)
				text[k] = text[k - 1];

			text[i] = 'k';
			text[i + 1] = 's';
		}
		if (text[i] == 'X') {
			char tmp = 0;
			for (int m = i; text[m] != ' '; ++m)
				++tmp;

			for (int m = i + tmp + 1; m > i; --m)
				text[m - 1] = text[m];

			text[i] = 'K';
			text[i + 1] = 's';
		}
		if (text[i] == 'w')
			text[i] = 'v';

		if (text[i] == 'W')
			text[i] = 'V';

		if (text[i] == 'y' && text[i + 1] == 'o' && text[i + 2] == 'u') {
			text[i] = 'u';
			for (int k = i + 1; k < size; ++k)
				text[k] = text[k + 2];
		}
		if (text[i] == 'o' && text[i + 1] == 'o') {
			text[i] = 'u';
			for (int k = i + 1; k < size; ++k)
				text[k] = text[k + 1];
		}
		if (text[i] == 'e' && text[i + 1] == 'e') {
			text[i] = 'i';
			for (int k = i + 1; k < size; ++k)
				text[k] = text[k + 1];
		}
		if (text[i] == 't' && text[i + 1] == 'h') {
			text[i] = 'z';
			for (int k = i + 1; k < size; ++k)
				text[k] = text[k + 1];
		}
		if (text[i] == 'T' && text[i + 1] == 'h') {
			text[i] = 'Z';
			for (int k = i + 1; k < size; ++k)
				text[k] = text[k + 1];
		}
		if (text[i] == 'p' && text[i + 1] == 'h') {
			text[i] = 'f';
			for (int k = i + 1; k < size; ++k)
				text[k] = text[k + 1];
		}
		if (text[i] == 'P' && text[i + 1] == 'h') {
			text[i] = 'F';
			for (int k = i + 1; k < size; ++k)
				text[k] = text[k + 1];
		}
		if (text[i] == 'Y' && text[i + 1] == 'o' && text[i + 2] == 'u') {
			text[i] = 'U';
			for (int k = i + 1; k < size; ++k)
				text[k] = text[k + 2];
		}
		if (text[i] == text[i + 1]) {
			int counter = 1;
			while (text[i + counter] == text[i]) ++counter;
			--counter;
			for (int k = i + 1; k < size; ++k)
				text[k] = text[k + counter];
		}
	}
	for (int i = 0; i < size; ++i) {
		if (text[i] == text[i + 1]) {
			int counter = 1;
			while (text[i + counter] == text[i]) ++counter;
			--counter;
			for (int k = i + 1; k < size; ++k)
				text[k] = text[k + counter];
		}

	}
	for (int i = 0; i < size; ++i) {
		if (text[i] == 32 || text[i] == 44 || text[i] == 46 || (text[i] >= 65 && text[i] <= 90) || (text[i] >= 97 && text[i] <= 122))
			std::cout << text[i];
	}
	delete[] text;
	return 0;
}