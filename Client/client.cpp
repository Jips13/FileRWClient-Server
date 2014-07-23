#define _CRT_SECURE_NO_WARNINGS

#include "header.h"

Client::Client()
{
	connection();
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
		char sendBuf[1028];
		sendBuf[0] = PROTOCOL_ID;
		char *pch, msg[127] = "";
		if (strlen(buf) == 1)
		{
			printf("Error: You sent an empty string. Try again.\n");
			continue;
		}
		pch = strtok(buf, " ");
		for (unsigned int i = 0; i < strlen(pch); i++)
			pch[i] = toupper(pch[i]);
		int operation = getOperationId(pch);
		if (operation == 0)
		{
			printf("Error: This function is not supported.\n");
			continue;
		}
		sendBuf[1] = (char)operation;
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
		sendBuf[2] = (char)strlen(msg);
		for(unsigned int i = 0; i < strlen(msg); i++)
		{
			sendBuf[3 + i] = msg[i];
		}
		sendBuf[3 + strlen(msg)] = '\0';
		printf("To Server: %s\n", sendBuf);
		send(sock, sendBuf, strlen(sendBuf), 0);
	}
}

int Client::getOperationId(char *operation)
{
	std::vector<char*> COMMANDS;
	COMMANDS.push_back("ADD");
	COMMANDS.push_back("REMOVE");
	COMMANDS.push_back("DISPLAY");
	int i = 0;
	for (std::vector<char*>::iterator it = COMMANDS.begin(); it != COMMANDS.end(); it++)
	{
		i++;
		if (strcmp(operation, *it) == 0)
			return i;
	}
	return 0;
}