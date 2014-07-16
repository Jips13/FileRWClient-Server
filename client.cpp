#include <stdio.h>
#include <winsock2.h>

#include "commands.cpp"

#pragma comment(lib, "ws2_32.lib")

class Client {
private:
	SOCKET sock;
public:
	char buf[1024];
	void conn();
	void listen();
};

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
	while(true) {
		fgets(buf, sizeof(buf) - 1, stdin);
		char line[1024] = "D", *pch, msg[1024] = "";
		pch = strtok(buf, " ");
		strcat(line, pch);
		pch = strtok(NULL, " ");
		while(pch != NULL)
		{
			strcat(msg, pch);
			strcat(msg, " ");
			pch = strtok(NULL, " ");
		}
		//strcat(line, len);
		printf("%s", msg);
		//send(sock, buf, strlen(buf), 0);
	}
}

void main()
{
	Client* client = new Client();
	client->listen();
}