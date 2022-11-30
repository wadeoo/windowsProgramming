// Client.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include "stdio.h"
#include "winsock2.h"
#include "stdlib.h"

#pragma comment(lib,"ws2_32")


//接受服务器广播的信息
DWORD WINAPI ProcessRecvServerResponse(LPVOID lpParam)
{
	SOCKET* serverSocket = (SOCKET*)lpParam;
	while (TRUE)
	{
		char buffer1[MAXBYTE] = { 0 };
		recv(*serverSocket, buffer1, MAXBYTE, NULL);
		printf("\n服务器: %s\n", buffer1);
	}
	return 0;
}

void main()
{
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	HANDLE threadForRecvingServer;//该线程用来不断接收服务器信息

	SOCKET s = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	sockaddr_in sockaddr;
	sockaddr.sin_family = PF_INET;
	sockaddr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	sockaddr.sin_port = htons(9000);

	connect(s, (SOCKADDR*)&sockaddr, sizeof(SOCKADDR));

	printf("***客户端***\n");
	char buffer[MAXBYTE] = { 0 };
	recv(s, buffer, MAXBYTE, NULL);
	printf("服务器: %s", buffer);
		
	threadForRecvingServer = CreateThread(NULL, 0, &ProcessRecvServerResponse, &s, 0, NULL);

	while (TRUE)
	{
		//客户端向服务器发送信息
		getchar();
		char* mymsg = new char[10000];
		printf("请输入消息\n ->");
		gets(mymsg);
		send(s, mymsg, strlen(mymsg) + sizeof(char), NULL);


		//当客户端发送"退出"时操作
		if (strcmp(mymsg, "退出") == 0){
			char* buffer2 = new char[1000];
			recv(s, buffer2, MAXBYTE, NULL);
			printf("服务器端: %s\n", buffer2);
			if (strcmp(buffer2, "再见") == 0)
			{
				break;
			}
			break;
		}
	}

	WaitForMultipleObjects(1, &threadForRecvingServer, TRUE, INFINITE);
	CloseHandle(threadForRecvingServer);

	closesocket(s);
	WSACleanup();
	getchar();
	exit(0);

}