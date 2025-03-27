ENG_LET_CAPITAL = 'ABCDEFGHIJKLMNOPQRSTUVWXYZ'
ENG_LET_LOWER = 'abcdefghijklmnopqrstuvwxyz'
RUS_LET_CAPITAL = 'АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ'
RUS_LET_LOWER = 'абвгдеёжзийклмнопрстуфхцчшщъыьэюя'


def encryption_ceaser(enc_text, key):
    temp_text = enc_text
    for index, character in enumerate(temp_text):
        temp_text = temp_text[:index] + encryption_ceaser_word(character, key) + temp_text[index + 1:]

    return temp_text


def decoding_ceaser(dec_text, key):
    temp_text = dec_text
    for index, character in enumerate(temp_text):
        temp_text = temp_text[:index] + decoding_ceaser_word(character, key) + temp_text[index + 1:]
    return temp_text


def encryption_ceaser_word(character, key):
    if character in ENG_LET_CAPITAL:
        position = ENG_LET_CAPITAL.find(character)
        key %= 26
        position = (position + key) % 26
        return ENG_LET_CAPITAL[position]
    if character in ENG_LET_LOWER:
        position = ENG_LET_LOWER.find(character)
        key %= 26
        position = (position + key) % 26
        return ENG_LET_LOWER[position]
    if character in RUS_LET_CAPITAL:
        position = RUS_LET_CAPITAL.find(character)
        key %= 33
        position = (position + key) % 33
        return RUS_LET_CAPITAL[position]
    if character in RUS_LET_LOWER:
        position = RUS_LET_LOWER.find(character)
        key %= 33
        position = (position + key) % 33
        return RUS_LET_LOWER[position]
    else:
        return character


def decoding_ceaser_word(character, key):
    if character in ENG_LET_CAPITAL:
        position = ENG_LET_CAPITAL.find(character)
        key %= 26
        position = (position - key + 26) % 26
        return  ENG_LET_CAPITAL[position]
    if character in ENG_LET_LOWER:
        position = ENG_LET_LOWER.find(character)
        key %= 26
        position = (position - key + 26) % 26
        return ENG_LET_LOWER[position]
    if character in RUS_LET_CAPITAL:
        position = RUS_LET_CAPITAL.find(character)
        key %= 33
        position = (position - key + 33) % 33
        return RUS_LET_CAPITAL[position]
    if character in RUS_LET_LOWER:
        position = RUS_LET_LOWER.find(character)
        key %= 33
        position = (position - key + 33) % 33
        return RUS_LET_LOWER[position]
    else:
        return character


def encryption_vigenere(enc_text, key):
    temp_text = enc_text

    current_key = find_keys(key)

    for index, character in enumerate(temp_text):
        cur_key = current_key[index % len(current_key)]
        temp_text = temp_text[:index] + encryption_ceaser_word(character, cur_key) + temp_text[index + 1:]

    return temp_text


def find_keys(key):
    current_key = []

    for key_symbol in key:
        if key_symbol in ENG_LET_CAPITAL:
            position = ENG_LET_CAPITAL.find(key_symbol)
            current_key.append(position)
        elif key_symbol in ENG_LET_LOWER:
            position = ENG_LET_LOWER.find(key_symbol)
            current_key.append(position)
        elif key_symbol in RUS_LET_CAPITAL:
            position = RUS_LET_CAPITAL.find(key_symbol)
            current_key.append(position)
        elif key_symbol in RUS_LET_LOWER:
            position = RUS_LET_LOWER.find(key_symbol)
            current_key.append(position)

    return current_key


def decoding_vigenere(enc_text, key):
    temp_text = enc_text

    current_key = find_keys(key)

    for index, character in enumerate(temp_text):
        cur_key = current_key[index % len(current_key)]
        temp_text = temp_text[:index] + decoding_ceaser_word(character, cur_key) + temp_text[index + 1:]

    return temp_text


if __name__ == "__main__":

    c_choice = int(input('Введите 1 для шифра Цезаря, 2 для шифра Виженера: '))

    input_text = open("input.txt", encoding="utf-8")
    enc_text = input_text.read()
    key = input('Введите ключ: ')
    value = int(input('Введите 1 для шифрования или 2 для дешифрования: '))

    file = open("output.txt", "w")
    if c_choice == 1:
        if value == 1:
            text = encryption_ceaser(enc_text, int(key))
            file.write(text)
        if value == 2:
            text = decoding_ceaser(enc_text, int(key))
            file.write(text)
    elif c_choice == 2:
        if value == 1:
            text = encryption_vigenere(enc_text, key)
            file.write(text)
        if value == 2:
            text = decoding_vigenere(enc_text, key)
            file.write(text)
    file.close()
