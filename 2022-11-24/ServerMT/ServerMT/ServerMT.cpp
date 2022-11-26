// ServerMT.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "stdio.h"
#include "winsock2.h"
#include "stdlib.h"
#define MAXCLIENTS 2

#pragma comment(lib,"ws2_32")
/*
多线程
SOCKET
*/

DWORD WINAPI ProcessRecvClientResponse(LPVOID lpParam)
{
	SOCKET* clientsocket = (SOCKET*)lpParam;
	char* msg = "您已成功连接至服务器\r\n";
	send(*clientsocket, msg, strlen(msg) + sizeof(char), NULL);
	while (TRUE)
	{
		char buffer[MAXBYTE] = { 0 };
		recv(*clientsocket, buffer, MAXBYTE, NULL);
		if (strcmp(buffer, "退出") == 0)
		{
			char* exit_msg = "再见 \r\n";
			send(*clientsocket, exit_msg, strlen(exit_msg) + sizeof(char), NULL);
			printf("一个客户端已退出\n");
			break;
		}
		printf("\n客户端: %s\n", buffer);
	}
	closesocket(*clientsocket);
	return 0;
}

DWORD WINAPI ProcessSendServerResponse(LPVOID lpParam)
{
	SOCKET* clientsocket = (SOCKET*)lpParam;
	while (TRUE)
	{
		getchar();
		char* mymsg = new char[10000];
		printf("请输入消息\n ->");
		gets(mymsg);
		send(*clientsocket, mymsg, strlen(mymsg) + sizeof(char), NULL);
	}
	closesocket(*clientsocket);
	return 0;
}


int main()
{
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);


	SOCKET s = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

	sockaddr_in sockaddr;
	sockaddr.sin_family = PF_INET;
	sockaddr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	sockaddr.sin_port = htons(9000);

	bind(s, (SOCKADDR*)&sockaddr, sizeof(SOCKADDR));

	listen(s, 1);

	printf("***服务器端***\n");
	printf("正在监听端口[%d].\n", 9000);

	char* msg = new char[1000];

	HANDLE threads[MAXCLIENTS];    //线程存放 数组
	HANDLE threads2;
	int CountClient = 0;
	while (TRUE)
	{
		SOCKADDR clientAddr;
		int size = sizeof(SOCKADDR);
		SOCKET clientsocket;
		clientsocket = accept(s, &clientAddr, &size);        //阻塞模式 直到有新的Tcp 接入
		if (CountClient < MAXCLIENTS)                        //创建新线程
		{
			threads[CountClient++] = CreateThread(NULL, 0, &ProcessRecvClientResponse, &clientsocket, 0, NULL);
			threads2= CreateThread(NULL, 0, &ProcessSendServerResponse, &clientsocket, 0, NULL);
		}
		else                                                //线程数超了 拒绝服务
		{
			char *msg = "服务器过载,已拒绝连接!.\r\n";
			send(clientsocket, msg, strlen(msg) + sizeof(char), NULL);
			printf("新的客户端尝试连接,但被服务器拒绝.\n");
			closesocket(clientsocket);
			break;
		}
		printf("新的客户端已连接 id: %d .\n", CountClient);            //
	}

	printf("客户端数量已达到最大值: %d.\r\n", MAXCLIENTS);
	WaitForMultipleObjects(MAXCLIENTS, threads, TRUE, INFINITE);
	WaitForMultipleObjects(1, &threads2, TRUE, INFINITE);

	closesocket(s); //关闭socket

	for (int i = 0; i < MAXCLIENTS; i++)
	{
		CloseHandle(threads[i]);
	}
	CloseHandle(threads2);

	WSACleanup();
	getchar();
	exit(0);
	return 0;
}