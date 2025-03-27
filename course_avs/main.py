import numpy as np
import sounddevice as sd
import matplotlib.pyplot as plt
from scipy.io import wavfile
from scipy.signal import spectrogram, butter, lfilter

# Параметры записи
duration = 5  # Длительность записи в секундах
sample_rate = 44100  # Частота дискретизации

def noise_removal(audio_data, output_file):
    # Загрузка аудио файла
    audio_array, _ = wavfile.read(audio_data)
    audio_array = audio_array.astype(np.float32) / np.iinfo(np.int16).max  # Нормализация аудио

    # Воспроизведение оригинальной дорожки
    print("Воспроизведение оригинальной дорожки...")
    sd.play(audio_array, sample_rate)
    sd.wait()

    # Вычисление и отображение оригинальной спектрограммы
    frequencies, times, Sxx_original = spectrogram(audio_array, fs=sample_rate, nperseg=1024)

    plt.subplot(4, 1, 1)
    plt.pcolormesh(times, frequencies, 10 * np.log10(Sxx_original), shading='auto')
    plt.ylabel('Частота [Гц]')
    plt.xlabel('Время [с]')
    plt.title('Оригинальная спектрограмма записанного звука')
    plt.colorbar()

    # Расчет ДПФ
    fourier_transform = np.fft.fft(audio_array)
    frequencies_fft = np.fft.fftfreq(len(fourier_transform), d=1/sample_rate)

    # Определение высокочастотных компонент (шумов)
    high_frequency_cutoff = 1000
    noise_indices = np.abs(frequencies_fft) > high_frequency_cutoff

    # Удаление шумов в частотной области
    fourier_transform[noise_indices] = 0

    # Обратное преобразование Фурье
    filtered_audio_fft = np.fft.ifft(fourier_transform).real

    # Вычисление и отображение спектрограммы после удаления шумов в частотной области
    frequencies, times, Sxx_filtered_fft = spectrogram(filtered_audio_fft, fs=sample_rate, nperseg=1024)

    plt.subplot(4, 1, 2)
    plt.pcolormesh(times, frequencies, 10 * np.log10(Sxx_filtered_fft), shading='auto')
    plt.ylabel('Частота [Гц]')
    plt.xlabel('Время [с]')
    plt.title('Спектрограмма после удаления шумов (частотная область)')
    plt.colorbar(label='Уровень мощности [дБ]')

    # Низкочастотный фильтр для сравнения
    def butter_lowpass_filter(data, cutoff, fs, order=4):
        nyquist = 0.5 * fs
        normal_cutoff = cutoff / nyquist
        b, a = butter(order, normal_cutoff, btype='low', analog=False)
        y = lfilter(b, a, data)
        return y

    cutoff_frequency = 1000
    filtered_audio_lowpass = butter_lowpass_filter(audio_array, cutoff_frequency, sample_rate)

    # Воспроизведение дорожки после низкочастотной фильтрации
    print("Воспроизведение дорожки после низкочастотной фильтрации...")
    sd.play(filtered_audio_lowpass, sample_rate)
    sd.wait()

    # Вычисление и отображение спектрограммы после низкочастотной фильтрации
    frequencies, times, Sxx_filtered_lowpass = spectrogram(filtered_audio_lowpass, fs=sample_rate, nperseg=1024)

    plt.subplot(4, 1, 3)
    plt.pcolormesh(times, frequencies, 10 * np.log10(Sxx_filtered_lowpass), shading='auto', rasterized=True)
    plt.ylabel('Частота [Гц]')
    plt.xlabel('Время [с]')
    plt.title('Спектрограмма после низкочастотной фильтрации')
    plt.colorbar()

    wavfile.write(output_file, sample_rate, (filtered_audio_lowpass * 32767).astype(np.int16))

    plt.tight_layout()
    plt.show()
