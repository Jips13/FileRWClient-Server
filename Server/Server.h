class Server
{
public:
	char buf[1024];
	void Connect();
	Server();
private:
	SOCKET sock;
	void parse(FILE** file, char *buf);
	void add(FILE** file, char str[]);
	void removeStr(FILE** file, int ind);
};