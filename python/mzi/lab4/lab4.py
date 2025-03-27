import random
import numpy as np

# Проверочная матрица для кода Хэмминга (7,4)
H = np.array([[1, 0, 1, 0, 1, 0, 1],
              [0, 1, 1, 0, 0, 1, 1],
              [0, 0, 0, 1, 1, 1, 1]])

# Генераторная матрица для кода Хэмминга (7,4)
G = np.array([[1, 1, 0, 1],
              [1, 0, 1, 1],
              [1, 0, 0, 0],
              [0, 1, 1, 1],
              [0, 1, 0, 0],
              [0, 0, 1, 0],
              [0, 0, 0, 1]])

# Матрица восстановления информации (выбор первых 4 бит из 7)
R = np.array([[0, 0, 1, 0, 0, 0, 0],
              [0, 0, 0, 0, 1, 0, 0],
              [0, 0, 0, 0, 0, 1, 0],
              [0, 0, 0, 0, 0, 0, 1]])

# Генерация случайной обратимой бинарной матрицы размерности n x n
def random_binary_non_singular_matrix(n):
    a = np.random.randint(0, 2, size=(n, n))
    while np.linalg.det(a) == 0:  # Проверка на обратимость (определитель не должен быть 0)
        a = np.random.randint(0, 2, size=(n, n))
    return a

# Случайная обратимая матрица для маскировки генераторной матрицы G
S = random_binary_non_singular_matrix(4)
S_inv = np.linalg.inv(S).astype(int)  # Обратная матрица S

# Генерация случайной перестановочной матрицы размерности n x n
def generate_permutation_matrix(n):
    i = np.eye(n)  # Единичная матрица
    p = np.random.permutation(i)  # Перестановка строк
    return p.astype(int)

# Случайная перестановочная матрица и её обратная
P = generate_permutation_matrix(7)
P_inv = np.linalg.inv(P).astype(int)

# Генерация публичного ключа G_hat
G_hat = np.transpose(np.mod((S.dot(np.transpose(G))).dot(P), 2))

# Определяет позицию ошибки в закодированных данных
def detect_error(err_enc_bits):
    err_idx_vec = np.mod(H.dot(err_enc_bits), 2)  # Вектор синдрома ошибки
    err_idx_vec = err_idx_vec[::-1]  # Инвертируем порядок бит
    err_idx = int(''.join(str(bit) for bit in err_idx_vec), 2)  # Конвертация в число
    return err_idx - 1  # Индекс ошибки (начинается с 0)

# Кодирование 4-битного блока с использованием G_hat
def hamming7_4_encode(p_str):
    p = np.array([int(x) for x in p_str])  # Преобразование строки в массив бит
    prod = np.mod(G_hat.dot(p), 2)  # Умножение на публичный ключ
    return prod

# Декодирование 7-битного блока и извлечение исходных данных
def hamming7_4_decode(c):
    prod = np.mod(R.dot(c), 2)  # Умножение на матрицу восстановления R
    return prod

# Переворот бита по индексу n
def flip_bit(bits, n):
    bits[n] = (bits[n] + 1) % 2  # Инвертируем значение бита (0 -> 1, 1 -> 0)

# Добавление одиночной битовой ошибки в кодированный блок
def add_single_bit_error(enc_bits):
    error = [0] * 7  # Вектор ошибок (поначалу все 0)
    idx = random.randint(0, 6)  # Случайный индекс бита
    error[idx] = 1  # Добавляем ошибку в выбранный бит
    return np.mod(enc_bits + error, 2)  # Сложение по модулю 2

# Разделение строки на части длиной n бит
def split_binary_string(str, n):
    return [str[i:i + n] for i in range(0, len(str), n)]

# Преобразование битов в строку текста
def bits_to_str(bits):
    my_chunks = [bits[i:i + 8] for i in range(0, len(bits), 8)]  # Разбиваем на 8-битные блоки
    my_chars = [chr(int(chunk, 2)) for chunk in my_chunks]  # Конвертируем каждый блок в символ
    my_text = ''.join(my_chars)  # Соединяем символы в строку
    return my_text

if __name__ == '__main__':
    # Чтение исходного текста из файла
    with open("input.txt", "r", encoding="utf-8") as f:
        textt = f.read()
    with open("input.txt", "rb") as f:
        text = f.read()
    binary_str = ''.join(format(x, '08b') for x in text)  # Преобразование текста в двоичный вид

    # Разделение битов на блоки по 4 бита
    split_bits_list = split_binary_string(binary_str, 4)
    enc_msg = []

    # Кодирование каждого блока и добавление ошибки
    for split_bits in split_bits_list:
        enc_bits = hamming7_4_encode(split_bits)  # Кодируем блок
        err_enc_bits = add_single_bit_error(enc_bits)  # Добавляем ошибку
        str_enc = ''.join(str(x) for x in err_enc_bits)  # Преобразуем в строку
        enc_msg.append(str_enc)  # Добавляем в список закодированных данных

    # Запись закодированного сообщения в файл
    encoded = ''.join(enc_msg)
    with open("encrypt.txt", "w", encoding="utf-8") as f:
        f.write(encoded)

    dec_msg = []

    # Декодирование каждого блока
    for enc_bits in enc_msg:
        enc_bits = np.array([int(x) for x in enc_bits])  # Преобразуем строку в массив бит
        c_hat = np.mod(enc_bits.dot(P_inv), 2)  # Убираем перестановку (умножаем на P^-1)
        err_idx = detect_error(c_hat)  # Определяем позицию ошибки
        flip_bit(c_hat, err_idx)  # Исправляем ошибку
        m_hat = hamming7_4_decode(c_hat)  # Извлекаем данные (m_hat)
        m_out = np.mod(m_hat.dot(S_inv), 2)  # Применяем обратное преобразование (S^-1)
        str_dec = ''.join(str(x) for x in m_out)  # Преобразуем в строку
        dec_msg.append(str_dec)

    # Преобразование расшифрованных бит в текст
    dec_msg_str = ''.join(dec_msg)
    txt = bits_to_str(dec_msg_str)

    # Запись расшифрованного текста в файл
    with open("decoded.txt", "w", encoding="utf-8") as f:
        f.write(textt)
