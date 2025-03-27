#pragma once

#define OnOpenMenuClicked	1
#define OnSaveAsMenuClicked	2
#define OnButtonClicked		3
#define OnSaveMenuClicked	4

#define TextBufferSize		256
char Buffer[TextBufferSize];
char currentFileName[260];

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
WNDCLASS WindowClass(HBRUSH BGColor, HCURSOR Cursor, HINSTANCE hInst, LPCWSTR Name, WNDPROC wc);
void MainWndAddMenu(HWND hwnd);
void MainWndAddWidget(HWND hwnd);
void SetOpenFileParams(HWND hwnd);
void SaveData(LPCSTR path);
void LoadData(LPCSTR path);

HWND hEditConstrol;
char fileName[260];
OPENFILENAMEA ofn = { 0 };
bool isTextChanged = false;
int length = 0;
int loadFileLength;
