///////////////////////////////////////////////////////////////
// ThreadDemo.cpp�ļ�



#include <stdio.h>
#include <windows.h>
#include <iostream>

BOOL g_bContinue = TRUE;
int count = 0;

// �̺߳���
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
	
	// ����һ���߳�
	hThread = ::CreateThread (
		NULL,		// Ĭ�ϰ�ȫ����
		NULL,		// Ĭ�϶�ջ��С
		ThreadProc,	// �߳���ڵ�ַ��ִ���̵߳ĺ�����
		NULL,		// ���������Ĳ���
		0,		// ָ���߳���������
		&dwThreadId);	// �����̵߳�ID��
	printf(" Now another thread has been created. ID = %d \n", dwThreadId);

	Sleep(4000);
	g_bContinue = FALSE;
	std::cout << count << std::endl;


	// �ȴ����߳����н���
	::WaitForSingleObject (hThread, INFINITE);
	::CloseHandle (hThread);

	system("pause");
	return 0;
}

