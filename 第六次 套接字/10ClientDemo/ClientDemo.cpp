///////////////////////////////////////////
// ClientDemo.cpp�ļ�


#include <winsock2.h>	// Ϊ��ʹ��Winsock API����
#include <stdio.h>
#include <windows.h>
//#include"SocketClassClient.h"

//// ������������WS2_32������
#pragma comment(lib,"WS2_32.lib")

int main(int argc, char* argv[])
{
	// ��ʼ��WS2_32.dll
	WSADATA wsaData; //wsa windows socket asynchronous
	WORD sockVersion = MAKEWORD(2, 0);
	::WSAStartup(sockVersion, &wsaData);
	
	// �����׽���
	SOCKET s = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);//address family=af
	if(s == INVALID_SOCKET)
	{
		printf("Failed socket() \n");
		::WSACleanup();
		return 0;
	}

	// Ҳ�������������bind������һ�����ص�ַ
	// ����ϵͳ�����Զ�����

	// ��дԶ�̵�ַ��Ϣ
	sockaddr_in servAddr; 
	servAddr.sin_family = AF_INET;
	servAddr.sin_port = htons(8888);
	// ע�⣬����Ҫ��д����������10ServerDemo�������ڻ�����IP��ַ
	// �����ļ����û��������ֱ��ʹ��127.0.0.1����
	//servAddr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	servAddr.sin_addr.S_un.S_addr = inet_addr("192.168.43.164");

	if (-1 == ::connect(s, (sockaddr*)&servAddr, sizeof(servAddr)))
	//if (::connect(s, (sockaddr*)&servAddr, sizeof(servAddr)) = -1)
	{  //double  float
		printf("Failed connect() \n");
		::WSACleanup();
		return 0;
	}
	

	// ��������
	char buff[256];
	int nRecv = ::recv(s, buff, 256, 0);
	if(nRecv > 0)
	{
		buff[nRecv] = '\0';
		printf(" ���յ����ݣ�%s", buff);
	}

	while (TRUE)
	{
		char* mymsg = new char[10000];
		printf(" OK Now You Can Connect .\n ->");
		gets(mymsg);
		send(s, mymsg, strlen(mymsg) + sizeof(char), NULL);
	}
	  
	// �ر��׽���
	::closesocket(s);
	// �ͷ�WS2_32��
	::WSACleanup();	
	return 0;
}
