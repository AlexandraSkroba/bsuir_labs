#pragma once

#define OnFileButtonClicked		1
#define OnFolderButtonClicked	2
#define OnCopyButtonClicked		3
#define OnMoveButtonClicked		4
int currentProccesses = 0;

LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
WNDCLASS WindowClass(HBRUSH BGColor, HCURSOR Cursor, HINSTANCE hInst, LPCWSTR Name, WNDPROC wc);

IFileDialog* pFileDialog = NULL;

WCHAR fileName[MAX_PATH];
OPENFILENAMEW ofn;

LPWSTR folderName;
HRESULT folderHR;
DWORD folderOptions;

HWND selectedText;
HWND destinationText;
HWND hEditControl;

void MainWndAddWidget(HWND hWnd);
void SetOpenFileParams(HWND hWnd);
bool GetFolder(HWND hwnd);
void ChangeSelectedTextText();
void ChangeDestinationText();

DWORD CopyFunction(LPVOID lpParam);
DWORD MoveFunction(LPVOID lpParam);
