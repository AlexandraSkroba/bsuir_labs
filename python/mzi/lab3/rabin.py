import random
import os
from sympy import isprime
import argparse


# Функция для генерации ключевой пары (n, p, q)
def create_keypair(bit_size):
    # Проверяем, что размер ключа не меньше 512 и кратен 8
    if bit_size < 512 or bit_size % 8 != 0:
        raise ValueError("Размер ключа должен быть не меньше 512 бит и кратен 8.")

    # Генерируем два больших простых числа
    prime1 = generate_large_prime(bit_size)
    prime2 = generate_large_prime(bit_size)
    modulus = prime1 * prime2  # Вычисляем модуль n
    return (modulus, prime1, prime2)  # Возвращаем модуль и два простых числа


# Генерация большого случайного простого числа с необходимым количеством бит
def generate_large_prime(bits):
    while True:
        prime_candidate = random.getrandbits(bits)  # Генерируем случайное число
        prime_candidate |= (1 << (bits - 1)) | 1  # Убедимся, что число нечётное и имеет нужное количество бит
        if isprime(prime_candidate) and prime_candidate % 4 == 3:  # Проверка простоты и условия p % 4 == 3
            return prime_candidate  # Возвращаем простое число

# Условия гарантируют, что алгоритм нахождения квадратных корней будет работать правильно.
# В частности, для таких p и q существует хорошо определённый способ нахождения квадратных
# корней по модулю этих простых чисел.

# Функция шифрования сообщения
def encrypt_rabin(plaintext_num, modulus):
    return (plaintext_num * plaintext_num) % modulus  # Возвращаем квадрат сообщения по модулю


# Алгоритм расширенного Евклида для нахождения коэффициентов
def extended_euclid(a, b):
    if a == 0:
        return b, 0, 1  # Базовый случай
    nod, x1, y1 = extended_euclid(b % a, a)  # Рекурсивный вызов
    x = y1 - (b // a) * x1  # Вычисляем коэффициенты
    y = x1
    return nod, x, y  # Возвращаем НОД и коэффициенты


# Нахождение коэффициентов для p и q в уравнении yp * p + yq * q = 1
def calculate_coefficients(prime1, prime2):
    nod, coeff_p, coeff_q = extended_euclid(prime1, prime2)  # Нахождение НОД и коэффициентов
    if nod != 1:
        raise ValueError("Числа p и q должны быть взаимно простыми")  # Проверка взаимной простоты
    return coeff_p, coeff_q


# Функция для дешифрования сообщения
def decrypt_rabin(ciphertext, prime1, prime2):
    modulus = prime1 * prime2  # Вычисляем модуль n
    exponent_p = (prime1 + 1) // 4  # Вычисляем степень для p
    exponent_q = (prime2 + 1) // 4  # Вычисляем степень для q

    # Согласно свойствам квадратных остатков, если y^2===x mod p, то
    # y можно найти с помощью экспоненты.

    # Вычисляем квадратные корни по модулю p и q
    mp = pow(ciphertext, exponent_p, prime1)
    mq = pow(ciphertext, exponent_q, prime2)

    coeff_p, coeff_q = calculate_coefficients(prime1, prime2)  # Находим коэффициенты

    # Находим 4 возможных решения
    solution1 = (coeff_p * prime1 * mq + coeff_q * prime2 * mp) % modulus
    solution2 = modulus - solution1
    solution3 = (coeff_p * prime1 * mq - coeff_q * prime2 * mp) % modulus
    solution4 = modulus - solution3

    # Возвращаем одно из решений, которое в диапазоне [0, 255] (для символьного шифрования)
    if 0 <= solution1 <= 255:
        return solution1
    if 0 <= solution2 <= 255:
        return solution2
    if 0 <= solution3 <= 255:
        return solution3
    if 0 <= solution4 <= 255:
        return solution4


# Преобразование текста в список чисел
def text_to_ascii_codes(text):
    return [ord(char) for char in text]  # Преобразуем каждый символ текста в его ASCII-код


# Преобразование списка чисел обратно в текст
def ascii_codes_to_text(numbers):
    return ''.join(chr(num) for num in numbers)  # Преобразуем каждый ASCII-код обратно в символ


# Функция для сохранения ключей в файл
def save_keys(filename, modulus, prime1, prime2):
    with open(filename, 'w+') as file:
        file.write(f"{modulus}\n{prime1}\n{prime2}\n")  # Сохраняем модуль и два простых числа


# Функция для загрузки ключей из файла
def load_keys(filename):
    if not os.path.exists(filename):
        raise FileNotFoundError(f"Файл {filename} не найден.")  # Проверяем наличие файла

    with open(filename, 'r+') as file:
        try:
            # Читаем ключи из файла
            modulus = int(file.readline().strip())
            prime1 = int(file.readline().strip())
            prime2 = int(file.readline().strip())
        except ValueError:
            raise ValueError(f"Невалидный формат файла ключей: {filename}")  # Проверка формата файла

    return modulus, prime1, prime2  # Возвращаем модуль и простые числа


# Основное меню программы
def menu_interface():
    parser = argparse.ArgumentParser(description="Шифрование/Дешифрование с использованием схемы Рабина.")

    parser.add_argument("-m", "--mode", choices=["encrypt", "decrypt"], required=True,
                        help="Выберите режим: шифрование или дешифрование")
    parser.add_argument("-i", "--input", required=True, help="Укажите файл для шифрования/дешифрования")
    parser.add_argument("-o", "--output", required=True, help="Укажите файл для сохранения результата")
    parser.add_argument("-k", "--keyfile", required=True, help="Файл для хранения или загрузки ключей")
    parser.add_argument("--gen-keys", action="store_true", help="Сгенерировать новые ключи")
    parser.add_argument("--key-size", type=int, help="Размер ключа в битах (по умолчанию 512)", default=512)

    args = parser.parse_args()

    if args.gen_keys:
        try:
            # Генерация ключей с проверкой размера
            modulus, prime1, prime2 = create_keypair(args.key_size)
            save_keys(args.keyfile, modulus, prime1, prime2)  # Сохраняем сгенерированные ключи
            print(f"Ключи сгенерированы и сохранены в {args.keyfile}. Размер ключа: {args.key_size} бит.")
        except ValueError as e:
            print(f"Ошибка генерации ключей: {str(e)}")
            return

    if args.mode == "encrypt":
        # Шифрование
        try:
            modulus, _, _ = load_keys(args.keyfile)  # Загружаем ключи

            with open(args.input, 'r', encoding='utf-8') as file:
                plaintext = file.read()  # Читаем текст для шифрования

            # Преобразуем текст в ASCII и шифруем
            ascii_codes = text_to_ascii_codes(plaintext)
            encrypted_codes = [encrypt_rabin(num, modulus) for num in ascii_codes]

            # Сохраняем зашифрованные данные в файл
            with open(args.output, 'w+') as file:
                file.write(' '.join(map(str, encrypted_codes)))

            print(f"Текст зашифрован и сохранен в {args.output}")

        except Exception as e:
            print(f"Ошибка шифрования: {str(e)}")

    elif args.mode == "decrypt":
        # Дешифрование
        try:
            modulus, prime1, prime2 = load_keys(args.keyfile)  # Загружаем ключи

            with open(args.input, 'r+') as file:
                encrypted_codes = list(map(int, file.read().split()))  # Читаем зашифрованные данные

            decrypted_numbers = []
            for encrypted in encrypted_codes:
                decrypted_number = decrypt_rabin(encrypted, prime1, prime2)  # Дешифруем каждое число
                decrypted_numbers.append(decrypted_number)

            decrypted_text = ascii_codes_to_text(decrypted_numbers)  # Преобразуем числа обратно в текст

            # Сохраняем расшифрованный текст в файл
            with open(args.output, 'w+') as file:
                file.write(decrypted_text)

            print(f"Текст расшифрован и сохранен в {args.output}")

        except Exception as e:
            print(f"Ошибка дешифрования: {str(e)}")


if __name__ == "__main__":
    menu_interface()  # Запуск основного интерфейса программы
