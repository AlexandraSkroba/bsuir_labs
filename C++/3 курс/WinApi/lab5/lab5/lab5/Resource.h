#pragma once

LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
WNDCLASS WindowClass(HBRUSH BGColor, HCURSOR Cursor, HINSTANCE hInst, LPCWSTR Name, WNDPROC wc);
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd);

void CheckWallpaperChange();
void CheckShortTime();

bool GetDesktopWallpaperPath(WCHAR* wallpaperPath, DWORD bufferSize);
bool GetShortTime(WCHAR* wallpaperPath, DWORD bufferSize);

int previousScreenWidth = 0;
int previousScreenHeight = 0;
LANGID previousSystemLanguage = 0;
HKL previousKeyboardLayout = nullptr;
HKEY hKey = nullptr;
WCHAR previousWallpaper[MAX_PATH];
WCHAR previousTime[12];
DWORD bufferSize;
DWORD buff;
HANDLE hRegChangeEvent = nullptr;
