#include <Windows.h>
#include <wtypes.h>
#include "Resource.h"   

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd) {
    WNDCLASS MainClass = WindowClass((HBRUSH)COLOR_WINDOW, LoadCursor(NULL, IDC_ARROW), hInstance, L"MainWndClass", WndProc);

    if (!RegisterClassW(&MainClass)) { return -1; }

    MSG MainMsg = { };

    HWND hwnd = CreateWindow(L"MainWndClass", L"Programm", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 500, 200, 300, 300, NULL, NULL, NULL, NULL);

    if (!hwnd) {
        return 1;
    }

    // �������� ��������� ���������� ������
    previousScreenWidth = GetSystemMetrics(SM_CXSCREEN);
    previousScreenHeight = GetSystemMetrics(SM_CYSCREEN);

    // �������� ��������� ���� �������
    previousSystemLanguage = GetUserDefaultUILanguage();

    // �������� ��������� ��������� ����������
    previousKeyboardLayout = GetKeyboardLayout(0);

    GUID guid = GUID_ACDC_POWER_SOURCE;
    HPOWERNOTIFY hPowerNotify = RegisterPowerSettingNotification(hwnd, &guid, 0);

    if (hPowerNotify == NULL) {
        return 1;
    }

    while (GetMessage(&MainMsg, NULL, NULL, NULL)) {
        TranslateMessage(&MainMsg);
        DispatchMessage(&MainMsg);

        // �������� ��������� ���������� ������
        int currentScreenWidth = GetSystemMetrics(SM_CXSCREEN);
        int currentScreenHeight = GetSystemMetrics(SM_CYSCREEN);

        if (currentScreenWidth != previousScreenWidth || currentScreenHeight != previousScreenHeight) {
            MessageBox(NULL, L"���������� ������ ����������!", L"��������� ����������", MB_OK | MB_ICONINFORMATION);
            previousScreenWidth = currentScreenWidth;
            previousScreenHeight = currentScreenHeight;
        }

        // �������� ��������� ����� �������
        LANGID currentSystemLanguage = GetUserDefaultUILanguage();

        if (currentSystemLanguage != previousSystemLanguage) {
            MessageBox(NULL, L"���� ������� ���������!", L"��������� ����� �������", MB_OK | MB_ICONINFORMATION);
            previousSystemLanguage = currentSystemLanguage;
        }

        // �������� ��������� ��������� ����������
        HKL currentKeyboardLayout = GetKeyboardLayout(0);

        if (currentKeyboardLayout != previousKeyboardLayout) {
            MessageBox(NULL, L"��������� ���������� ����������!", L"��������� ��������� ����������", MB_OK | MB_ICONINFORMATION);
            previousKeyboardLayout = currentKeyboardLayout;
        }

        // �������� ��������� ���� �������� �����
        CheckWallpaperChange();

        // �������� ��������� �������� �������
        CheckShortTime();
    }

    UnregisterPowerSettingNotification(hPowerNotify);

    return 0;
}

WNDCLASS WindowClass(HBRUSH BGColor, HCURSOR Cursor, HINSTANCE hInst, LPCWSTR Name, WNDPROC wc) {
    WNDCLASS nwc = { };

    nwc.hbrBackground = BGColor;
    nwc.hCursor = Cursor;
    nwc.hInstance = hInst;
    nwc.lpszClassName = Name;
    nwc.lpfnWndProc = wc;

    return nwc;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    if (uMsg == WM_POWERBROADCAST) {
        if (wParam == PBT_POWERSETTINGCHANGE) {
            POWERBROADCAST_SETTING* powerSetting = (POWERBROADCAST_SETTING*)lParam;

            if (powerSetting->PowerSetting == GUID_ACDC_POWER_SOURCE) {
                if (powerSetting->Data[0] == 0) {
                    MessageBox(NULL, L"��������� ��������� � �������!", L"��������� ������", MB_ICONINFORMATION);
                }
                else {
                    MessageBox(NULL, L"��������� �������� �� ��������!", L"��������� ������", MB_ICONINFORMATION);
                }
            }
        }
    }
    
    switch (uMsg) {
    case WM_CREATE:
        bufferSize = sizeof(previousWallpaper);
        buff = sizeof(previousTime);

        GetDesktopWallpaperPath(previousWallpaper, bufferSize);
        GetShortTime(previousTime, buff);
        break;
    case WM_DESTROY:
        if (hRegChangeEvent != nullptr) {
            CloseHandle(hRegChangeEvent);
        }
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
}

void CheckWallpaperChange() {
    if (RegOpenKeyEx(HKEY_CURRENT_USER, L"Control Panel\\Desktop", 0, KEY_READ, &hKey) == ERROR_SUCCESS) {
        WCHAR currentWallpaper[MAX_PATH];
        bufferSize = sizeof(currentWallpaper);

        if (RegQueryValueEx(hKey, L"Wallpaper", nullptr, nullptr, (LPBYTE)currentWallpaper, &bufferSize) == ERROR_SUCCESS) {
            if (lstrcmpW(currentWallpaper, previousWallpaper) != 0) {
                MessageBox(NULL, L"��� �������� ����� ���������!", L"��������� ���� �������� �����", MB_OK | MB_ICONINFORMATION);
                lstrcpynW(previousWallpaper, currentWallpaper, MAX_PATH);
            }
        }
        RegCloseKey(hKey);
    }
}

bool GetDesktopWallpaperPath(WCHAR* wallpaperPath, DWORD bufferSize) {
    HKEY hKey = nullptr;

    // ��������� ���� �������, ���������� ���������� � ���� �������� �����
    if (RegOpenKeyEx(HKEY_CURRENT_USER, L"Control Panel\\Desktop", 0, KEY_READ, &hKey) == ERROR_SUCCESS) {
        DWORD valueType;
        // ��������� �������� "Wallpaper" �� �������
        if (RegQueryValueEx(hKey, L"Wallpaper", nullptr, &valueType, (LPBYTE)wallpaperPath, &bufferSize) == ERROR_SUCCESS) {
            // ���������, ��� ��� �������� - REG_SZ (������)
            if (valueType == REG_SZ) {
                RegCloseKey(hKey);
                return true;
            }
        }
        RegCloseKey(hKey);
    }

    return false;
}

void CheckShortTime() {
    if (RegOpenKeyEx(HKEY_CURRENT_USER, L"Control Panel\\International", 0, KEY_READ, &hKey) == ERROR_SUCCESS) {
        WCHAR currentShortTime[12];
        bufferSize = sizeof(currentShortTime);

        if (RegQueryValueEx(hKey, L"sShortDate", nullptr, nullptr, (LPBYTE)currentShortTime, &bufferSize) == ERROR_SUCCESS) {
            if (lstrcmpW(currentShortTime, previousTime) != 0) {
                WCHAR message[256];
                wcscpy_s(message, L"������� ������ ������� ���������!\n����� ��������: ");
                wcscat_s(message, currentShortTime);

                MessageBox(NULL, message, L"��������� �������", MB_OK | MB_ICONINFORMATION);

                // ��������� previousTime
                lstrcpynW(previousTime, currentShortTime, MAX_PATH);
            }
        }
        RegCloseKey(hKey);
    }
}

bool GetShortTime(WCHAR* previousShortTime, DWORD bufferSize) {
    HKEY hKey = nullptr;

    if (RegOpenKeyEx(HKEY_CURRENT_USER, L"Control Panel\\International", 0, KEY_READ, &hKey) == ERROR_SUCCESS) {
        DWORD valueType;
        if (RegQueryValueEx(hKey, L"sShortDate", nullptr, &valueType, (LPBYTE)previousShortTime, &bufferSize) == ERROR_SUCCESS) {
            if (valueType == REG_SZ) {
                RegCloseKey(hKey);
                return true;
            }
        }
        RegCloseKey(hKey);
    }

    return false;
}
