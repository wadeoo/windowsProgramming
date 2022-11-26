#pragma once

#include <winsock2.h>	// 为了使用Winsock API函数
#include <stdio.h>
#include <windows.h>

// 告诉连接器与WS2_32库连接
#pragma comment(lib,"WS2_32.lib")

class SocketClassClient
{
public:
	SocketClassClient();
	~SocketClassClient();
};

