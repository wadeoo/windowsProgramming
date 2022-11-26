#include "stdafx.h"

#include "SocketForClient.h"


SocketForClient::SocketForClient()
{
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);
	m_socketForClient = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
}

void SocketForClient::myConnect(const sockaddr* sockaddr){
	connect(m_socketForClient, sockaddr, sizeof(SOCKADDR));
}

void SocketForClient::myRecv(char* buffer){
	recv(m_socketForClient, buffer, MAXBYTE, NULL);
}

void SocketForClient::mySend(char* msg){
	send(m_socketForClient, msg, strlen(msg) + sizeof(char), NULL);
}

void SocketForClient::myCloseSocket(){
	closesocket(m_socketForClient);
	WSACleanup();
}

SOCKET* SocketForClient::getSocket(){
	return &m_socketForClient;
}



SocketForClient::~SocketForClient()
{
	closesocket(m_socketForClient);
	WSACleanup();
}
