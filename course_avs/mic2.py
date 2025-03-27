import os
import sys
import main
import wave
import timeit
import pyaudio
import numpy as np
import simpleaudio as sa
import matplotlib.pyplot as plt
from scipy.io import wavfile
from scipy.signal import spectrogram

# Создаем объект PyAudio
p = pyaudio.PyAudio()

# Создание пустого списка для хранения потоков записи звука
stream_list = []

# Установка параметров для аудио записи
FORMAT = pyaudio.paInt16  # Формат звука (16 бит, целочисленный)
CHANNELS = 1              # Количество каналов (моно)
RATE = 44100              # Частота дискретизации (в Гц)
CHUNK = 4                 # Размер блока данных (в сэмплах)
duration = 5  # seconds
filename_counter = 0
folder_name = "Rec"
number_of_mics = 2


def play_audio_wave(file_path):
    # Открытие аудиофайла
    wave_file = wave.open(file_path, 'rb')

    # Получение параметров аудио
    channels = wave_file.getnchannels()
    sample_width = wave_file.getsampwidth()
    frame_rate = wave_file.getframerate()

    # Чтение аудиоданных
    audio_data = wave_file.readframes(wave_file.getnframes())

    # Закрытие аудиофайла
    wave_file.close()

    # Проигрывание аудио
    wave_obj = sa.WaveObject(audio_data, num_channels=channels, bytes_per_sample=sample_width, sample_rate=frame_rate)
    play_obj = wave_obj.play()

    # Ожидание завершения проигрывания
    play_obj.wait_done()


def plot_spectrogram():
    # Построение спектрограммы для каждого файла в подпапке
    plt.figure(figsize=(10, 6))  # Создаем единственный график для обоих микрофонов

    for i in range(number_of_mics):
        mic_folder = os.path.join(folder_name, str(i))
        files = os.listdir(mic_folder)

        # Построение спектрограммы для каждого файла в подпапке
        for j, file in enumerate(files, start=1):
            # Формирование пути к файлу
            file_path = os.path.join(mic_folder, file)

            # Загрузка аудиофайла
            _, audio_array = wavfile.read(file_path)

            # Получение спектрограммы
            frequencies, times, Sxx_original = spectrogram(audio_array, fs=RATE, nperseg=1024)

            # Вычисление индекса текущего подграфика в матрице подграфиков
            subplot_index = (i * len(files)) + j
            plt.subplot(number_of_mics, len(files), subplot_index)

            # Строим спектрограмму
            plt.pcolormesh(times, frequencies, 10 * np.log10(Sxx_original), shading='auto', rasterized=True)

            # Устанавливаем подписи осей
            plt.ylabel('Частота [Гц]')
            plt.xlabel('Время [с]')

            # Устанавливаем заголовок графика с именем файла
            plt.title(f'Спектрограмма - {file_path}')

            # Добавляем цветовую шкалу с подписью
            plt.colorbar(label='Уровень мощности [дБ]')

            print(f"Проигрывание аудио - {file_path}")
            play_audio_wave(file_path)

    # Корректируем расположение подграфиков, чтобы избежать их перекрытия
    plt.tight_layout()

    # Отображаем график
    plt.show()


# Функция для создания и возвращения объекта потока записи звука
def makeStream(FORMAT, CHANNELS, RATE, INDEX, CHUNK):
    # Открываем аудио-поток с заданными параметрами
    stream = p.open(format=FORMAT,            # Формат аудио-сигнала (например, 16 бит, целочисленный)
                    channels=CHANNELS,        # Количество аудио-каналов (например, 1 для моно, 2 для стерео)
                    rate=RATE,                # Частота дискретизации (в Гц, например, 16000)
                    input=True,               # Указываем, что поток будет входным (для записи звука)
                    input_device_index=INDEX, # Индекс устройства ввода (микрофона)
                    frames_per_buffer=CHUNK)  # Размер блока данных (в сэмплах, например, 4)

    # Возвращаем созданный поток, который можно использовать для записи аудио
    return stream


# Функция записи звукового сигнала с нескольких микрофонов в течение определенного времени и сохранения записей в файлы формата WAV
def record_utterance():
    global filename_counter
    # Инициализация списков для хранения сэмплов каждого микрофона
    frames = [[] for _ in range(len(stream_list))]

    # Запуск записи с микрофонов
    start = timeit.default_timer()
    print("Идет запись...")

    # Цикл записи аудио-сэмплов
    for i in range(0, int(RATE / CHUNK * duration)):
        for j in range(len(stream_list)):
            # Чтение данных из каждого микрофона
            data = stream_list[j].read(CHUNK, exception_on_overflow=False)
            frames[j].append(data)

    # Остановка записи
    stop = timeit.default_timer()
    print('Конец записи: ', stop - start)

    # Формирование имени файла
    filename = str(filename_counter) + '.wav'

    # Сохранение записанных сэмплов в файлы для каждого микрофона
    for i in range(len(stream_list)):
        # Открытие файла для записи
        wf = wave.open(os.path.join(folder_name, str(i), filename), 'wb')
        wf.setnchannels(CHANNELS)
        wf.setsampwidth(p.get_sample_size(FORMAT))
        wf.setframerate(RATE)
        wf.writeframes(b''.join(frames[i]))  # Запись сэмплов в файл
        wf.close()

    # Увеличение счетчика файлов
    filename_counter += 1


# Функция для получения информации об аудиоустройствах ввода
def getDeviceInfo():
    # Получаем информацию о хост-API (хост-API с индексом 0 представляет собой систему по умолчанию)
    info = p.get_host_api_info_by_index(0)

    # Получаем количество доступных аудиоустройств
    numdevices = info.get('deviceCount')

    # Итерируем по каждому аудиоустройству
    for i in range(0, numdevices):
        # Проверяем, имеет ли текущее устройство входные каналы
        if (p.get_device_info_by_host_api_device_index(0, i).get('maxInputChannels')) > 0:
            # Получаем имя текущего устройства ввода
            n = p.get_device_info_by_host_api_device_index(0, i).get('name')

            # Выводим ID и имя устройства ввода (декодируем имя с использованием указанной кодировки)
            print("Устройство ввода с ID ", i, "-", n.encode("utf8").decode("cp1251", "ignore"))


# Сравнивает два аудиофайла на основе коэффициента корреляции.
def compare_audio_files(file_path1, file_path2):

    # Загрузка аудиосигналов из файлов
    _, audio_array1 = wavfile.read(file_path1)
    _, audio_array2 = wavfile.read(file_path2)

    correlation = np.corrcoef(audio_array1, audio_array2)[0, 1]
    correlation_percentage = (correlation + 1) / 2 * 100  # Преобразование коэффициента в проценты
    return "Коэффициент корреляции: ", correlation_percentage


def plot_spectrogram_n(file_path):
    # Загрузка аудиофайла
    _, audio_array = wavfile.read(file_path)

    # Получение спектрограммы
    frequencies, times, Sxx_original = spectrogram(audio_array, fs=RATE, nperseg=1024)

    # Добавляем маленькую константу к значениям мощности перед логарифмированием
    epsilon = 1e-10
    Sxx_log = 10 * np.log10(Sxx_original + epsilon)

    # Строим спектрограмму
    plt.pcolormesh(times, frequencies, Sxx_log, shading='auto', rasterized=True)

    # Устанавливаем подписи осей
    plt.ylabel('Частота [Гц]')
    plt.xlabel('Время [с]')

    # Устанавливаем заголовок графика с именем файла
    plt.title(f'Спектрограмма - {file_path}')

    # Добавляем цветовую шкалу с подписью
    plt.colorbar(label='Уровень мощности [дБ]')
    plt.show()

    return frequencies, times, Sxx_log

# Проверяем, запущен ли сценарий как основная программа
if __name__ == '__main__':
    # Вызываем функцию getDeviceInfo для вывода информации об устройствах ввода
    getDeviceInfo()
    index_of_mics = []

    # Цикл для запроса у пользователя индексов микрофонов и создания потоков записи для каждого микрофона
    for i in range(number_of_mics):
        # Формирование строки с вопросом пользователю и получение ответа в виде целого числа
        stri = 'Индекс для ' + str(i) + '-ого микрофона.'
        index_of_mics.append(int(input(stri)))

        # Создание потока записи для текущего микрофона и добавление его в список
        stream_list.append(makeStream(FORMAT, CHANNELS, RATE, index_of_mics[-1], CHUNK))

    # Проверка существования папки folder_name, если её нет - создается
    if not os.path.exists(folder_name):
        os.makedirs(folder_name)

    # Создание подпапок для каждого микрофона внутри folder_name
    for i in range(number_of_mics):
        if not os.path.exists(os.path.join(folder_name, str(i))):
            os.makedirs(os.path.join(folder_name, str(i)))

    # record_utterance()

    # plot_spectrogram()
  
    wav0_file_path = r'Rec\\0\\0.wav'
    wav1_file_path = r'Rec\\1\\0.wav'
    output_file_0 = "output_0.wav"
    output_file_1 = "output_1.wav"

    _, correlation_percentage = compare_audio_files(wav0_file_path, wav1_file_path)
    print("Коэффициент корреляции: ",correlation_percentage)

    if correlation_percentage < 50:
        print("Ошибка: Недостаточная корреляция звука!")
        sys.exit("Записи слишком разные для продолжения работы программы")

    main.noise_removal(wav0_file_path, output_file_0)
    main.noise_removal(wav1_file_path, output_file_1)

    print(compare_audio_files(output_file_0, output_file_1))

    spec_0 = plot_spectrogram_n(output_file_0)
    spec_1 = plot_spectrogram_n(output_file_1)

    concatenated_spec = np.concatenate((spec_0[2], spec_1[2]), axis=1)

    times_concatenated = np.concatenate((spec_0[1], spec_1[1]))
    frequencies_concatenated = spec_0[0]

    # Отображение объединенной спектрограммы
    plt.imshow(concatenated_spec, aspect='auto', origin='lower',
               extent=[times_concatenated[0], times_concatenated[-1], frequencies_concatenated[0],
                       frequencies_concatenated[-1]])
    plt.ylabel('Частота [Гц]')
    plt.xlabel('Время [с]')
    plt.title('Объединенная спектрограмма')
    plt.colorbar(label='Уровень мощности [дБ]')
    plt.show()
