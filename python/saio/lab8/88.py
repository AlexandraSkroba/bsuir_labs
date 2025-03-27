from collections import deque, defaultdict
import matplotlib.pyplot as plt
import networkx as nx


class MaxFlow:
    def __init__(self, vertices):
        self.graph = defaultdict(dict)  # Словарь для хранения графа с рёбрами и их пропускными способностями
        self.vertices = vertices  # Вершины графа

    def add_edge(self, u, v, capacity):
        # Добавление рёбер и их пропускных способностей
        self.graph[u][v] = capacity  # Пропускная способность прямого ребра
        self.graph[v][u] = 0  # Обратное ребро с нулевой пропускной способностью (по умолчанию)

    def bfs(self, source, sink, parent):
        # Поиск в ширину для нахождения (s, t)-пути
        visited = {v: False for v in self.vertices}  # Словарь для отслеживания посещённых вершин
        queue = deque([source])  # Инициализируем очередь BFS
        visited[source] = True  # Помечаем источник как посещённый

        while queue:
            u = queue.popleft()  # Извлекаем вершину из очереди

            for v in self.graph[u]:
                # Проверка, доступно ли ребро (положительная пропускная способность)
                if not visited[v] and self.graph[u][v] > 0:
                    queue.append(v)  # Добавляем вершину в очередь
                    visited[v] = True  # Помечаем как посещённую
                    parent[v] = u  # Запоминаем путь
                    if v == sink:  # Если достигли стока, возвращаем True
                        return True
        return False  # Если путь не найден, возвращаем False

    def ford_fulkerson(self, source, sink):
        parent = {v: None for v in self.vertices}  # Словарь для хранения пути
        max_flow = 0  # Инициализируем максимальный поток
        iteration = 0  # Счётчик итераций

        # Основной цикл, пока есть путь из источника в сток
        while self.bfs(source, sink, parent):
            iteration += 1
            # Находим минимальную пропускную способность по найденному пути
            path_flow = float('Inf')
            v = sink
            while v != source:  # Прослеживаем путь от стока к источнику
                u = parent[v]
                path_flow = min(path_flow, self.graph[u][v])
                v = u

            # Обновляем пропускные способности рёбер
            v = sink
            while v != source:
                u = parent[v]
                self.graph[u][v] -= path_flow
                self.graph[v][u] += path_flow
                v = u

            max_flow += path_flow  # Увеличиваем общий поток

            # Отладочная информация
            print(f"\nИтерация {iteration}:")
            print(f"  Найденный путь: {self.reconstruct_path(parent, source, sink)}")
            print(f"  Пропускная способность пути: {path_flow}")
            print(f"  Текущий максимальный поток: {max_flow}")
            print("  Остаточная сеть после обновления:")
            self.print_residual_graph()
            self.visualize_graph(title=f"Граф после итерации {iteration}")

        return max_flow

    # Вспомогательная функция для восстановления пути
    def reconstruct_path(self, parent, source, sink):
        path = []
        v = sink
        while v != source:
            path.append(v)
            v = parent[v]
        path.append(source)
        path.reverse()
        return path

    # Вспомогательная функция для вывода остаточной сети
    def print_residual_graph(self):
        for u in self.graph:
            for v, capacity in self.graph[u].items():
                if capacity > 0:
                    print(f"    {u} -> {v} : остаточная пропускная способность {capacity}")

    # Визуализация графа
    def visualize_graph(self, title="Граф"):
        G = nx.DiGraph()
        for u in self.graph:
            for v, capacity in self.graph[u].items():
                if capacity > 0:
                    G.add_edge(u, v, capacity=capacity)

        pos = nx.spring_layout(G)
        edge_labels = {(u, v): f"{d['capacity']}" for u, v, d in G.edges(data=True)}

        plt.figure(figsize=(8, 6))
        nx.draw(G, pos, with_labels=True, node_size=700, node_color="lightblue", font_size=10, font_weight="bold")
        nx.draw_networkx_edge_labels(G, pos, edge_labels=edge_labels)
        plt.title(title)
        plt.show()


# Пример использования
if __name__ == "__main__":
    # Создаем экземпляр класса
    vertices = ['s', 'a', 'b', 't']
    max_flow = MaxFlow(vertices)

    # Добавляем рёбра и их пропускные способности
    max_flow.add_edge('s', 'a', 3)
    max_flow.add_edge('s', 'b', 2)
    max_flow.add_edge('a', 'b', 1)
    max_flow.add_edge('a', 't', 2)
    max_flow.add_edge('b', 't', 2)

    # Визуализация начального графа
    max_flow.visualize_graph("Начальный граф")

    # Вычисляем максимальный поток
    source = 's'
    sink = 't'
    result = max_flow.ford_fulkerson(source, sink)

    # Визуализация графа после завершения алгоритма
    max_flow.visualize_graph("Граф после завершения алгоритма")

    # Вывод результата
    print(f"\nМаксимальный поток: {result}")
