#include <stdlib.h>
#include <stdio.h>
#include <cstdio>
#pragma comment(lib, "ws2_32.lib")
#include <winsock2.h>
#include "Server.h"
#include "commands.cpp"

Server::Server()
{
	Connect();
}

void Server::Connect(void)
{
	/*WSAStartup(0x202,(LPWSADATA)&buf[0]);
	SOCKET s1 = socket(AF_INET,SOCK_STREAM,0);

	sockaddr_in add;
	sockaddr_in add2;
	int len=0;
	add.sin_addr.S_un.S_addr=inet_addr("192.168.2.2");
	add.sin_family=AF_INET;
	add.sin_port=htons(65000);

	int bind1=bind(s1,(sockaddr*)&add,sizeof(add));
	int lis = listen(s1,0x100);
	len = sizeof(add2);
	memset(buf, 0, sizeof(buf));

	FILE* file=NULL;
	while (SOCKET s2 = accept(s1,(sockaddr*)&add2,&len))
	{
		int rec=0;
		while(rec=recv(s2,&buf[0],sizeof(buf),0) && rec != SOCKET_ERROR)
		{
			if(strlen(buf) > 0)
			printf("String received = %s\n", buf);
			//parse(&file,buf);
		}
	}*/
	FILE* file=NULL;
	buf[0] = '3';
	buf[1] = '1';
	buf[2] = '0';
	buf[3] = '0';
	buf[4] = '0';
	buf[5] = '5';
	buf[6] = 's';
	buf[7] = 'l';
	buf[8] = 'o';
	buf[9] = 'v';
	buf[10] = 'o';
	parse(&file,buf);
	
	
}


void Server::parse(FILE** file, char *buf)
{
	int len=0;
	if(buf[0] == '3')
	{
		//int ind_comand = atoi(buf+1);
		char lenData[4];
		strncpy(lenData, buf+2,4);
		len = atoi(lenData);
		char Data[1018];

		switch(buf[1])
		{
		case ('1'):
			{
				
				add(file,strncpy(Data, buf+6,len));
				break;
			}
		
		case ('2'):
			{
				removeStr(file,buf[6]);
				break;
			}
		case ('3'):
			{
				break;
			}
		}

	}
}
void Server::add(FILE** file, char str[])
{
	*file = fopen("E:\\name_file.txt","a");
	fprintf((*file),str);
	fprintf((*file),"\n");
	fclose(*file);
}
void Server::removeStr(FILE** file, int ind)
{
	char read[1018];
	int numstr=0;
	(*file) = fopen("E:\\name_file.txt","r");
	FILE* file2 = NULL;
	(file2) = fopen("E:\\name_file2.txt","w");
	while(file!=NULL)
	{
		numstr++;
		if(numstr!=ind)
		{
			fscanf((*file),"&[^\n]",read);
			fprintf(file2,read);
		}
	}
	remove("E:\\name_file.txt");
	rename("E:\\name_file2.txt","E:\\name_file.txt");
}











