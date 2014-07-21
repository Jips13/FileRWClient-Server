#include "header.h"

Client::Client()
{
	//connection();
	listen();
}

void Client::connection()
{
	WSAStartup(0x202, (LPWSADATA)&buf[0]);
	sock = socket(AF_INET, SOCK_STREAM, 0);
	sockaddr_in adr;
	adr.sin_family = AF_INET;
	adr.sin_port = htons(SERVER_PORT);
	adr.sin_addr.S_un.S_addr = inet_addr(SERVER_IP);
	bind(sock, (sockaddr*)&adr, sizeof(adr));
	connect(sock, (sockaddr*)&adr, sizeof(adr));
}

void Client::close()
{
	shutdown(sock, SD_BOTH);
	closesocket(sock);
	WSACleanup();
}

void Client::listen()
{
	while (true)
	{
		fgets(buf, sizeof(buf)-1, stdin);
		if (strcmp(buf, "quit\n") == 0)
		{
			close();
			break;
		}
		std::vector<char*> request(4);
		request[0] = PROTOCOL_ID;
		char *pch, msg[1024] = "";
		int operation = 0;
		if (strlen(buf) == 1)
		{
			printf("Error: You sent an empty string. Try again.\n");
			continue;
		}
		pch = strtok(buf, " ");
		for (unsigned int i = 0; i < strlen(pch); i++)
			pch[i] = toupper(pch[i]);
		if (!isOperationSupported(pch))
		{
			printf("Error: This function is not supported.\n");
			continue;
		}
		request[1] = pch;
		pch = strtok(NULL, " ");
		while (true)
		{
			if (pch != NULL) strcat(msg, " ");
			else break;
			strcat(msg, pch);
			pch = strtok(NULL, " ");
		}
		trim(msg);
		if (strlen(msg) == 0)
		{
			printf("Error: You have not sent a message.\n");
			continue;
		}
		request[2] = new char[16];
		itoa(strlen(msg), request[2], 10);
		request[3] = msg;
		printf("To Server: %s - %s - %s - %s\n", request[0], request[1], request[2], request[3]);
		send(sock, (char*)request.data(), request.size(), 0);
	}
}

bool Client::isOperationSupported(char *operation)
{
	std::vector<char*> COMMANDS;
	COMMANDS.push_back("ADD");
	COMMANDS.push_back("REMOVE");
	COMMANDS.push_back("DISPLAY");
	for (std::vector<char*>::iterator it = COMMANDS.begin(); it != COMMANDS.end(); it++)
	{
		if (strcmp(operation, *it) == 0)
			return true;
	}
	return false;
}