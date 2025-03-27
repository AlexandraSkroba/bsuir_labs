#include <Windows.h>
#include <string.h>
#include <shlwapi.h>
#pragma comment(lib, "shlwapi.lib")
#include "Resource.h"
#include <commdlg.h>

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd) {
	WNDCLASS MainClass = WindowClass((HBRUSH)COLOR_WINDOW, LoadCursor(NULL, IDC_ARROW), hInstance, L"MainWndClass", WndProc);

	if (!RegisterClassW(&MainClass)) { return -1; }

	MSG MainMsg = { };

	CreateWindow(L"MainWndClass", L"TextEditor", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 200, 100, 565, 360, NULL, NULL, NULL, NULL);

	while (GetMessage(&MainMsg, NULL, NULL, NULL)) {
		TranslateMessage(&MainMsg);
		DispatchMessage(&MainMsg);
	}
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
	switch (uMsg) {
	case WM_COMMAND:
		switch (wParam)
		{
		case OnOpenMenuClicked:
			if (GetOpenFileNameA(&ofn))
			{
				LoadData(fileName);
				lstrcpyA(currentFileName, fileName); // Сохраняем имя файла в переменной currentFileName
				SetWindowTextA(hwnd, currentFileName);
				loadFileLength = GetWindowTextLength(hEditConstrol);
				isTextChanged = true;
			}
			break;
		case OnSaveAsMenuClicked:
			while (true)
			{
				if (GetSaveFileNameA(&ofn)) {
					if (PathFileExistsA(fileName)) {
						int result = MessageBoxW(hwnd, L"Файл с таким именем уже существует. Хотите перезаписать?", L"Подтвердить сохранение", MB_YESNO | MB_ICONQUESTION);
						if (result == IDYES) {
							SaveData(fileName);
							MessageBoxW(hwnd, L"Файл сохранен!", L"Сохранение", MB_OK);
							isTextChanged = false;
							break;
						}
					}
					else {
						SaveData(fileName);
						isTextChanged = false;
						break;
					}
				}
				else {
					break;
				}
			}
			break;
		case OnButtonClicked:
			SetWindowTextW(hEditConstrol, L"");
			selectedColor = RGB(0, 0, 0);
			selectedBgColor = RGB(255, 255, 255);
			isBold = false;
			isItalic = false;
			isTextChanged = true;
			break;
		case OnSaveMenuClicked:
			if (PathFileExistsA(fileName)) {
				SaveData(fileName);
				MessageBoxW(hwnd, L"Файл сохранен!", L"Сохранение", MB_OK);
				break;
			}
			else {
				if (GetSaveFileNameA(&ofn)) {
					SaveData(fileName);
					MessageBoxW(hwnd, L"Файл сохранен!", L"Save", MB_OK);
				}
			}
			break;
		case OnBoldClicked:
			isBold = !isBold;

			hFont = CreateMyFont(16, isBold, isItalic, false);
			SendMessage(hEditConstrol, WM_SETFONT, (WPARAM)hFont, TRUE);
			break;
		case OnItalicClicked:
			isItalic = !isItalic;

			hFont = CreateMyFont(16, isBold, isItalic, false);
			SendMessage(hEditConstrol, WM_SETFONT, (WPARAM)hFont, TRUE);
			break;
		case OnTextColorClicked:
			ZeroMemory(&cc, sizeof(cc));
			cc.lStructSize = sizeof(cc);
			cc.hwndOwner = hwnd;
			cc.lpCustColors = customColors;

			if (ChooseColor(&cc))
			{
				selectedColor = cc.rgbResult;
				InvalidateRect(hEditConstrol, NULL, TRUE);
			}
			break;
		case OnBgColorClicked:
			ZeroMemory(&cc, sizeof(cc));
			cc.lStructSize = sizeof(cc);
			cc.hwndOwner = hwnd;
			cc.lpCustColors = customColors;

			if (ChooseColor(&cc))
			{
				selectedBgColor = cc.rgbResult;
				InvalidateRect(hEditConstrol, NULL, TRUE);
			}
			break;
		break;
		default:
			break;
		}
		break;
	case WM_CTLCOLOREDIT:
		dc = (HDC)wParam;
		SetTextColor(dc, selectedColor);
		
		hBrush = CreateSolidBrush(selectedBgColor);
		SetBkColor(dc, selectedBgColor); // Установка цвета фона

		return (LRESULT)hBrush;

		break;
	case WM_CREATE:
		MainWndAddMenu(hwnd);
		MainWndAddWidget(hwnd);
		SetOpenFileParams(hwnd);

		break;

	case WM_DESTROY:

		length = GetWindowTextLength(hEditConstrol);

		if (length == loadFileLength) {
			PostQuitMessage(0);
			break;
		}

		if (isTextChanged || (isTextChanged == false && length > 1))
		{
			int result = MessageBox(hwnd, L"Хотите сохранить изменения?", L"Подтверждение", MB_YESNO);

			if (result == IDYES)
			{
				if (PathFileExistsA(currentFileName))
				{
					SaveData(currentFileName);
				}
				else
				{
					if (GetSaveFileNameA(&ofn))
					{
						SaveData(fileName);
					}
				}
			}
		}

		PostQuitMessage(0);
		break;

	default: return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
}

void MainWndAddMenu(HWND hwnd) {
	HMENU RootMenu = CreateMenu();

	AppendMenu(RootMenu, MF_STRING, OnOpenMenuClicked, L"Открыть");
	AppendMenu(RootMenu, MF_STRING, OnSaveMenuClicked, L"Сохранить");
	AppendMenu(RootMenu, MF_STRING, OnSaveAsMenuClicked, L"Сохранить как...");

	AppendMenu(RootMenu, MF_STRING, OnBoldClicked, L"Bold");
	AppendMenu(RootMenu, MF_STRING, OnItalicClicked, L"Italic");
	AppendMenu(RootMenu, MF_STRING, OnTextColorClicked, L"Text color");
	AppendMenu(RootMenu, MF_STRING, OnBgColorClicked, L"Bg color");

	SetMenu(hwnd, RootMenu);
}

void MainWndAddWidget(HWND hwnd) {
	hEditConstrol = CreateWindow(L"edit", L" ", WS_VISIBLE | WS_CHILD | ES_MULTILINE | WS_VSCROLL, 30, 30, 490, 200, hwnd, NULL, NULL, NULL);
	CreateWindowA("button", "Clear", WS_VISIBLE | WS_CHILD, 30, 240, 475, 30, hwnd, (HMENU)OnButtonClicked, NULL, NULL);

	hFont = CreateMyFont(16, isBold, isItalic, false);
	SendMessage(hEditConstrol, WM_SETFONT, (WPARAM)hFont, TRUE);
}

void SaveData(LPCSTR path) {
	HANDLE FileToSave = CreateFileA(
		path,
		GENERIC_WRITE,
		0,
		NULL,
		CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		NULL);

	int saveLenth = GetWindowTextLength(hEditConstrol) + 1;
	char* data = new char[saveLenth];

	saveLenth = GetWindowTextA(hEditConstrol, data, saveLenth);

	DWORD bytesIterated;
	WriteFile(FileToSave, data, saveLenth, &bytesIterated, NULL);

	CloseHandle(FileToSave);
	delete[] data;
}

void LoadData(LPCSTR path) {
	HANDLE FileToLoad = CreateFileA(
		path,
		GENERIC_READ,
		0,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL);

	DWORD saveSize = GetFileSize(FileToLoad, NULL) + 1;
	char* data = new char[saveSize];

	DWORD bytesIterated;
	ReadFile(FileToLoad, data, saveSize, &bytesIterated, NULL);
	data[bytesIterated] = '\0';

	SetWindowTextA(hEditConstrol, data);

	CloseHandle(FileToLoad);
	delete[] data;
}

void SetOpenFileParams(HWND hwnd) {
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = hwnd;
	ofn.lpstrFile = fileName;
	ofn.nMaxFile = sizeof(fileName);
	ofn.lpstrFilter = "Текстовые файлы *.txt\0*.txt\0";
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = "D:\\С++\\WinApi\\lab1";
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
}

HFONT CreateMyFont(int fontSize, bool isBold, bool isItalic, bool isUnderline) {
	int fontWeight = isBold ? FW_BOLD : FW_NORMAL;
	DWORD fontStyle = isItalic ? (DWORD)ItalicFont : 0;
	fontStyle |= isUnderline ? (DWORD)UnderlineFont : 0;

	HFONT hFont = CreateFont(
		fontSize,            // Размер шрифта
		0,                   // Ширина символов (0 для автоматического)
		0,                   // Угол наклона (0 для нормального)
		0,                   // Угол наклона базовой линии (0 для нормального)
		fontWeight,          // Толщина шрифта
		fontStyle,           // Стиль шрифта (курсив, подчеркивание)
		0,                   // Подчеркивание
		0,                   // Зачеркивание
		DEFAULT_CHARSET,     // Набор символов
		OUT_OUTLINE_PRECIS,  // Точность вывода
		CLIP_DEFAULT_PRECIS, // Точность обрезки
		CLEARTYPE_QUALITY,   // Качество рендеринга
		DEFAULT_PITCH | FF_DONTCARE, // Расстояние между символами и семейство шрифта
		L"Arial"             // Имя шрифта
	);

	return hFont;
}

