// Client.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "stdio.h"
#include "stdlib.h"
#include "SocketForClient.h"



//接受服务器广播的信息
DWORD WINAPI ProcessRecvServerResponse(LPVOID lpParam)
{
	SOCKET* clientSocket = (SOCKET*)lpParam;
	while (TRUE)
	{
		char buffer1[MAXBYTE] = { 0 };
		recv(*clientSocket, buffer1, MAXBYTE, NULL);
		printf("\n服务器: %s\n", buffer1);
	}
	return 0;
}

void main()
{
	SocketForClient socketForClient;

	HANDLE threadForRecvingServer;//该线程用来不断接收服务器信息


	sockaddr_in sockaddr;
	sockaddr.sin_family = PF_INET;
	sockaddr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	sockaddr.sin_port = htons(9000);

	socketForClient.myConnect((SOCKADDR*)&sockaddr);

	printf("***客户端***\n");
	char buffer[MAXBYTE] = { 0 };
	socketForClient.myRecv(buffer);
	printf("服务器: %s", buffer);
	
	threadForRecvingServer = CreateThread(NULL, 0, &ProcessRecvServerResponse, socketForClient.getSocket(), 0, NULL);

	while (TRUE)
	{


		//客户端向服务器发送信息
		getchar();
		char* mymsg = new char[10000];
		printf("请输入消息\n ->");
		gets(mymsg);
		socketForClient.mySend(mymsg);


		//当客户端发送"退出"时操作
		if (strcmp(mymsg, "退出") == 0){
			char* buffer2 = new char[1000];
			socketForClient.myRecv(buffer2);
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

	socketForClient.myCloseSocket();
	getchar();
	exit(0);

}