#include <Windows.h>
#include <string.h>
#include <shlwapi.h>
#pragma comment(lib, "shlwapi.lib")
#include <shlobj.h>
#include "Resource.h"


int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd) {
	WNDCLASS MainClass = WindowClass((HBRUSH)COLOR_WINDOW, LoadCursor(NULL, IDC_ARROW), hInstance, L"MainWndClass", WndProc);

	if (!RegisterClass(&MainClass)) { return -1; }

	MSG SoftwareMainMessage = { 0 };

	CreateWindow(L"MainWndClass", L"FileManager", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 200, 100, 610, 375, NULL, NULL, NULL, NULL);

	while (GetMessage(&SoftwareMainMessage, NULL, NULL, NULL)) {
		TranslateMessage(&SoftwareMainMessage);
		DispatchMessage(&SoftwareMainMessage);
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
		switch (wParam) {
		case OnFileButtonClicked:
			if (GetOpenFileNameW(&ofn)) {
				ChangeSelectedTextText();
			}

			break;
		case OnFolderButtonClicked:
			if (GetFolder(hwnd)) {
				ChangeDestinationText();
			}

			break;
		case OnCopyButtonClicked:

			if (!CreateThread(
					NULL,			// Атрибуты безопасности потока
					0,				// Размер стека потока
					CopyFunction,	// Функция, которую будет выполнять поток
					NULL,			// Параметры, передаваемые в CopyFunction
					0,				// Флаги создания потока
					NULL)) {		// Указатель на переменную для сохранения ID потока
				MessageBox(hwnd, L"Oops. Something went wrong.", L"Error!", MB_OK | MB_ICONERROR);
			}
			else {
				currentProccesses++;
			}

			break;
		case OnMoveButtonClicked:
			if (!CreateThread(NULL, 0, MoveFunction, NULL, 0, NULL)) {
				MessageBox(hwnd, L"Oops. Something went wrong.", L"Error!", MB_OK | MB_ICONERROR);
			}
			else {
				currentProccesses++;
			}
			break;
		}

		break;
	case WM_CREATE: {
		MainWndAddWidget(hwnd);
		SetOpenFileParams(hwnd);

		HRESULT hr = CoInitialize(NULL);

		if (SUCCEEDED(hr)) {
			hr = CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&pFileDialog));
			if (SUCCEEDED(hr)) {
				folderHR = pFileDialog->GetOptions(&folderOptions);
				if (SUCCEEDED(folderHR)) {
					pFileDialog->SetOptions(folderOptions | FOS_PICKFOLDERS);
				}
			}
		}
		else {
			MessageBox(hwnd, L"Can't create file dialog.", L"Error!", MB_OK | MB_ICONERROR);
			PostQuitMessage(0);
		}

		break;
	}
	case WM_CLOSE:
		if (currentProccesses > 0) {
			MessageBox(hwnd, L"Сannot close the application until the program execution is finished.", L"Error!", MB_OK | MB_ICONERROR);
		}
		else {
			DestroyWindow(hwnd);
		}

		break;
	case WM_DESTROY:
		pFileDialog->Release();
		CoUninitialize();
		PostQuitMessage(0);

		break;
	default: return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
}

void MainWndAddWidget(HWND hwnd) {

	CreateWindow(L"button", L"Copy", WS_VISIBLE | WS_CHILD , 190, 10, 100, 30, hwnd, (HMENU)OnCopyButtonClicked, NULL, NULL);
	CreateWindow(L"button", L"Move", WS_VISIBLE | WS_CHILD , 315, 10, 100, 30, hwnd, (HMENU)OnMoveButtonClicked, NULL, NULL);

	selectedText = CreateWindow(L"static", L"Selected file: ", WS_VISIBLE | WS_CHILD, 20, 70, 580, 20, hwnd, NULL, NULL, NULL);
	CreateWindow(L"button", L"Сhoose a file", WS_VISIBLE | WS_CHILD | WS_BORDER, 20, 95, 100, 25, hwnd, (HMENU)OnFileButtonClicked, NULL, NULL);

	destinationText = CreateWindow( L"static", L"Destination path: ", WS_VISIBLE | WS_CHILD, 20, 150, 580, 20, hwnd, NULL, NULL, NULL);
	CreateWindow(L"button", L"Destination", WS_VISIBLE | WS_CHILD | WS_BORDER, 20, 175, 100, 25, hwnd, (HMENU)OnFolderButtonClicked, NULL, NULL);

	hEditControl = CreateWindow(L"edit", L" ", WS_VISIBLE | WS_CHILD | ES_AUTOVSCROLL | WS_DISABLED | ES_MULTILINE, 20, 225, 560, 100, hwnd, NULL, NULL, NULL);
}


void SetOpenFileParams(HWND hwnd) {
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = hwnd;
	ofn.lpstrFile = fileName;
	ofn.nMaxFile = sizeof(fileName);
	ofn.lpstrFilter = L"All Files\0*.*\0";
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = L"D:\\С++\\WinApi";
	ofn.lpstrDefExt = NULL;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
}

bool GetFolder(HWND hwnd) {
	bool isSuccess = false;
	folderHR = pFileDialog->Show(NULL);
	if (SUCCEEDED(folderHR)) {
		IShellItem* pItem;
		folderHR = pFileDialog->GetResult(&pItem);
		if (SUCCEEDED(folderHR)) {
			folderHR = pItem->GetDisplayName(SIGDN_FILESYSPATH, &folderName);
			if (SUCCEEDED(folderHR)) {
				isSuccess = true;
			}
			pItem->Release();
		}
	}
	return isSuccess;
}

void ChangeSelectedTextText() {
	WCHAR newText[300];
	wcscpy_s(newText, L"Selected file: ");
	wcscat_s(newText, fileName);

	SetWindowText(selectedText, (LPWSTR)newText);
}

void ChangeDestinationText() {
	WCHAR newText[300];
	wcscpy_s(newText, L"Destination path: ");
	wcscat_s(newText, folderName);

	SetWindowText(destinationText, (LPWSTR)newText);
}

DWORD CopyFunction(LPVOID lpParam) {



	//if (lstrlen(fileName) == 0 || lstrlen(folderName) == 0) {
	//	MessageBox(NULL, L"Please select a file and a destination folder before copying.", L"Warning", MB_OK | MB_ICONWARNING);
	//	currentProccesses--;
	//	ExitThread(1);
	//	return 1;
	//}

	WCHAR path[MAX_PATH]; // полный путь к исходному файлу
	WCHAR filePath[MAX_PATH]; // только имя файла без пути
	WCHAR folder[MAX_PATH]; // полный путь к папке

	wcscpy_s(filePath, fileName);
	wcscpy_s(path, fileName);
	wcscpy_s(folder, folderName);

	WCHAR name[MAX_PATH];
	PathStripPath(filePath);
	lstrcpyW(name, filePath);

	WCHAR newPath[MAX_PATH];
	PathCombine(newPath, folder, name);
	SendMessage(hEditControl, EM_SETSEL, (WPARAM)-1, (LPARAM)-1);

	WCHAR message[MAX_PATH];
	wcscpy_s(message, L"Copying a file to ");
	wcscat_s(message, newPath);
	wcscat_s(message, L"\r\n");

	SendMessage(hEditControl, EM_SETSEL, (WPARAM)-1, (LPARAM)-1);
	SendMessage(hEditControl, EM_REPLACESEL, 0, (LPARAM)message);

	Sleep(10000);

	if (CopyFile(path, newPath, TRUE)) {

		SendMessage(hEditControl, EM_SETSEL, (WPARAM)-1, (LPARAM)-1);
		wcscpy_s(message, L"File was successfully copied to ");
		wcscat_s(message, newPath);
		wcscat_s(message, L"\r\n");
		SendMessage(hEditControl, EM_REPLACESEL, 0, (LPARAM)message);

		currentProccesses--;
		ExitThread(0);
		return 0;
	}

	SendMessage(hEditControl, EM_SETSEL, (WPARAM)-1, (LPARAM)-1);
	wcscpy_s(message, L"Error while copying a file to ");
	wcscat_s(message, newPath);
	wcscat_s(message, L"\r\n");
	SendMessage(hEditControl, EM_REPLACESEL, 0, (LPARAM)message);

	currentProccesses--;
	ExitThread(1);
	return 1;
}


DWORD MoveFunction(LPVOID lpParam) {
	
	/*if (lstrlen(fileName) == 0 || lstrlen(folderName) == 0) {
		MessageBox(NULL, L"Please select a file and a destination folder before moving.", L"Warning", MB_OK | MB_ICONWARNING);
		currentProccesses--;
		ExitThread(1);
		return 1;
	}*/

	WCHAR path[MAX_PATH];
	WCHAR folder[MAX_PATH];
	WCHAR filePath[MAX_PATH];

	if (lstrlen(path) == 0) {
		wcscpy_s(path, MAX_PATH, L"C:\\Users\\Александра\\Desktop\\Новый текстовый документ (2).txt");
	}
	if (lstrlen(folder) == 0) {
		wcscpy_s(folder, MAX_PATH, L"D:\\study\\Новый текстовый документ (2).txt");
	}

	wcscpy_s(filePath, fileName);
	wcscpy_s(path, fileName);
	wcscpy_s(folder, folderName);

	WCHAR name[MAX_PATH];
	PathStripPath(filePath);
	lstrcpyW(name, filePath);

	WCHAR newPath[MAX_PATH];
	PathCombine(newPath, folder, name);

	WCHAR message[MAX_PATH];
	wcscpy_s(message, L"Moving a file to ");
	wcscat_s(message, newPath);
	wcscat_s(message, L"\r\n");

	SendMessage(hEditControl, EM_SETSEL, (WPARAM)-1, (LPARAM)-1);
	SendMessage(hEditControl, EM_REPLACESEL, 0, (LPARAM)message);

	Sleep(10000);
	if (MoveFileW(path, newPath)) {

		SendMessage(hEditControl, EM_SETSEL, (WPARAM)-1, (LPARAM)-1);
		wcscpy_s(message, L"File was successfully moved to ");
		wcscat_s(message, newPath);
		wcscat_s(message, L"\r\n");
		SendMessage(hEditControl, EM_REPLACESEL, 0, (LPARAM)message);

		currentProccesses--;
		ExitThread(0);
		return 0;
	}

	SendMessage(hEditControl, EM_SETSEL, (WPARAM)-1, (LPARAM)-1);
	wcscpy_s(message, L"Error while moving a file to ");
	wcscat_s(message, newPath);
	wcscat_s(message, L"\r\n");
	SendMessage(hEditControl, EM_REPLACESEL, 0, (LPARAM)message);

	currentProccesses--;
	ExitThread(1);
	return 1;

}
