#include"stdafx.h"
#include "SocketForServer.h"


SocketForServer::SocketForServer()
{

	m_socket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);



}

void SocketForServer::myBind(SOCKADDR* clientAddrPtr){
	bind(m_socket, clientAddrPtr, sizeof(SOCKADDR));
}

void SocketForServer::myListen(int backlog){
	listen(m_socket, backlog);
}

SOCKET SocketForServer::myAccept(SOCKADDR* clientAddrPtr){
	int size = sizeof(SOCKADDR);
	return accept(m_socket, clientAddrPtr, &size);
}

void SocketForServer::mySend(SOCKET clientSocket, const char* buf, int flags){
	send(clientSocket, buf, strlen(buf) + sizeof(char), flags);
}

void SocketForServer::myRecv(SOCKET clientSocket, char* buf, int flags){
	recv(clientSocket, buf, MAXBYTE, flags);
}

void SocketForServer::myCloseSocket(SOCKET socket){
	closesocket(socket);
}

SOCKET SocketForServer::getMySocket(){
	return m_socket;
}

SocketForServer::~SocketForServer()
{
}
