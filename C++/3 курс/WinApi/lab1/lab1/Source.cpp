#include <Windows.h>
#include <string.h>
#include <shlwapi.h>
#pragma comment(lib, "shlwapi.lib")
#include "Resource.h"

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
		default:
			break;
		}
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
				// Сохраняем изменения
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
	SetMenu(hwnd, RootMenu);
}

void MainWndAddWidget(HWND hwnd) {
	hEditConstrol = CreateWindow(L"edit", L" ", WS_VISIBLE | WS_CHILD | ES_MULTILINE |WS_VSCROLL , 30, 30, 490, 200, hwnd, NULL, NULL, NULL);
	CreateWindowA("button", "Clear", WS_VISIBLE | WS_CHILD, 30, 240, 475, 30, hwnd, (HMENU)OnButtonClicked, NULL, NULL);
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
