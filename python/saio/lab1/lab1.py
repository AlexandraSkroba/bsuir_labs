# Метод ветвей и границ
import numpy as np
from numpy import *
import math

def double_simplex(c, b, a_matrix, j_vector):
    m, n = a_matrix.shape
    iter_count = 1
    j_vector -= 1
    y = get_initial_y(c, a_matrix, j_vector)
    x_0 = [0 for _ in range(n)]

    while True:
        not_J = delete(arange(n), j_vector)
        B = linalg.inv(a_matrix[:, j_vector])
        kappa = B.dot(b)

        if all(kappa >= 0):
            for j, _kappa in zip(j_vector, kappa):
                x_0[j] = _kappa
            print("Оптимальный план задачи: ", list(map(lambda _x: round(float(_x), 3), list(x_0))))
            return list(map(lambda _x: round(float(_x), 3), list(x_0)))

        k = argmin(kappa)
        delta_y = B[k]
        mu = delta_y.dot(a_matrix)

        sigma = []
        for i in not_J:
            if mu[i] >= 0:
                sigma.append(inf)
            else:
                sigma.append((c[i] - a_matrix[:, i].dot(y)) / mu[i])

        sigma_0_ind = not_J[argmin(sigma)]
        sigma_0 = min(sigma)

        if sigma_0 == inf:
            return "Задача не имеет решения" # множество её допустимых планов пусто

        y += sigma_0 * delta_y
        j_vector[k] = sigma_0_ind
        iter_count += 1


def get_initial_y(c, a_matrix, j_vector):
    return (c[j_vector]).dot(linalg.inv(a_matrix[:, j_vector]))


# Требуется определить совместна ли задача и в случае положительного
# ответа найти оптимальный план
def main():
    c_d = np.array([1, 1])
    A = np.array([[5, 9], [9, 5]])
    b_0 = np.array([63, 63])
    d_m = np.array([1, 1])
    d_p = np.array([6, 6])
    x_0 = np.array([0, 0])

    c_init = np.copy(c_d)

    print("---- ШАГ1. Преобразуем задачу таким образом, чтобы c ⩽ 0. Для каждого"
          "индекса i ∈ {1, 2, . . . , n} такого, что ci > 0")
    i = None
    for idx in range(len(c_d)):
        # в векторе c i-ую компоненту умножим на −1
        if c_d[idx] > 0:
            c_d[idx] *= -1
            i = idx + 1  # запоминаем, какую по счету компоненту изменили

        # если нашли компоненту > 0, продолжаем работу
        if i is not None:
            # Умножаем i-ый столбец матрицы A на -1
            A[:, i - 1] *= -1

            # Умножаем i-ую компоненту векторов d_m и d_p на -1
            d_m[i - 1] *= -1
            d_p[i - 1] *= -1

            # Меняем местами i-ые компоненты векторов d_m и d_p
            d_m[i - 1], d_p[i - 1] = d_p[i - 1], d_m[i - 1]

    n = len(A[0])
    m = len(A)
    print(f"n = {n}, m = {m}")

    print("---- ШАГ2. Отбросим условие целочисленности на переменные и приведем "
          "полученную задачу линейного программирования\n\t\t   в каноническую форму без учета "
          "ограничений неотрицательности")
    c_1 = np.concatenate([c_d, [0] * (len(A[0]) + len(A))])
    b_1 = np.concatenate([b_0, d_p])
    d_1_minus = np.concatenate([d_m, [0] * (len(A[0]) + len(A))])
    A = np.hstack([np.vstack([A, np.eye(len(A[0]))]), np.eye(len(A[0]) + len(A))])

    print("Вектор с: ", c_1)
    print("Вектор b:", b_1)
    print("Вектор d_minus:", d_1_minus)
    print("Матрица A:\n", A)
    print("---------------------------------------------------")

    print("---- ШАГ3. Создадим переменные x_star, r и пустой стек S. В переменной x_star будем "
          "хранить\n\t\t   наилучший допустимый целочисленный план задачи (2). "
          "Значение целевой функции задачи (2) на плане x_star\n\t\t   будем хранить в переменной r, т.е. "
          "r = c*x_star. Поместим в стек S задачу (2) вместе с вектором Δ = d−")
    x_star = []
    r = 0
    S = []
    alpha = 0
    S.append([d_1_minus, b_1, alpha, d_1_minus])

    print("---- ШАГ4. Очень большой пункт из 2-х случаев")
    iter_count = 0
    while S:
        iter_count = iter_count + 1
        print(f"\n===== Итерация {iter_count} =====")
        D = S.pop() # Извлечем из стека S задачу линейного программирования с вектором Δ = d_minus

        alpha_shtr = D[2] + np.dot(c_1, D[0]) # α′ = α + c*d_minus
        b_shtr = np.array(D[1] - np.dot(A, D[0])) # b′ = b − A*d_minsu

        print("Вектор дельта:", D[3])
        print("Альфа:", alpha_shtr)
        print("Новый вектор b:", b_shtr)

        # Создаем и заполняем вектор j для начального базисный двойственного плана
        j = np.array([0] * (n + m))
        for i in range(0, len(j)):
            j[i] = n + i + 1

        # Решим задачу двойственным симплекс-методом
        x_voln = double_simplex(c_1, b_shtr, A, j)
        if x_voln == "Задача не имеет решения":
            print("Задача не имеет решения")
            continue

        #Рассмотрим два случая в зависимости от того является план ex целочисленным или нет.
        flg = 1
        for i in range(0, len(x_voln)):
            if not (float(x_voln[i]) == int(x_voln[i])): #Выберем дробную компоненту exi из числа первых n компонент плана ex.
                flg = 0
                if (not x_star) or (math.floor(np.dot(c_1, x_voln)) > r): # построим две новые задачи линейного программирования
                    b_two_shtr = np.copy(b_shtr)
                    b_two_shtr[m + i] = math.floor(x_voln[i])
                    d_zero = np.array([0] * (2 * n + m))
                    S.append([d_zero, b_two_shtr, alpha_shtr, D[3]])
                    d_zero[i] = math.ceil(x_voln[i])
                    S.append([d_zero, b_shtr, alpha_shtr, D[3] + d_zero])
                break

        # По этому плану восстановим допустимый план задачи (2) следующим образом.
        if flg == 1:
            x_final = x_voln + D[3] #Прибавим к плану ex вектор Δ
            if (not x_star) or (np.dot(c_1, x_final) + alpha_shtr > r):
                x_star = x_final
                r = np.dot(c_1, x_final) + alpha_shtr

    print("\nДопустимый целочисленный план:", x_star)
    print("r:", r)

    # возвратим оптимальный план x задачи (1), восстановленный по x∗, следующим образом
    for i in range(0, len(x_0)):
        if c_init[i] < 0:
            x_0[i] = x_star[i]
        else:
            x_0[i] = -x_star[i]

    print("Оптимальный план задачи:", x_0)


if __name__ == "__main__":
    main()


