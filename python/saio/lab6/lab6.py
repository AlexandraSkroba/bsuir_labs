import networkx as nx
import matplotlib.pyplot as plt

# Паросочетание в двудольном графе

# Шаг 3: Использование поиска в ширину (BFS) для нахождения пути от s до t
def searching_algo_BFS(graph, s, t, parent):
    visited = [False] * len(graph)
    queue = []

    queue.append(s)
    visited[s] = True

    while queue:
        u = queue.pop(0)

        for ind, val in enumerate(graph[u]):
            if not visited[ind] and val > 0:
                queue.append(ind)
                visited[ind] = True
                parent[ind] = u

    return True if visited[t] else False


# Шаг 4: Формирование множества M после завершения алгоритма
def find_max_matching(graph, L, R):
    M = []
    # Проходим по рёбрам между долями V1 и V2
    for i in range(L + 1, L + R + 1):  # Вершины V2
        for j in range(1, L + 1):  # Вершины V1
            if graph[i][j] == 1:  # Если существует обратная дуга из V2 в V1
                M.append((j, i - L))  # Добавляем в паросочетание
                break
    return M


# Шаг 5: Основная функция для нахождения максимального паросочетания
def parosoch(graph, source, sink):
    parent = [-1] * len(graph)
    max_flow = 0
    steps = []

    # Пока есть путь из s в t, продолжаем
    while searching_algo_BFS(graph, source, sink, parent):
        path_flow = float("Inf")
        s = sink
        while s != source:
            path_flow = min(path_flow, graph[parent[s]][s])
            s = parent[s]

        max_flow += path_flow

        v = sink
        # Шаг 5: графе G∗ первую и последнюю дуги пути
        # P удалим, а остальным дугам этого пути поменяем ориентацию на противоположную
        while v != source:
            u = parent[v]
            graph[u][v] -= path_flow
            graph[v][u] += path_flow
            v = parent[v]
        steps.append(parent.copy())

    return max_flow, graph, steps

# Задан неориентированный двудольный граф G с долями V1 и V2
# Подмножество M множества ребер E(G) графа называется паросочетанием, если
# в нем нет двух ребер с общей концевой вершиной.
# Требуется реализовать алгоритм, который находит в графе G паросочетание с максимальным числом ребер.

edges = [(1, 5), (1, 6), (2, 6), (3, 7), (3, 8), (4, 5), (4, 7)]
L = 4  # Количество вершин в первой доле
R = 4  # Количество вершин во второй доле


# Шаг 1 и 2: Создание матрицы смежности для двудольного графа и добавление вершин s и t
def make_graph2d(edges, l, r):
    N = l + r + 2  # Общее количество вершин: левая доля + правая доля + источник и сток
    matrix = [[0] * N for _ in range(N)]  # Инициализация матрицы смежности

    # Соединяем источник (вершина 0) с вершинами первой доли (1..L)
    for i in range(1, l + 1):
        matrix[0][i] = 1

    # Соединяем вершины второй доли (L+1..L+R) со стоком (вершина N-1)
    for i in range(l + 1, l + r + 1):
        matrix[i][-1] = 1

    # Задаём рёбра между вершинами первой и второй долей
    for u, v in edges:
        matrix[u][v] = 1

    return matrix


# Создаём матрицу для графа
graph = make_graph2d(edges, L, R)

# Запуск алгоритма Форда-Фалкерсона для нахождения максимального паросочетания
par = parosoch(graph, 0, L + R + 1)
print(f'Максимальное число паросочетаний: {par[0]}')

# g = par[1]
# # Вывод паросочетаний
# print("Паросочетания:")
# for i in range(L + 1, L + R + 1):
#     for j in range(1, L + 1):
#         if g[i][j] == 1:
#             print(f"[ {j}, {i - L} ]")
#             break

# Шаг 4: Нахождение максимального паросочетания
max_matching = find_max_matching(par[1], L, R)
print("Паросочетания:")
for match in max_matching:
    print(f"[ {match[0]}, {match[1]} ]")

# ----------------------------------------------------
# Визуализация графа с использованием библиотеки NetworkX
G = nx.Graph()
V1 = ['p', 'q', 'r', 's']  # Вершины первой доли
V2 = ['u', 'v', 'w', 'x']  # Вершины второй доли

for u, v in edges:
    G.add_edge(V1[u - 1], V2[v - L - 1])

pos = {**{V1[i]: (0, i) for i in range(len(V1))}, **{V2[i]: (1, i) for i in range(len(V2))}}
nx.draw(G, pos, with_labels=True, node_size=3000, node_color="lightblue", font_size=12, font_color="black")
plt.show()
