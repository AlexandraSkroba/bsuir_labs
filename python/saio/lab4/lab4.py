import numpy as np
# Задача о целочисленном рюкзаке

def knapsack(v, c, B):  # v = v, c = c, B = B
    n = len(v)  # n различных предметов
    # dp[i][b] хранит максимальную ценность для первых i предметов и вместимости рюкзака b
    dp = [[0] * (B + 1) for _ in range(n + 1)]

    for i in range(1, n + 1):  # Перебираем каждый предмет
        for b in range(1, B + 1):  # Перебираем каждую возможную вместимость рюкзака
            if v[i - 1] <= b:  # Если объем текущего предмета меньше или равен b
                # Выбираем максимум: взять предмет или нет
                dp[i][b] = max(dp[i - 1][b], c[i - 1] + dp[i - 1][b - v[i - 1]])
            else:
                dp[i][b] = dp[i - 1][b]  # Если предмет не помещается, то оставляем предыдущий максимум

    selected_items = []  # Список для хранения выбранных предметов
    i, b = n, B
    # Обратный проход для восстановления набора выбранных предметов
    while i > 0 and b > 0:
        if dp[i][b] != dp[i - 1][b]:  # Если предмет был выбран
            selected_items.append(i - 1)  # Добавляем индекс предмета
            b -= v[i - 1]  # Уменьшаем оставшуюся вместимость
        i -= 1

    selected_items.reverse()  # Предметы восстановлены в обратном порядке, поэтому нужно развернуть список
    print('   0  1  2  3  4  5  6  7  8')
    print(np.array(dp))
    return dp[n][B], selected_items  # Возвращаем максимальную ценность и список выбранных предметов


# Пример использования
v = [2, 3, 4, 5]  # объемы предметов (v)
c = [3, 4, 5, 6]  # ценности предметов (c)
B = 8  # вместимость рюкзака (B)
# В рюкзак можно поместить
# предметы, суммарный объем которых не превосходит B.

max_value, selected_items = knapsack(v, c, B)

print("Максимальная ценность:", max_value)
print("Выбранные предметы (индексы):", selected_items)
