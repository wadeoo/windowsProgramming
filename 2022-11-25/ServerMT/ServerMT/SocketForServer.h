#ifndef SOCKETFORSERVER_H
#define SOCKETFORSERVER_H
#include "stdafx.h"
#include "winsock2.h"
#pragma comment(lib,"ws2_32")
#pragma once
class SocketForServer
{
public:
	SocketForServer();
	~SocketForServer();
	void myBind(SOCKADDR* sockaddrPtr);
	void myListen(int backlog);
	SOCKET myAccept(SOCKADDR* clientAddrPtr);
	void mySend(SOCKET clientSocket, const char* buf, int flags);
	void myRecv(SOCKET clientSocket, char* buf, int flags);
	void myCloseSocket(SOCKET socket);
	SOCKET getMySocket();

private:
	SOCKET m_socket;
};
#endif

