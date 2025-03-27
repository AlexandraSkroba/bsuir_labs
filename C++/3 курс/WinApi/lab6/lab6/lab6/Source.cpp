#include <Windows.h>
#include <string>
#include "Resource.h"

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd) {
    // Создание мьютекса
    mutex = CreateMutex(NULL, FALSE, NULL);
    if (mutex == NULL) {
        MessageBox(NULL, L"Failed to create mutex", L"Error", MB_OK | MB_ICONERROR);
        return 1;
    }

    // Создание семафора
    semaphore = CreateSemaphore(NULL, 1, 1, NULL);
    if (semaphore == NULL) {
        MessageBox(NULL, L"Failed to create semaphore", L"Error", MB_OK | MB_ICONERROR);
        CloseHandle(mutex);
        return 1;
    }

    WNDCLASS MainClass = WindowClass((HBRUSH)COLOR_WINDOW, LoadCursor(NULL, IDC_ARROW), hInstance, L"MainWndClass", WndProc);

    if (!RegisterClassW(&MainClass)) {
        return -1;
    }

    MSG MainMsg = {};

    CreateWindow(L"MainWndClass", L"Streams", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 500, 250, 300, 200, NULL, NULL, NULL, NULL);

    while (GetMessage(&MainMsg, NULL, NULL, NULL)) {
        TranslateMessage(&MainMsg);
        DispatchMessage(&MainMsg);
    }

    // Закрытие мьютекса и семафора
    CloseHandle(mutex);
    CloseHandle(semaphore);

    return 0;
}

WNDCLASS WindowClass(HBRUSH BGColor, HCURSOR Cursor, HINSTANCE hInst, LPCWSTR Name, WNDPROC wc) {
    WNDCLASS nwc = {};

    nwc.hbrBackground = BGColor;
    nwc.hCursor = Cursor;
    nwc.hInstance = hInst;
    nwc.lpszClassName = Name;
    nwc.lpfnWndProc = wc;

    return nwc;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
    case WM_CREATE:
        MainWndAddWidget(hwnd);
        break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    case WM_COMMAND:
        switch (wParam) {
        case OnIncrementClicked:
            // Создание потока для инкремента
            CreateThread(NULL, 0, IncrementThread, hwnd, 0, NULL);
            break;

        case OnDecrementClicked:
            // Создание потока для декремента
            CreateThread(NULL, 0, DecrementThread, hwnd, 0, NULL);
            break;
        }
        break;

    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }

    return 0;
}

void MainWndAddWidget(HWND hwnd) {
    hEditControl = CreateWindow(L"edit", L"0", WS_VISIBLE | WS_CHILD | ES_MULTILINE | ES_READONLY, 30, 30, 100, 30, hwnd, NULL, NULL, NULL);
    CreateWindowA("button", "Increment", WS_VISIBLE | WS_CHILD, 30, 80, 100, 30, hwnd, (HMENU)OnIncrementClicked, NULL, NULL);
    CreateWindowA("button", "Decrement", WS_VISIBLE | WS_CHILD, 140, 80, 100, 30, hwnd, (HMENU)OnDecrementClicked, NULL, NULL);
}

DWORD WINAPI IncrementThread(LPVOID lpParam) {
    // Ожидание мьютекса и семафора
    WaitForSingleObject(mutex, INFINITE);
    WaitForSingleObject(semaphore, INFINITE);

    // Инкремент общей переменной
    sharedValue++;
    std::wstring value = std::to_wstring(sharedValue);

    // Обновление текстового поля
    SetWindowText(hEditControl, value.c_str());

    // Освобождение семафора и мьютекса
    ReleaseSemaphore(semaphore, 1, NULL);
    ReleaseMutex(mutex);

    return 0;
}

DWORD WINAPI DecrementThread(LPVOID lpParam) {
    // Ожидание мьютекса и семафора
    WaitForSingleObject(mutex, INFINITE);
    WaitForSingleObject(semaphore, INFINITE);

    // Декремент общей переменной
    sharedValue--;
    std::wstring value = std::to_wstring(sharedValue);

    // Обновление текстового поля
    SetWindowText(hEditControl, value.c_str());

    // Освобождение семафора и мьютекса
    ReleaseSemaphore(semaphore, 1, NULL);
    ReleaseMutex(mutex);

    return 0;
}
