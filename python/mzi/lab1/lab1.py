import sys

# Блоки сдвигов при шифровании (S-блоки)
blocks = (
    (4, 10, 9, 2, 13, 8, 0, 14, 6, 11, 1, 12, 7, 15, 5, 3),
    (14, 11, 4, 12, 6, 13, 15, 10, 2, 3, 8, 1, 0, 7, 5, 9),
    (5, 8, 1, 13, 10, 3, 4, 2, 14, 15, 12, 7, 6, 0, 9, 11),
    (7, 13, 10, 1, 0, 8, 9, 15, 14, 4, 6, 12, 11, 2, 5, 3),
    (6, 12, 7, 1, 5, 15, 13, 8, 4, 10, 9, 14, 0, 3, 11, 2),
    (4, 11, 10, 0, 7, 2, 1, 13, 3, 6, 8, 5, 9, 12, 15, 14),
    (13, 11, 4, 1, 3, 15, 5, 9, 0, 10, 14, 7, 6, 8, 2, 12),
    (1, 15, 13, 0, 5, 7, 10, 4, 9, 2, 3, 14, 6, 11, 8, 12),
)
# 256-битное число
key = 18318279387912387912789378912379821879387978238793278872378329832982398023031

# для получения количества битов в числе
def bit_length(value):
    return len(bin(value)[2:])  # удаляем '0b' в начале

class Crypt(object):
    def __init__(self, key, sbox):
        assert bit_length(key) <= 256  # проверяем, что ключ не больше 256 бит
        self._key = None
        self._subkeys = None
        self.key = key  # установка ключа через setter
        self.sbox = sbox  # используемые S-блоки

    @property
    def key(self):
        return self._key

    # Устанавливаем ключ и разбиваем его на подключи
    @key.setter
    def key(self, key):
        assert bit_length(key) <= 256  # проверяем размер ключа
        self._key = key
        # Разбиваем ключ на восемь 32-битных блоков
        self._subkeys = [(key >> (32 * i)) & 0xFFFFFFFF for i in range(8)]

    # Вспомогательная функция для шифрования одного раунда
    def _f(self, part, key):
        assert bit_length(part) <= 32  # проверяем, что часть данных не больше 32 бит
        temp = part ^ key  # XOR с подключом
        output = 0
        # Применение S-блоков к каждому 4-битному блоку данных
        for i in range(8):
            output |= ((self.sbox[i][(temp >> (4 * i)) & 0b1111]) << (4 * i))
        # Циклический сдвиг результата на 11 бит
        return ((output >> 11) | (output << (32 - 11))) & 0xFFFFFFFF

    # один раунд дешифрования
    def _decrypt_round(self, left_part, right_part, round_key):
        return left_part, right_part ^ self._f(left_part, round_key)

    # (64-битное сообщение)
    def encrypt(self, msg):
        def _encrypt_round(left, right, round_key):
            return right, left ^ self._f(right, round_key)

        assert bit_length(msg) <= 64  # сообщение не больше 64 бит
        left_part = msg >> 32  # старшая половина сообщения
        right_part = msg & 0xFFFFFFFF  # младшая половина сообщения
        # 24 раунда с прямыми подключами
        for i in range(24):
            left_part, right_part = _encrypt_round(left_part, right_part, self._subkeys[i % 8])
        # 8 раундов с подключами в обратном порядке
        for i in range(8):
            left_part, right_part = _encrypt_round(left_part, right_part, self._subkeys[7 - i])
        return (left_part << 32) | right_part  # соединяем обе части в одно целое

    def decrypt(self, crypted_msg):
        def _decrypt_round(left_part, right_part, round_key):
            return right_part ^ self._f(left_part, round_key), left_part

        assert bit_length(crypted_msg) <= 64  # сообщение не больше 64 бит
        left_part = crypted_msg >> 32  # старшая половина зашифрованного сообщения
        right_part = crypted_msg & 0xFFFFFFFF  # младшая половина
        # 8 раундов с подключами в прямом порядке
        for i in range(8):
            left_part, right_part = _decrypt_round(left_part, right_part, self._subkeys[i])
        # 24 раунда с подключами в обратном порядке
        for i in range(24):
            left_part, right_part = _decrypt_round(left_part, right_part, self._subkeys[(7 - i) % 8])
        return (left_part << 32) | right_part  # соединяем обе части в одно целое


def main(argv=None):
    action = input("Зашифровать или дешифровать (s, d): ").strip().lower()
    if action not in ['s', 'd']:
        print("Неверный выбор. Введите 's' для шифрования или 'd' для дешифровки.")
        return

    if action == 's':
        cyphred = []
        gost = Crypt(key, blocks)  # создаем объект шифрования
        try:
            s = []
            # конвертируем данные в байты
            with open('input.txt', 'rb') as file:
                byte = file.read(1)
                while byte:
                    s.append(ord(byte))  # преобразуем байты в числа
                    byte = file.read(1)
            # Шифруем каждый байт
            for x in s:
                cyphred.append(gost.encrypt(x))
        except:
            print(f"Не удалось открыть файл input.txt")
            return

        try:
            with open('encrypted.txt', 'w') as file:
                print(*cyphred, file=file)
            print("Файл зашифрован")
        except:
            print(f"Не удалось открыть файл encrypted.txt")
            return

    if action == 'd':
        decyphred = []
        gost = Crypt(key, blocks)  # создаем объект шифрования
        try:
            # Читаем зашифрованные данные из файла
            with open('encrypted.txt') as file:
                s = file.read()
            # Дешифруем данные
            for x in s.split():
                decyphred.append(gost.decrypt(int(x)))
        except:
            print(f"Не удалось открыть файл encrypted.txt")
            return

        try:
            with open('text1.txt', 'wb') as file:
                file.write(bytes(decyphred))  # преобразуем числа обратно в байты
            print("Файл расшифрован")
        except:
            print(f"Не удалось открыть файл text1.txt")
            return


if __name__ == "__main__":
    main()
