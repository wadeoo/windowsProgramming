#pragma once
#ifndef SOCKETFORCLIENT_H
#define SOCKETFORCLIENT_H
#include "winsock2.h"

#pragma comment(lib,"ws2_32")

class SocketForClient
{
public:
	SocketForClient();
	~SocketForClient();
	void myConnect(const sockaddr* sockaddr);
	void myRecv(char* buffer);
	void mySend(char* msg);
	SOCKET* getSocket();
	void myCloseSocket();
	
private:
	SOCKET m_socketForClient;
};

#endif

