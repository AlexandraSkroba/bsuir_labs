import numpy as np

#Двойственный симплекс-метод — это метод решения задач линейного программирования, который применяется,
# когда исходная задача не соответствует требованиям стандартного симплекс-метода из-за отрицательных
# элементов в векторе правых частей ограничений. Этот метод полезен когда решение удовлетворяет условиям базисности, но не допустимости

# вектор коэффициентов целевой функции. В контексте симплекс-метода это вектор,
# определяющий целевую функцию, которую мы хотим минимизировать или максимизировать.
# Каждый элемент этого вектора соответствует коэффициенту при соответствующей переменной в целевой функции.

#y - вектор двойственных переменных
#Допустимый план y двойственной задачи (2) называется
#базисным, если существует подмножество B множества индексов переменных

#x — допустимый план прямой задачи
# текущий оптимальный план решения обеспечивает наилучшее значение
# целевой функции удовлетворяет всем ограничениям задачи

#k - Псевдоплан
#вектор, который составлен из значений базисных переменных и нулей на местах небазисных переменных.
# Псевдоплан показывает текущее решение задачи.

#Базисный допустимый план — это такой план, при котором матрица ограничений преобразуется в единичную матрицу
# (или матрицу, которая может быть приведена к единичной), и все ограничения задачи удовлетворяются.

#B — множество базисных индексов начального базисного допустимого плана двойственной задачи
#Выход: x — оптимальный план прямой задачи (1) или сообщение о том, что
#прямая задача не совместна
def double_simplex(c, b, A, j):
    m, n = A.shape
    x_0 = [0 for _ in range(n)]
    j -= 1

    A_inv = np.linalg.inv(A[:, j])

    #Шаг 2. Сформируем вектор cB, состоящий из компонент вектора c с базисными индексами.
    #Шаг 3. Находим базисный допустимый план двойственной задачи y⊺ =c⊺BA−1B .
    y = (c[j]).dot(A_inv)
    print(y)

    iter = 1
    while True:
        print(f"-------------Iteration {iter}-------------")
        #Шаг 1. Составим базисную матрицу AB и найдем для нее обратную матрицу A−1B .
        j_n = np.delete(np.arange(n), j)
        A_inv = np.linalg.inv(A[:, j])
        print('A:\n', A_inv)
        print('A_inv:\n', A_inv)
        print('---------')

        #Шаг 4. Находим псевдоплан κ⊺ = (κB, κN), соответствующий текущему
        #базисному допустимому плану y, κB = A−1B b, κN = 0.
        k_b = A_inv.dot(b)
        print("k_b:", k_b)
        print('---------')

        #Шаг 5. Если κ ⩾ 0, то κ — оптимальный план прямой задачи (1) и метод завершает свою работу.
        if all(k_b >= 0):
            for j, copy in zip(j, k_b):
                x_0[j] = copy

            return x_0

        #Шаг 6. Выделим отрицательную компоненту псевдоплана κ и сохраним ее индекс. Этот индекс базисный jk ∈ B.
        ind = np.argmin(k_b)
        print('New index:', ind)
        print('---------')

        #Шаг 7. Пусть Δy — это k-я строка матрицы A−1B . Для каждого индекса
        #j ∈ {1, 2, . . . , n} \ B вычислим μj = Δy⊺Aj ,

        # представляет собой вычисляемый параметр на каждом шаге алгоритма, который используется для
        # определения направления движения к оптимальному решению и для проверки условий совместности задачи
        delta_y = A_inv[ind]
        mu = delta_y.dot(A)
        print('delta_y:', delta_y)
        print("mu:", mu)
        print('---------')
        print("y:", y)

        #Шаг 8. Если для каждого индекса j ∈ {1, 2, . . . , n} \ B выполняется μj ⩾ 0,
        #то прямая задача (1) не совместна и метод завершает свою работу.
        #Шаг 9. Для каждого индекса j ∈ {1, 2, . . . , n} \ B такого, что μj < 0 вычислим
        sigma = []
        for i in j_n:
            sigma.append(np.inf) if mu[i] >= 0 else sigma.append((c[i] - A[:, i].dot(y)) / mu[i])

        print("sigma:", sigma)
        print('---------')

        #Шаг 10. Найдем σ0 = min{σj : j ∈ {1, 2, . . . , n} \ B ∧ μj < 0}.
        #и сохраним индекс, на котором достигается минимум, в переменной j0.
        sigma_0_ind = j_n[np.argmin(sigma)]
        sigma_0 = min(sigma)

        print(f"sigma_val: {sigma_0}")
        print(f"sigma_index: {sigma_0_ind}")
        print('---------')

        if sigma_0 == np.inf:
            print("Прямая задача несовместна")
            return

        #Шаг 11. В множестве B заменим k-ый базисный индекс на индекс j0. Переходим на Шаг 1
        y += sigma_0 * delta_y
        j[ind] = sigma_0_ind

        iter += 1


if __name__ == "__main__":
    A = np.array([
        [-2, -1, -4, 1, 0],
        [-2, -2, -2, 0, 1]
    ])
    b = np.array([-1, -1.5])
    c = np.array([-4, -3, -7, 0, 0])
    B = np.array([4, 5])

    result = double_simplex(c, b, A, B)
    print("Result:", result)
