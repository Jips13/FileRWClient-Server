#include <vector>
#include <stdio.h>
#include <ctype.h>
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib")

#define SERVER_IP "192.168.2.2"
#define SERVER_PORT 65000

#define PROTOCOL_ID 3

void trim(char*);

class Client {
private:
	SOCKET sock;
	char buf[1024];
	void connection();
	void close();
	void listen();
	int getOperationId(char*);
public:
	Client();
};