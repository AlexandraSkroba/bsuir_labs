#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <conio.h>

#include <winsock2.h> // �-� ��� ������ � ����� 
#pragma comment(lib, "WS2_32.lib")
#pragma warning(disable : 4996)

// ������� ��� ��������� ����� ������ � �������
void setConsoleColor(int color) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void chat(SOCKET s) {
	char mess[200];
	WSAEventSelect(s, 0, FD_READ);
	do {
		if ((GetKeyState(VK_F1) < 0) && (GetForegroundWindow() == GetConsoleWindow())) {
			printf("message: ");
			while (getch() != 0);
			scanf("\n%200[0-9a-zA-Z.,! ]", mess);
			send(s, mess, sizeof(mess), 0);
		}

		if (recv(s, mess, sizeof(mess), 0) > 0) {
			setConsoleColor(FOREGROUND_GREEN); 
			printf("%s\n", mess);
			setConsoleColor(FOREGROUND_INTENSITY);
		}

	} while (GetKeyState(VK_ESCAPE) >= 0);
}

int main() {
	WSADATA ws;
	// �������������� ������������� �������(������ ������� + ���������, ����������� ����� �������������)
	WSAStartup(MAKEWORD(2, 2), &ws);

	SOCKET s; // ���������� ������
	s = socket(AF_INET, SOCK_STREAM, 0); // (IPv4, TCP)

	SOCKADDR_IN sa; // ��������� � ����������� �����������
	memset(&sa, 0, sizeof(sa));
	sa.sin_family = AF_INET; // ������ IPv4
	sa.sin_port = htons(1234);

	char c;
	std::cout << "s - server\nc - client" << std::endl;
	std::cin >> &c;

	if (c == 'c') {
		char ip[100];
		printf("Set ip address to connect: ");
		scanf("\n%100[0-9.]", ip);

		sa.sin_addr.S_un.S_addr = inet_addr("127.0.0.1"); // ����� ���������� �����

		connect(s, (const sockaddr *)&sa, sizeof(sa)); // ���������� � �������� ��������� ��������� ����� � ��������� ����������

		chat(s);
	}

	if (c == 's') {
		bind(s, (const sockaddr*)&sa, sizeof(sa)); // ������ ��������� ����. �� ��� �����

		// ��������� ����. �� ������� �������� ���������
		listen(s, 100); // (�����, ������ �������)

		char buf[200];
		memset(buf, 0, sizeof(buf));

		SOCKET client_socket; // ����������� ������ �������
		SOCKADDR_IN client_addr;
		int client_addr_size = sizeof(client_addr);

		// ���� ����. ����. � ����������� ���� ���-�� �����������
		while (client_socket = accept(s, (sockaddr *)&client_addr, &client_addr_size))
		{
			std::cout << "Connect OK\n" << std::endl;

			chat(client_socket);
		}
	}
	
	closesocket(s);

	return 0;
}
