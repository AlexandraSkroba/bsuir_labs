import numpy as np

def dot(A, B, index):
    C = np.zeros(A.shape)
    for i in range(len(A)):
        for j in range(len(A)):
            C[i][j] += A[i][index] * B[index][j]
            if i != index:
                C[i][j] += B[i][j]

    return C


def find_inv(A_inv: np.array, x: np.array, index: int):
    l = A_inv @ x
    if l[index] == 0:
        return False

    l_wave = np.copy(l)
    l_wave[index] = -1.
    l_hat = -1. / l[index] * l_wave

    Q = np.identity(len(x))
    Q[:, index] = l_hat

    return dot(Q, A_inv, index)


def solve_simplex(c: np.array, A: np.array, x: np.array, B=None):
    i = 0
    while True:
        if i == 0 and B is None:
            B = np.nonzero(x)[0]

        A_B = A[:, B]
        if i == 0:
            A_B_inv = np.linalg.inv(A_B)
        else:
            A_B_inv = find_inv(A_B_inv, A[:, j_0], k)

        c_B = c[B]
        u = c_B @ A_B_inv
        delta = u @ A - c

        if (delta >= 0).all():
            return x, B

        j_0 = np.argmax(delta < 0)
        z = A_B_inv @ A[:, j_0]
        theta = np.empty(len(z))

        for i in range(len(z)):
            if z[i] > 0:
                theta[i] = x[B[i]] / z[i]
            else:
                theta[i] = np.Inf

        theta_0 = np.min(theta)

        if theta_0 == np.inf:
            raise ValueError('Целевой функционал задачи не ограничен сверху на множестве допустимых планов')

        k = np.argmin(theta)
        j_asterisk = B[k]
        B[k] = j_0
        x[j_0] = theta_0

        for i in range(len(B)):
            if i == k:
                continue
            x[B[i]] -= theta_0 * z[i]
        x[j_asterisk] = 0

        i += 1


def solve_simplex_initial(c: np.array, A: np.array, b: np.array):
    n = len(c)
    m = len(b)
    assert A.shape == (m, n)

    for i in range(len(b)):
        if b[i] < 0:
            b[i] *= -1
            A[i] *= -1

    c_wave = np.array([0] * n + [-1] * m)
    x_wave = np.zeros(n + m)
    A_wave = np.hstack((A, np.eye(A.shape[0])))

    x_wave[n:] = b
    B = np.array([i for i in range(n, n + m)])

    x_wave, B = solve_simplex(c_wave, A_wave, x_wave, B)

    if not (x_wave[n:] == 0).all():
        raise ValueError('Задача несовместна')

    x = x_wave[:n]

    while True:
        if (B < n - 1).all():
            return x

        k = B.argmax()
        j_k = B[k]
        i = j_k - n

        l = np.ones([n, m])
        l[:, :] = np.nan

        for j in range(n):
            if j not in B:
                l[j] = np.linalg.inv(A_wave[:, B]) @ A_wave[:, j]

        found_nonzero = False
        for j, l_j in enumerate(l):
            if not np.isnan(l_j[k]) and l_j[k] != 0:
                B[k] = j
                found_nonzero = True
                break

        if not found_nonzero:
            B = np.delete(B, k)
            A = np.delete(A, i, axis=0)
            A_wave = np.delete(A_wave, i, axis=0)
            b = np.delete(b, i)
            A_wave = np.delete(A_wave, n + i, axis=1)
            c_wave = np.delete(c_wave, n + i)

# Отсекающее ограничение Гомори

# Метод отсекающих ограничений Гомори предназначен для решения задач
# целочисленного линейного программирования

c = np.array([0, 1, 0, 0]) # вектор стоимостей
A = np.array([      # матрица коэффициентов размера m×n, состоящая из целых чисел
    [3, 2, 1, 0],
    [-3, 2, 0, 1]
])
b = np.array([6, 0]) # вектор свободных членов (вектор правых частей)


# На выходе метод возвращает либо оcотсекающее ограничение Гомори, которое необходимо добавить к задаче,
# либо оптимальный план задачи,
# либо сообщение о том, что задача несовместна/её целевая функция неограничена сверху
# на множестве допустимых планов
def solve(c, A, b):
    # c (коэффициенты целевой функции), A (матрица коэффициентов ограничений) и b (вектор правых частей ограничений).
    print('---- Шаг 1. Решаем симплекс-методом задачу линейного программирования,'
          'которая получается из задачи ЦЛП \n\t\t\tотбрасыванием условий целочисленности'
          'на переменные.')
    x = solve_simplex_initial(c, A, b)
    print("Оптимальный план:", x)

    x_is_int = np.isclose(x, x.astype(int), 10 ** -3)
    if np.all(x_is_int):
        print(x)
        return x

    x, B = solve_simplex(c, A, x)
    print("Упорядоченный набор базисных индексов:", B)

    print('\n---- Шаг 2. Если симплекс-метод завершил работу и сообщил о том, что задача линейного программирования '
          'несовместна или \n\t\t\tеё целевая функция не ограничена сверху на множестве допустимых планов, '
          'то метод завершает свою работу и \n\t\t\tвозвращает ответ: «задача ЦЛП несовместна или её целевая функция'
          'неограничена сверху на множестве допустимых планов»')

    print('\n---- Шаг 3. Если симплекс-метод вернул оптимальный план x (вместе с упорядоченным набором базисных индексов B) '
          '\n\t\t\tи план x состоит только из целых чисел, то метод завершает свою работу и возвращает план x '
          '\n\t\t\tв качестве оптимального плана задачи ЦЛП.')

    print('\n---- Шаг 4. Если симплекс-метод вернул оптимальный план x (вместе с упорядоченным набором базисных индексов B) '
          '\n\t\t\tи в плане x есть дробные компоненты, то строим отсекающее ограничение Гомори следующим образом.')

    print('\n---- Шаг 5. Находим дробную компоненту в оптимальном плане x. Её индекс базисный.')

    float_idx = np.argmin(x_is_int) # Нахождение индекса первой небазисной переменной, которая не является целым числом.
    k = np.argmax(B == float_idx) # Нахождение индекса переменной в базисе, которая соответствует найденной небазисной переменной.
    print('k =', k)

    print('\n---- Шаг 6. Строим базисную и небазисную матрицы.')

    # Создание списка N, который содержит индексы переменных, не входящих в базис.
    # Эти индексы представляют небазисные переменные.
    N = [i for i in range(len(x)) if i not in B]

    A_B = A[:, B] # Извлечение из матрицы A только тех столбцов, которые соответствуют базисным переменным.
    A_N = A[:, N] # Извлечение из матрицы A только тех столбцов, которые соответствуют небазисным переменным.
    print('Базисная матрица:\n', A_B)
    print('Небазисная матрица:\n', A_N)

    print('\n---- Шаг 7. Разбиваем набор переменных x базисные и небазисные.')
    print(B, N)

    print('\n---- Шаг 8-9. Обращаем базисную матрицу и находим произведение '
          '\n\t\t\t  обратной матрицы базисных переменных на матрицу небазисных переменных.')
    Q = np.linalg.inv(A_B) @ A_N
    print(Q)

    print('\n---- Шаг 10. Выделим в матрице Q строку ℓ, которая идёт k-ой по счёту')
    l = Q[k, :]
    print("l = ",l)

    print('\n---- Шаг 11. Найдем отсекающее ограничение')

    print('Найдём дробные части элементов этой строк')
    l_floats = l - np.floor(l)
    print(l_floats)

    # Нулевой вектор l_result длиной, равной длине вектора x плюс один элемент для добавления новой переменной.
    l_result = np.zeros(len(x) + 1)
    l_result[-1] = -1
    l_result[N] = l_floats

    x_k = x[k] - int(x[k])
    print('Вектор коэффициентов при переменных:', l_result) # дополнительное линейное неравенство, которое добавляется к исходной задаче,
                                                            # чтобы «отрезать» текущее дробное решение симплекс-метода и
                                                            # приблизиться к целочисленному решению
    print('Cвободный член:', x_k) # Дробная часть базисной переменной, которая используется для формирования нового ограничения
    return l_result, x_k


solve(c, A, b)
