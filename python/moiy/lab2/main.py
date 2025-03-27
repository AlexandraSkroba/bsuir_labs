import numpy as np

if __name__ == '__main__':
    # m, n = map(int, input("Введите количество m строк и n столбцов, для матрицы A: ").split())
    # print(f'm = {m}, n = {n}')

    m = 3
    n = 5

    # Создаем матрицу A, заполненную случайными целыми значениями от -1 до 1
    # A = np.random.randint(-1, 2, size=(m, n))

    A = np.array([[-1, 1, 1, 0, 0],
                    [1, 0, 0, 1, 0],
                    [0, 1, 0, 0, 1]])

    print("Матрица A:")
    print(A)

    # B = np.random.permutation(np.arange(1, n + 1))[:m]  # Создаем вектор B, заполненный случайными значениями от 1 до n, не повторяющимися
    # B.sort()
    det_T = -1
    i = 1

    while det_T <= 0:
        B = np.array([[3, 4, 5]])

        print("Вектор B:")
        print(B)

        print(f'-----Итерация {i}-----')
        # ШАГ1. Строим базисную матрицу AB и находим ее обратную матрицу
        AB = A[:, B.flatten() - 1]  # Выбираем столбцы матрицы A с помощью среза

        print("Матрица AB:")
        print(AB)

        det = np.linalg.det(AB)  # Вычисляем определитель
        if det != 0:  # Проверяем, что определитель не равен нулю
            AB_inv = np.linalg.inv(AB)  # Находим обратную матрицу
            print("Обратная матрица к AB:")
            print(AB_inv)
        else:
            print("Матрица AB вырождена, обратной матрицы не существует.")

        # ШАГ2. Формируем вектор cB — вектор компонент вектора c, чьи индексы принадлежат множеству B;
        cT = np.array([[1, 1, 0, 0, 0]])
        xT = np.array([[0, 0, 1, 3, 2]])

        print('Вектор коэффициентов')
        print(cT)

        cB = cT[:, B.flatten() - 1]

        print("Вектор cB:")
        print(cB)

        # ШАГ3. Находим вектор потенциалов uT = cT * AB_inv
        uT = cB @ AB_inv

        print('Вектор потенциалов: ')
        print(uT)

        # ШАГ4. Находим вектор оценок det_T = uT * A − cT;
        det_T = uT @ A - cT

        print('Вектор оценок:')
        print(det_T)

        j = 1
        det_Tj = int(det_T[0, j - 1])
        print(f'det_Tj = {det_Tj}')
        print(f'j = {j}')

        Aj = A[:, j - 1]

        z = AB_inv @ Aj
        print(z)

        if z[0] == -1:
            tet_1 = np.inf
        else:
            tet_1 = z[0]

        if z[1] > 0:
            tet_2 = xT[0, (B[0, 1] - 1)] / z[1]

        if z[2] <= 0:
            tet_3 = np.inf
        else:
            tet_3 = z[2]

        tet_T = np.array([tet_1, tet_2, tet_3])
        print(f'θ⊺ = {tet_T}')

        # Находим индекс минимального элемента вектора tet_T
        tet_min = np.min(tet_T)
        k = np.argmin(tet_T) + 1
        print(k)

        # Находим индекс j* по формуле
        j_star = B[0, k] - 1

        print(f'k = {k}, j* = {j_star}')

        # Обновляем базисные индексы
        B[0, k - 1] = j

        print("Обновленный вектор B:")
        print(B)

        # Обновляем компоненты текущего плана x
        xT[0, j - 1] = tet_min  # xj0 = θ0
        xT[0, (B[0, 0] - 1)] -= tet_min * z[0]
        xT[0, (B[0, 2] - 1)] -= tet_min * z[2]
        xT[0, j_star -1] = 0


        print("Обновленный вектор x:")
        print(xT)
