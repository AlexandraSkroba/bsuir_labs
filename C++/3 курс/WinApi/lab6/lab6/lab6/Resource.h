#pragma once

HWND hEditControl; 
HANDLE mutex;      
HANDLE semaphore;  

#define OnIncrementClicked 1
#define OnDecrementClicked 2

int sharedValue = 0; 

WNDCLASS WindowClass(HBRUSH BGColor, HCURSOR Cursor, HINSTANCE hInst, LPCWSTR Name, WNDPROC wc);
LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
void MainWndAddWidget(HWND hwnd);
DWORD WINAPI IncrementThread(LPVOID lpParam);
DWORD WINAPI DecrementThread(LPVOID lpParam);
