///////////////////////////////////////////////////////////////
// ThreadDemo.cpp文件



#include <stdio.h>
#include <windows.h>
#include <iostream>

BOOL g_bContinue = TRUE;
int count = 0;

// 线程函数
DWORD WINAPI ThreadProc(LPVOID lpParam)
{
	if (g_bContinue){

	int i = 0;
	//while(i < 20)
	//{
	//	printf(" I am from a thread, count = %d \n", i++);
	//}
	count++;
	return 0;
	
	}
}

int  main(int argc, char* argv[])
{
	HANDLE hThread;
	DWORD dwThreadId;
	
	// 创建一个线程
	hThread = ::CreateThread (
		NULL,		// 默认安全属性
		NULL,		// 默认堆栈大小
		ThreadProc,	// 线程入口地址（执行线程的函数）
		NULL,		// 传给函数的参数
		0,		// 指定线程立即运行
		&dwThreadId);	// 返回线程的ID号
	printf(" Now another thread has been created. ID = %d \n", dwThreadId);

	Sleep(4000);
	g_bContinue = FALSE;
	std::cout << count << std::endl;


	// 等待新线程运行结束
	::WaitForSingleObject (hThread, INFINITE);
	::CloseHandle (hThread);

	system("pause");
	return 0;
}

