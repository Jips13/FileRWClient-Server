#include "header.h"

void Client::conn()
{
	WSAStartup(0x202, (LPWSADATA)&buf[0]);
	sock = socket(AF_INET, SOCK_STREAM, 0);
	sockaddr_in adr;
	adr.sin_family = AF_INET;
	adr.sin_port = htons(110714);
	adr.sin_addr.S_un.S_addr = inet_addr("192.168.2.1");
	bind(sock, (sockaddr*)&adr, sizeof(adr));
	connect(sock, (sockaddr*)&adr, sizeof(adr));
}

void Client::listen()
{
	while (true) {
		fgets(buf, sizeof(buf)-1, stdin);
		std::vector<char*> request(4);
		char *protoId = "845128";
		request[0] = protoId;
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
		std::vector<char*> COMMANDS;
		COMMANDS.push_back("ADD");
		COMMANDS.push_back("REMOVE");
		COMMANDS.push_back("DISPLAY");
		bool funcSupported = false;
		for (std::vector<char*>::iterator it = COMMANDS.begin(); it != COMMANDS.end(); it++)
		{
			if (strcmp(pch, *it) == 0)
			{
				funcSupported = true;
				break;
			}
		}
		if (!funcSupported)
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
		printf("%s - %s - %s - %s", request[0], request[1], request[2], request[3]);
		//can we send so?
		//send(sock, request.data(), request.size(), 0);
	}
}