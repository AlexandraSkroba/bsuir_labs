import matplotlib.pyplot as plt
from tkinter import *
from tkinter import messagebox
import numpy as np

# Генератор псевдослучайных чисел
class LCG:
    def __init__(self, seed, a=1664525, c=1013904223, m=2**32):
        self.seed = seed  # Начальное значение
        self.a = a        # Множитель
        self.c = c        # Приращение
        self.m = m        # Модуль
        self.current = seed

    def random(self):
        self.current = (self.a * self.current + self.c) % self.m
        return self.current / self.m

# Создаем объединенный графический интерфейс
def create_gui():
    root = Tk()
    root.title("Лабораторная работа 1 и симулятор событий")
    root.geometry("500x600")

    # Заголовок
    title = Label(root, text="Лабораторная работа 1", font=("Arial", 14))
    title.pack(pady=10)

    # Вкладки для выбора одного события или нескольких
    notebook = Frame(root)
    notebook.pack(pady=10)

    single_event_frame = Frame(notebook)
    multiple_events_frame = Frame(notebook)

    def show_frame(frame):
        frame.tkraise()

    # Размещение фреймов с помощью pack
    for frame in (single_event_frame, multiple_events_frame):
        frame.pack(fill="both", expand=True)

    # =================== Одиночное событие ===================
    # Ввод начального значения (seed)
    seed_label_single = Label(single_event_frame, text="Введите начальное значение (seed):", font=("Arial", 10))
    seed_label_single.pack()
    seed_entry = Entry(single_event_frame, width=30)
    seed_entry.pack(pady=5)
    seed_entry.insert(0, "33")  # Значение по умолчанию

    # Ввод вероятности
    prob_label_single = Label(single_event_frame, text="Введите вероятность (от 0 до 1):", font=("Arial", 10))
    prob_label_single.pack()
    prob_entry_single = Entry(single_event_frame, width=30)
    prob_entry_single.pack(pady=5)

    # Функция симуляции одиночного события и вывода результатов
    def run_single_event_simulation():
        try:
            seed = int(seed_entry.get())
            probability = float(prob_entry_single.get())
            events_count = 10**6

            if not (0 <= probability <= 1):
                raise ValueError

            lcg = LCG(seed=seed)
            count_true = sum(1 for _ in range(events_count) if lcg.random() <= probability)
            count_false = events_count - count_true
            empirical_probability = count_true / events_count

            result_label_single.config(text=f"Эмпирическая вероятность: {empirical_probability:.6f}")

            # Создание графика для одиночного события
            labels = ['True', 'False']
            percentages = [count_true / events_count, count_false / events_count]
            plt.figure(figsize=(4, 4))
            bars = plt.bar(labels, percentages, color=['lightblue', 'orange'])

            for bar in bars:
                height = bar.get_height()
                plt.text(bar.get_x() + bar.get_width() / 2.0, height, f'{height:.4f}%', ha='center', va='bottom')

            plt.xlabel('Результат')
            plt.ylabel('Процент')
            plt.ylim(0, 1)
            plt.grid(axis='y', linestyle='--', alpha=0.5)
            plt.show()

        except ValueError:
            messagebox.showerror("Ошибка", "Неверный ввод. Проверьте значения и попробуйте снова.")

    # Кнопка для запуска симуляции одиночного события
    run_button_single = Button(single_event_frame, text="Запустить симуляцию", command=run_single_event_simulation)
    run_button_single.pack(pady=10)

    # Место для вывода результата одиночного события
    result_label_single = Label(single_event_frame, text="", font=("Arial", 10))
    result_label_single.pack(pady=10)

    # =================== Несколько событий ===================

    # Ввод количества событий
    count_label = Label(multiple_events_frame, text="Введите количество событий:", font=("Arial", 10))
    count_label.pack()
    count_entry = Entry(multiple_events_frame, width=30)
    count_entry.pack(pady=5)

    # Поле для ввода вероятностей
    probabilities_entries = []

    def add_probability_inputs():
        try:
            num_events = int(count_entry.get())
            for entry in probabilities_entries:
                entry.pack_forget()
            probabilities_entries.clear()

            for i in range(num_events):
                prob_label = Label(multiple_events_frame, text=f"Введите вероятность для события {i + 1} (от 0 до 1):", font=("Arial", 10))
                prob_label.pack()
                prob_entry = Entry(multiple_events_frame, width=30)
                prob_entry.pack(pady=5)
                probabilities_entries.append(prob_entry)

        except ValueError:
            messagebox.showerror("Ошибка", "Введите корректное количество событий.")

    # Кнопка для добавления полей ввода вероятностей
    add_button = Button(multiple_events_frame, text="Добавить вероятности", command=add_probability_inputs)
    add_button.pack(pady=10)

    # Функция симуляции нескольких событий и вывода результатов
    def run_multiple_events_simulation():
        try:
            seed = int(seed_entry.get())
            num_events = int(count_entry.get())
            probabilities = [float(entry.get()) for entry in probabilities_entries]

            if any(not (0 <= p <= 1) for p in probabilities):
                raise ValueError

            lcg = LCG(seed=seed)

            # Моделирование событий
            def simulate_event(probabilities):
                results = []
                for i in range(len(probabilities)):
                    results.append(lcg.random() <= probabilities[i])
                return results

            values = 1000000  # Количество симуляций
            count = [{True: 0, False: 0} for _ in range(len(probabilities))]

            for i in range(values):
                res = simulate_event(probabilities)
                for j in range(len(res)):
                    count[j][res[j]] += 1

            empirical_probability = []
            for i in count:
                empirical_probability.append(i[True] / (i[True] + i[False]))

            # Создание графика для нескольких событий
            labels = [f'Event {i+1}' for i in range(len(empirical_probability))]
            plt.figure(figsize=(6, 4))
            bars = plt.bar(labels, empirical_probability, color='lightblue')

            for bar in bars:
                height = bar.get_height()
                plt.text(bar.get_x() + bar.get_width() / 2.0, height, f'{height:.4f}', ha='center', va='bottom')

            plt.xlabel('События')
            plt.ylabel('Эмпирическая вероятность')
            plt.ylim(0, 1)
            plt.grid(axis='y', linestyle='--', alpha=0.5)
            plt.show()

        except ValueError:
            messagebox.showerror("Ошибка", "Введите корректные значения.")

    # Кнопка для запуска симуляции нескольких событий
    run_button_multiple = Button(multiple_events_frame, text="Запустить симуляцию", command=run_multiple_events_simulation)
    run_button_multiple.pack(pady=10)

    # Начальная вкладка (отображение)
    show_frame(single_event_frame)

    root.mainloop()

# Запуск интерфейса
create_gui()
