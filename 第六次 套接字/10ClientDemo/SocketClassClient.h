#pragma once

#include <winsock2.h>	// Ϊ��ʹ��Winsock API����
#include <stdio.h>
#include <windows.h>

// ������������WS2_32������
#pragma comment(lib,"WS2_32.lib")

class SocketClassClient
{
public:
	SocketClassClient();
	~SocketClassClient();
};

