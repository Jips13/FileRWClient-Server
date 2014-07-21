#include <vector>
#include <stdio.h>
#include <ctype.h>
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib")

#define SERVER_IP "192.168.1.6"
#define SERVER_PORT 110714

#define PROTOCOL_ID "845128"

void trim(char*);

class Client {
private:
	SOCKET sock;
	char buf[1024];
	void connection();
	void close();
	void listen();
	bool isOperationSupported(char*);
public:
	Client();
};