#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <conio.h>

#include <winsock2.h> // ф-и дл€ работы с сетью 
#pragma comment(lib, "WS2_32.lib")
#pragma warning(disable : 4996)

// ‘ункци€ дл€ установки цвета текста в консоли
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
	// инициализируем использование сокетов(верси€ сокетов + структура, заполн€етс€ после инициализации)
	WSAStartup(MAKEWORD(2, 2), &ws);

	SOCKET s; // дискриптор сокета
	s = socket(AF_INET, SOCK_STREAM, 0); // (IPv4, TCP)

	SOCKADDR_IN sa; // структура с настройками соедеинени€
	memset(&sa, 0, sizeof(sa));
	sa.sin_family = AF_INET; // только IPv4
	sa.sin_port = htons(1234);

	char c;
	std::cout << "s - server\nc - client" << std::endl;
	std::cin >> &c;

	if (c == 'c') {
		char ip[100];
		printf("Set ip address to connect: ");
		scanf("\n%100[0-9.]", ip);

		sa.sin_addr.S_un.S_addr = inet_addr("127.0.0.1"); // адрес локального компа

		connect(s, (const sockaddr *)&sa, sizeof(sa)); // соединение с сервером использу€ созданный сокет и настройки соединени€

		chat(s);
	}

	if (c == 's') {
		bind(s, (const sockaddr*)&sa, sizeof(sa)); // биндим настройки соед. на наш сокет

		// прослушка соед. на наличие вход€щих сообщений
		listen(s, 100); // (сокет, размер очереди)

		char buf[200];
		memset(buf, 0, sizeof(buf));

		SOCKET client_socket; // индификатор сокета клиента
		SOCKADDR_IN client_addr;
		int client_addr_size = sizeof(client_addr);

		// ждем вход. соед. и выполн€емс€ если кто-то подключилс€
		while (client_socket = accept(s, (sockaddr *)&client_addr, &client_addr_size))
		{
			std::cout << "Connect OK\n" << std::endl;

			chat(client_socket);
		}
	}
	
	closesocket(s);

	return 0;
}
