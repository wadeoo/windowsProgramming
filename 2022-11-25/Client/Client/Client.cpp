// Client.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "stdio.h"
#include "stdlib.h"
#include "SocketForClient.h"



//���ܷ������㲥����Ϣ
DWORD WINAPI ProcessRecvServerResponse(LPVOID lpParam)
{
	SOCKET* clientSocket = (SOCKET*)lpParam;
	while (TRUE)
	{
		char buffer1[MAXBYTE] = { 0 };
		recv(*clientSocket, buffer1, MAXBYTE, NULL);
		printf("\n������: %s\n", buffer1);
	}
	return 0;
}

void main()
{
	SocketForClient socketForClient;

	HANDLE threadForRecvingServer;//���߳��������Ͻ��շ�������Ϣ


	sockaddr_in sockaddr;
	sockaddr.sin_family = PF_INET;
	sockaddr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	sockaddr.sin_port = htons(9000);

	socketForClient.myConnect((SOCKADDR*)&sockaddr);

	printf("***�ͻ���***\n");
	char buffer[MAXBYTE] = { 0 };
	socketForClient.myRecv(buffer);
	printf("������: %s", buffer);
	
	threadForRecvingServer = CreateThread(NULL, 0, &ProcessRecvServerResponse, socketForClient.getSocket(), 0, NULL);

	while (TRUE)
	{


		//�ͻ����������������Ϣ
		getchar();
		char* mymsg = new char[10000];
		printf("��������Ϣ\n ->");
		gets(mymsg);
		socketForClient.mySend(mymsg);


		//���ͻ��˷���"�˳�"ʱ����
		if (strcmp(mymsg, "�˳�") == 0){
			char* buffer2 = new char[1000];
			socketForClient.myRecv(buffer2);
			printf("��������: %s\n", buffer2);
			if (strcmp(buffer2, "�ټ�") == 0)
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