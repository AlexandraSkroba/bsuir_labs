// Лабораторная 4, задача 14. Выполнена: Скроба А.П.

/* На вход подаётся поле для игры в "сапёр" размером n*m символов, где символ '.' означает пустое место, а символ '*' - бомбу.
Требуется дополнить это поле числами , как в оригинальной игре. Выделение памяти через функции языка С. */

#include <iostream>
#include <iomanip>
#include <ctime>

int main() {

	setlocale(LC_ALL, "Rus");
	srand(time(NULL));

	long double n, m;
	char symbol, number = 49;

	std::cout << "\tМакет игры \"Сапёр\"\n\n";

	bool flag = false;
	do {
		std::cout << "Введите длинну игрового поля: ";
		std::cin >> n;

		/* Проверка на ввод */
		if (std::cin.fail()) {
			std::cin.clear();
			std::cin.ignore();
			std::cout << "\nВведено неверное значение. Попробуйте снова.\n" << std::endl;
			flag = true;
		}

	} while (flag);

	bool flag = false;
	do {
		std::cout << "Введите ширину игрового поля: ";
		std::cin >> m;

		/* Проверка на ввод */
		if (std::cin.fail()) {
			std::cin.clear();
			std::cin.ignore();
			std::cout << "\nВведено неверное значение. Попробуйте снова.\n" << std::endl;
			flag = true;
		}

	} while (flag);

	n = n + 2;
	m = m + 2;

	char** arr;
	arr = (char**)calloc(n, sizeof(*arr));

	for (int i = 0; i < n; i++) {
		arr[i] = (char*)calloc(m, sizeof(*arr[i]));
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (i == 0 || i == n - 1 || j == 0 || j == m - 1) {
				arr[i][j] = '#';
			}
		}
	}

	int choice, bomb = 0;
	bool boom = true;


	bool flag = false;

	do {
		std::cout << "Как вы хотите заполнить игровое поле?\n1.Заполнять вручную\n2.Заполнить через функцию rand()\n";
		std::cin >> choice;

		/* Проверка на ввод */
		if (std::cin.fail()) {
			std::cin.clear();
			std::cin.ignore();
			std::cout << "\nВведено неверное значение. Попробуйте снова.\n" << std::endl;
			flag = true;
		}

	} while (flag);

	if (choice == 1) {

		std::cout << "Заполните игровое поля(\".\" - пустое место; \"*\" - бомба): \n";

		for (int i = 1; i < n - 1; i++) {

			for (int j = 1; j < m - 1; j++) {

				std::cin >> symbol;

				while (std::cin.fail() || std::cin.peek() != '\n' || (symbol != '.' && symbol != '*')) {

					std::cin.clear();
					std::cin.ignore(99999, '\n');

					std::cout << "\nВы ввели неверное значение, введите либо \".\"\"*\": ";
					std::cin >> symbol;
				}
				if (symbol == '*') arr[i][j] = '*';
				else arr[i][j] = ' ';
			}
		}
	} else {
		for (int i = 1; i < n - 1; i++) {
			for (int j = 1; j < m - 1; j++) {
				if (rand() % 2 + 1 == 1 && bomb < (((n - 2) * (m - 2)) / 4) && boom) {
					arr[i][j] = '*';
					bomb++;
					boom = false;
				} else {
					arr[i][j] = ' ';
					boom = true;
				}
			}
		}
	}

	std::cout << "\nИсходное поле:\n\n";

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			std::cout << arr[i][j] << " ";
		}
		std::cout << "\n";
	}

	std::cout << "\n\nПоле после добавления цифр:\n\n";

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			std::cout << arr[i][j] << " ";
		}
		std::cout << "\n";
	}

	for (int i = 0; i < n; i++) {
		free(arr[i]);
	}
	free(arr);
	return 0;
}