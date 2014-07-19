#include <vector>
#include <stdio.h>
#include <ctype.h>
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib")

void trim(char*);

class Client {
private:
	SOCKET sock;
public:
	char buf[1024];
	void conn();
	void listen();
};