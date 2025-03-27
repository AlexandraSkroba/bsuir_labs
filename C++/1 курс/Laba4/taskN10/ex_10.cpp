// Лабораторная 4, задача 10. Выполнена: Скроба А.П.

/* Построить магический квадрат любого порядка, используя любой алгоритм. Выделение памяти через функции языка С. */

#include <iostream>
#include <iomanip>

// Ввод целочисленного значения (число больше 0)
long long int inputInt() {
    setlocale(LC_ALL, "rus");
    long double value;

    std::cin >> value;

    // Удаление всех пробелов (если они есть) после первого числа, если оно было в потоке
    while (std::cin.peek() == ' ')
        std::cin.ignore(1, ' ');

    // Проверка состояния потока ввода, конца строки, области допустимых значений и экспоненты
    while (std::cin.fail() || std::cin.peek() != '\n' || value <= 0 || value != (long long int)value) {
        std::cout << "Ввод некорректен. Введите целое положительное числовое значение (до 2⁶³): ";

        std::cin.clear(); // Включение потока ввода
        std::cin.ignore(3256, '\n'); // Очищение буфера потока ввода

        std::cin >> value;

        while (std::cin.peek() == ' ')
            std::cin.ignore(1, ' ');
    }

    return value;
}

int main() {
    setlocale(LC_ALL, "rus");
    int n, i, j, m = 1, t, y, x, buff;

    std::cout << "Программа строит магический квадрат заданного вами порядка.\n\nВведите порядок магического квадрата: ";
    n = inputInt();

    int** magicSquare;

    magicSquare = (int**)calloc(n, sizeof(*magicSquare));

    for (int i = 0; i < n; ++i) {
        magicSquare[i] = (int*)calloc(n, sizeof(*magicSquare[i]));
    }

    if (n == 2) {
        std::cout << "\nМагического квадрата не существует.";
    }
    else if (n == 1) {
        std::cout << "\nМагический квадрат:\n\n" << std::setw(3) << 1 << '\n';
    }
    else if (n % 2 == 1) {
        i = 0;
        j = static_cast<int>(n / 2); // Высчитывание среднего элемента

        magicSquare[i][j] = 1; // Средний элемент верхней строки равен 1

        // Заполнение магического квадрата
        for (int k = 2; k < n * n + 1; ++k) {
            if (i - 1 >= 0 && j - 1 >= 0 && magicSquare[i - 1][j - 1] == 0) {
                magicSquare[i - 1][j - 1] = k;
                --i;
                --j;
            }
            else if (i - 1 >= 0 && j - 1 >= 0 && magicSquare[i - 1][j - 1] != 0) {
                magicSquare[i + 1][j] = k;
                ++i;
            }
            else if (i - 1 < 0 && j - 1 >= 0) {
                magicSquare[n - 1][j - 1] = k;
                i = n - 1;
                --j;
            }
            else if (i - 1 >= 0 && j - 1 < 0) {
                magicSquare[i - 1][n - 1] = k;
                --i;
                j = n - 1;
            }
            else if (i - 1 < 0 && j - 1 < 0 && magicSquare[n - 1][n - 1] != 0) {
                magicSquare[i + 1][j] = k;
                ++i;
            }
        }
    }
    else if (n % 4 == 0) {
        int** secondarySquare;

        secondarySquare = (int**)malloc(n * sizeof(int*));

        for (long long int i = 0; i < n; ++i) {
            secondarySquare[i] = (int*)malloc(n * sizeof(int));
        }

        // Заполнение от 0 до n^2 магического квадрата
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                magicSquare[i][j] = m;
                ++m;
            }
        }

        m = n * n;

        // Заполнение вспомогательного квадрата
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                secondarySquare[i][j] = m;
                --m;
            }
        }

        // Длина одного маленького квадрата
        m = (n / 4) * (n / 4);

        t = 1;
        i = 0;
        j = 0;

        // Перестановка элементов из вспомогательного в магический квадрат по диагоналям
        while (t < m + 1) {
            ++t;

            y = i;
            x = j;

            while (y < i + 4) {
                magicSquare[y][x] = secondarySquare[y][x];
                ++y;
                ++x;
            }

            y = i + 3;
            x = j;

            while (x < i + 4) {
                magicSquare[y][x] = secondarySquare[y][x];
                --y;
                ++x;
            }

            if (j + 4 < n) {
                j += 4;
            }
            else if (j + 4 >= n) {
                j = 0;
                i += 4;
            }
        }

        for (long long int i = 0; i < n; ++i) {
            free(secondarySquare[i]);
        }
        free(secondarySquare);

    }
    else {
        int length4 = n / 2;

        int** _arr1;
        _arr1 = (int**)calloc(length4, sizeof(*_arr1));
        int** _arr2;
        _arr2 = (int**)calloc(length4, sizeof(*_arr2));
        int** _arr3;
        _arr3 = (int**)calloc(length4, sizeof(*_arr3));
        int** _arr4;
        _arr4 = (int**)calloc(length4, sizeof(*_arr4));

        for (int i = 0; i < length4; ++i) {
            _arr1[i] = (int*)calloc(length4, sizeof(*_arr1[i]));
        }
        for (int i = 0; i < length4; ++i) {
            _arr2[i] = (int*)calloc(length4, sizeof(*_arr2[i]));
        }
        for (int i = 0; i < length4; ++i) {
            _arr3[i] = (int*)calloc(length4, sizeof(*_arr3[i]));
        }
        for (int i = 0; i < length4; ++i) {
            _arr4[i] = (int*)calloc(length4, sizeof(*_arr4[i]));
        }

        // Высчитывание максимальных значений в маленьких квадратах
        int pred1 = n * n / 4;
        int pred2 = n * n / 2;
        int pred3 = n * n / 4 * 3;
        int pred4 = n * n;

        int k = 1;

        i = 0;
        j = static_cast<int>(length4 / 2);
        _arr1[i][j] = 1;
        ++k;

        // Заполнение магического первого маленького квадрата
        while (k < pred1 + 1) {
            if (i - 1 > -1 && j - 1 > -1 && _arr1[i - 1][j - 1] == 0) {
                _arr1[i - 1][j - 1] = k;
                --i;
                --j;
            }
            else if (i - 1 > -1 && j - 1 > -1 && _arr1[i - 1][j - 1] != 0 && i + 1 < length4) {
                _arr1[i + 1][j] = k;
                ++i;
            }
            else if (i - 1 < 0 && j - 1 >= 0) {
                _arr1[length4 - 1][j - 1] = k;
                i = length4 - 1;
                --j;
            }
            else if (i - 1 >= 0 && j - 1 < 0) {
                _arr1[i - 1][length4 - 1] = k;
                --i;
                j = length4 - 1;
            }
            else if (i - 1 < 0 && j - 1 < 0 && _arr1[length4 - 1][length4 - 1] != 0 && i + 1 < length4) {
                _arr1[i + 1][j] = k;
                ++i;
            }

            ++k;
        }

        i = 0;
        j = static_cast<int>(length4 / 2);
        _arr4[i][j] = k;

        ++k;

        // Заполнение магического четвёртого маленького квадрата
        while (k < pred2 + 1) {
            if (i - 1 > -1 && j - 1 >= 0 && _arr4[i - 1][j - 1] == 0) {
                _arr4[i - 1][j - 1] = k;
                --i;
                --j;
            }
            else if (i - 1 >= 0 && j - 1 >= 0 && _arr4[i - 1][j - 1] != 0 && i + 1 < length4) {
                _arr4[i + 1][j] = k;
                ++i;
            }
            else if (i - 1 < 0 && j - 1 >= 0) {
                _arr4[length4 - 1][j - 1] = k;
                i = length4 - 1;
                --j;
            }
            else if (i - 1 >= 0 && j - 1 < 0) {
                _arr4[i - 1][length4 - 1] = k;
                --i;
                j = length4 - 1;
            }
            else if (i - 1 < 0 && j - 1 < 0 && _arr4[length4 - 1][length4 - 1] != 0 && i + 1 < length4) {
                _arr4[i + 1][j] = k;
                ++i;
            }

            ++k;
        }

        i = 0;
        j = static_cast<int>(length4 / 2);
        _arr2[i][j] = k;

        ++k;

        // Заполнение магического второго маленького квадрата
        while (k < pred3 + 1) {
            if (i - 1 >= 0 && j - 1 >= 0 && _arr2[i - 1][j - 1] == 0) {
                _arr2[i - 1][j - 1] = k;
                --i;
                --j;
            }
            else if (i - 1 >= 0 && j - 1 >= 0 && _arr2[i - 1][j - 1] != 0 && i + 1 < length4) {
                _arr2[i + 1][j] = k;
                ++i;
            }
            else if (i - 1 < 0 && j - 1 >= 0) {
                _arr2[length4 - 1][j - 1] = k;
                i = length4 - 1;
                --j;
            }
            else if (i - 1 >= 0 && j - 1 < 0) {
                _arr2[i - 1][length4 - 1] = k;
                --i;
                j = length4 - 1;
            }
            else if (i - 1 < 0 && j - 1 < 0 && _arr2[length4 - 1][length4 - 1] != 0 && i + 1 < length4) {
                _arr2[i + 1][j] = k;
                ++i;
            }

            ++k;
        }

        i = 0;
        j = static_cast<int>(length4 / 2);
        _arr3[i][j] = k;

        ++k;

        // Заполнение магического третьего маленького квадрата
        while (k < pred4 + 1) {
            if (i - 1 >= 0 && j - 1 >= 0 && _arr3[i - 1][j - 1] == 0) {
                _arr3[i - 1][j - 1] = k;
                --i;
                --j;
            }
            else if (i - 1 >= 0 && j - 1 >= 0 && _arr3[i - 1][j - 1] != 0 && i + 1 < length4) {
                _arr3[i + 1][j] = k;
                ++i;
            }
            else if (i - 1 < 0 && j - 1 >= 0) {
                _arr3[length4 - 1][j - 1] = k;
                i = length4 - 1;
                --j;
            }
            else if (i - 1 >= 0 && j - 1 < 0) {
                _arr3[i - 1][length4 - 1] = k;
                --i;
                j = length4 - 1;
            }
            else if (i - 1 < 0 && j - 1 < 0 && _arr3[length4 - 1][length4 - 1] != 0 && i + 1 < length4) {
                _arr3[i + 1][j] = k;
                ++i;
            }

            ++k;
        }

        // Меняем местами два крайних слева числа
        buff = _arr1[0][0];
        _arr1[0][0] = _arr3[0][0];
        _arr3[0][0] = buff;

        buff = _arr1[length4 - 1][0];
        _arr1[length4 - 1][0] = _arr3[length4 - 1][0];
        _arr3[length4 - 1][0] = buff;

        y = 1; // Отсчёт со второй строки

        // Замена на втором столбике
        while (y < length4 - 1) {
            buff = _arr1[y][1];
            _arr1[y][1] = _arr3[y][1];
            _arr3[y][1] = buff;

            ++y;
        }

        k = (n - 2) / 4 - 1; // Высчитывание, сколько столбиков сдвинется

        // Сдвигание столбиков
        if (k > 0) {
            while (k > 0) {
                for (int i = 0; i < length4; ++i) {
                    buff = _arr1[i][length4 - k];
                    _arr1[i][length4 - k] = _arr3[i][length4 - k];
                    _arr3[i][length4 - k] = buff;

                    buff = _arr2[i][k - 1];
                    _arr2[i][k - 1] = _arr4[i][k - 1];
                    _arr4[i][k - 1] = buff;
                }

                --k;
            }
        }

        // Из маленьких четырёх квадратов собирается магический квадрат
        for (int i = 0; i < length4; ++i) {
            for (int j = 0; j < length4; ++j) {
                magicSquare[i][j] = _arr1[i][j];
                magicSquare[i][j + length4] = _arr2[i][j];
                magicSquare[i + length4][j] = _arr3[i][j];
                magicSquare[i + length4][j + length4] = _arr4[i][j];
            }
        }

        for (long long int i = 0; i < length4; ++i) {
            free(_arr1[i]);
        }
        free(_arr1);

        for (long long int i = 0; i < length4; ++i) {
            free(_arr2[i]);
        }
        free(_arr2);

        for (long long int i = 0; i < length4; ++i) {
            free(_arr3[i]);
        }
        free(_arr3);

        for (long long int i = 0; i < length4; ++i) {
            free(_arr4[i]);
        }
        free(_arr4);
    }

    // Вывод магического квадрата
    if (n > 2) {
        std::cout << "\nМагический квадрат:\n\n";
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (n < 100) {
                    std::cout << std::setw(4) << magicSquare[i][j] << " ";
                }
                else {
                    std::cout << std::setw(10) << magicSquare[i][j] << " ";
                }
            }
            std::cout << std::endl;
        }
    }

    for (long long int i = 0; i < n; ++i) {
        free(magicSquare[i]);
    }
    free(magicSquare);
}
