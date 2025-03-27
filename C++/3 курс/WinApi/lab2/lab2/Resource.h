#pragma once

#define OnOpenMenuClicked			1
#define OnSaveAsMenuClicked			2
#define OnButtonClicked				3
#define OnSaveMenuClicked			4
#define OnBoldClicked				5
#define OnItalicClicked				6
#define OnTextColorClicked			7
#define OnBgColorClicked			8

#define TextBufferSize		256

char Buffer[TextBufferSize];
char currentFileName[260];
const DWORD ItalicFont = 0x00000002; // Битовый флаг для стиля шрифта курсив
const DWORD UnderlineFont = 0x00000004; // Битовый флаг для стиля шрифта подчеркивание

CHOOSECOLOR cc; // Структура для диалога выбора цвета
COLORREF customColors[16]; // Массив для пользовательских цветов
HBRUSH hBrush;
HDC dc;
static COLORREF selectedColor = RGB(0, 0, 0);
static COLORREF selectedBgColor = RGB(255, 255, 255);

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
WNDCLASS WindowClass(HBRUSH BGColor, HCURSOR Cursor, HINSTANCE hInst, LPCWSTR Name, WNDPROC wc);
HFONT CreateMyFont(int fontSize, bool isBold, bool isItalic, bool isUnderline);
void MainWndAddMenu(HWND hwnd);
void MainWndAddWidget(HWND hwnd);
void SetOpenFileParams(HWND hwnd);
void SaveData(LPCSTR path);
void LoadData(LPCSTR path);

HWND hEditConstrol;
HFONT hFont;
char fileName[260];
OPENFILENAMEA ofn = { 0 };
bool isTextChanged = false;
int length = 0;
int loadFileLength;
bool isBold = false;
bool isItalic = false;
