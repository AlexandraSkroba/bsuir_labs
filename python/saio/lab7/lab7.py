import numpy as np
from lab7.main import get_max_matching

UPPER_VERTEX = 'v'
LOWER_VERTEX = 'u'

# Реализовать метод решения задачи о назначениях.
# Задача о назначениях заключается в том, чтобы в сбалансированном полном двудольном графе с целочисленными
# весами на ребрах найти паросочетание из n ребер, сумма весов которых минимальна.
# Матричный вариант задачи о назначениях состоит в том, чтобы в целочис-
# ленной квадратной матрице порядка n выбрать n элементов таким образом,
# чтобы, во-первых, в каждой строке и в каждом столбце матрицы был выбран
# ровно один элемент и, во-вторых, сумма выбранных элементов была минимальна.

# Использование поиска в глубину
def dfs(visited: set, graph: dict, node: str) -> set:
    visited.add(node)

    if node not in graph.keys():
        return visited

    for adjacent in (x for x in graph[node] if x not in visited):
        return dfs(visited, graph, adjacent)

    return visited


# Функция для построения матрицы смежности для двудольного графа
def build_adjacent_matrix_from_dict(graph, n):
    matrix = np.zeros((2 * n, 2 * n))

    for u in graph.keys():
        for v in graph[u]:
            u_idx = int(u.replace(UPPER_VERTEX, ''))
            v_idx = int(v.replace(LOWER_VERTEX, '')) + n  # Вершины нижней доли смещаем
            matrix[u_idx, v_idx] = 1
            matrix[v_idx, u_idx] = 1

    return matrix


def dual_based_proc(c: np.ndarray):
    # Шаг 1. Находим допустимый план αi, βi (i ∈ {1, 2, . . . , n}) задачи, двойственной задаче о назначениях
    n = c.shape[0]
    iter = 1

    # Шаг 1. Инициализация плана alpha и beta
    # alpha_i = 0 для всех i, beta_j = минимальное значение в j-ом столбце матрицы C
    alphas = [0 for i in range(n)]
    betas = [min(c[:, i]) for i in range(n)]

    print("alphas: ", alphas)
    print("betas: ", betas)

    while True:
        print("============ Итерация ", iter, " ============")
        # Шаг 2. Найти множество пар индексов J=, где alpha_i + beta_j = C_ij
        J_equal = [(i, j) for i, alpha in enumerate(alphas) for j, beta in enumerate(betas) if alpha + beta == c[i, j]]
        print('J=: ', J_equal)

        # Шаг 3. Построим двудольный граф G с долями V1 = {u1, u2, . . . , un} и
        # V2 = {v1, v2 . . . , vn}. При этом в графе G есть ребро, соединяющее вершины ui
        # и vj , тогда и только тогда, когда пара (i, j) принадлежит множеству J=.
        graph = {str(f'{UPPER_VERTEX}{k[0]}'): [] for k in J_equal}
        for i in J_equal:
            graph[str(f'{UPPER_VERTEX}{i[0]}')].append(str(f'{LOWER_VERTEX}{i[1]}'))
        # Построение матрицы смежности для двудольного графа
        adjacent_matrix = build_adjacent_matrix_from_dict(graph, n)

        # Шаг 4. Поиск максимального паросочетания в графе G
        max_matching = get_max_matching(adjacent_matrix)

        # Шаг 5. Если размер паросочетания равен n, искомый набор позиций в матрице определяется
        # паросочетанием M, совокупность позиций задает оптимальное решение задачи о назначениях
        if len(max_matching) == n:
            return [(i, j - n) for i, j in max_matching]

        # Шаг 6. Если |M| < n, Берем направленный граф G* и в
        # нем находим вершины, достижимые из вершины s
        start_v = set(f'{UPPER_VERTEX}{i}' for i in range(n)) - set(f'{UPPER_VERTEX}{i}' for i, j in max_matching)
        v_star = set()
        for v in start_v:
            v_star = v_star.union(dfs(set(), graph, v))

        # Шаг 7. Формирование множеств I* и J*
        I_star = set(int(v.replace(UPPER_VERTEX, '')) for v in v_star if UPPER_VERTEX in v)
        J_star = set(int(u.replace(LOWER_VERTEX, '')) for u in v_star if LOWER_VERTEX in u)

        print("\nI_star: ", I_star)
        print("J_star: ", J_star)

        # Шаг 8. Определение новых alpha_capped и beta_capped
        # Находим допустимый план задачи, двойственной ограниченной прямой задачи
        alphas_capped = [1 if i in I_star else -1 for i in range(n)]
        betas_capped = [-1 if i in J_star else 1 for i in range(n)]

        print("\nalphas_capped: ", alphas_capped)
        print("betas_capped: ", betas_capped)

        # Шаг 9. Нахождение величины theta, минимум берется по всем парам индексов (i, j) таким, что i ∈ I∗ и j /∈ J∗
        theta = min((c[i, j] - alphas[i] - betas[j]) / 2 for i in I_star for j in set(range(n)) - J_star)

        print("theta: ", theta)

        # Шаг 10-11. Находим новый допустимый план. Новый план объявляем текущим
        alphas = [alpha + theta * alphas_capped[i] for i, alpha in enumerate(alphas)]
        betas = [beta + theta * betas_capped[i] for i, beta in enumerate(betas)]

        print("\nalphas: ", alphas)
        print("betas: ", betas)


if __name__ == '__main__':
    # Целочисленная квадратная матрица C порядка n
    C = np.array([
        [7, 2, 1, 9, 4],
        [9, 6, 9, 5, 5],
        [3, 8, 3, 1, 8],
        [7, 9, 4, 2, 2],
        [8, 4, 7, 4, 8],
    ])

    # Запуск Венгерского алгоритма для задачи о назначениях
    indexes = dual_based_proc(C)

    # Вывод результатов
    # Позиции в матрице C, которые определяют решение задачи о назначениях
    print('Indexes: ', indexes)
    print('Minimum cost:', sum(C[i, j] for (i, j) in indexes))
