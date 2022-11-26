///////////////////////////////////////////
// ClientDemo.cpp文件


#include <winsock2.h>	// 为了使用Winsock API函数
#include <stdio.h>
#include <windows.h>
//#include"SocketClassClient.h"

//// 告诉连接器与WS2_32库连接
#pragma comment(lib,"WS2_32.lib")

int main(int argc, char* argv[])
{
	// 初始化WS2_32.dll
	WSADATA wsaData; //wsa windows socket asynchronous
	WORD sockVersion = MAKEWORD(2, 0);
	::WSAStartup(sockVersion, &wsaData);
	
	// 创建套节字
	SOCKET s = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);//address family=af
	if(s == INVALID_SOCKET)
	{
		printf("Failed socket() \n");
		::WSACleanup();
		return 0;
	}

	// 也可以在这里调用bind函数绑定一个本地地址
	// 否则系统将会自动安排

	// 填写远程地址信息
	sockaddr_in servAddr; 
	servAddr.sin_family = AF_INET;
	servAddr.sin_port = htons(8888);
	// 注意，这里要填写服务器程序（10ServerDemo程序）所在机器的IP地址
	// 如果你的计算机没有联网，直接使用127.0.0.1即可
	//servAddr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	servAddr.sin_addr.S_un.S_addr = inet_addr("192.168.43.164");

	if (-1 == ::connect(s, (sockaddr*)&servAddr, sizeof(servAddr)))
	//if (::connect(s, (sockaddr*)&servAddr, sizeof(servAddr)) = -1)
	{  //double  float
		printf("Failed connect() \n");
		::WSACleanup();
		return 0;
	}
	

	// 接收数据
	char buff[256];
	int nRecv = ::recv(s, buff, 256, 0);
	if(nRecv > 0)
	{
		buff[nRecv] = '\0';
		printf(" 接收到数据：%s", buff);
	}

	while (TRUE)
	{
		char* mymsg = new char[10000];
		printf(" OK Now You Can Connect .\n ->");
		gets(mymsg);
		send(s, mymsg, strlen(mymsg) + sizeof(char), NULL);
	}
	  
	// 关闭套节字
	::closesocket(s);
	// 释放WS2_32库
	::WSACleanup();	
	return 0;
}
