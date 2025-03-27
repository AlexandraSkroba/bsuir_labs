/*»з величин, определ€емых выражени€ми a = sinx, b = cosx, c = ln | x |
при заданном х, определить и вывести на экран диспле€ минимальное
значение.Ѕиблиотеку <cmath> использовать запрещено.*/

#include <iostream>
#include <cmath>

int main() {

    double i = 1, ln = 0, x, z, powe = 1, y, x1;

    do {
        std::cout << "Enter x: ";
        std::cin >> x;
    } while (x <= 0);

    x1 = x;

    z = (x + 1) / (x - 1);

    double step = ((x - 1) * (x - 1)) / ((x + 1) * (x + 1));

    while (i <= 150) {
        z *= step;
        y = (1 / powe) * z;
        ln = ln + y;
        powe = powe + 2;
        i++;
    }

    std::cout << "\nln(x) = " << 2 * ln;
    std::cout << "\n(cmath) ln(x) = " << log(x1);

    return 0;
}