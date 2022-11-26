///////////////////////////////////////////////////////////////
// PriorityDemo.cpp�ļ�



#include <stdio.h>
#include <windows.h>

int g_nCount1 = 0,g_nCount2=0;

DWORD WINAPI ThreadIdle(LPVOID lpParam)
{
	int i = 0;
	while(i++<50)
		printf("Idle Thread is running \n");

	g_nCount1++;
	return 0;
}

DWORD WINAPI ThreadNormal(LPVOID lpParam)
{
	int i = 0;
	while(i++<50)
		printf(" Normal Thread is running \n");

	g_nCount2++;
	return 0;
}
int main(int argc, char* argv[])
{
	DWORD dwThreadID;
	HANDLE h[2];
	
	// ����һ�����ȼ�ΪIdle���߳�
	h[0] = ::CreateThread(NULL, 0, ThreadIdle, NULL,
		CREATE_SUSPENDED, &dwThreadID);
	::SetThreadPriority(h[0], THREAD_PRIORITY_IDLE);
	::ResumeThread(h[0]);

	// ����һ�����ȼ�ΪNormal���߳�
	h[1] = ::CreateThread(NULL, 0, ThreadNormal, NULL,
		0, &dwThreadID);
	
	// �ȴ������߳��ں˶��󶼱������״̬
	DWORD dw=::WaitForMultipleObjects(
		2,	    // DWORD nCount  Ҫ�ȴ����ں˶��������
		h,	    // CONST HANDLE *lpHandles �������
		TRUE,	    // BOOL bWaitAll	ָ���Ƿ�ȴ������ں˶���������״̬
		100);  // DWORD dwMilliseconds Ҫ�ȴ���ʱ��
   	
	::CloseHandle(h[0]);
	::CloseHandle(h[1]);

	printf("g_nCount1 = %d \n", g_nCount1);
	printf("g_nCount2 = %d \n", g_nCount2);
	

	system("pause");

	return 0;
}

/*
	HANDLE h[2];
	h[0] = hThread1;
	h[1] = hThread2;
	DWORD dw = ::WaitForMultipleObjects(2, h, FALSE, 5000);
	switch(dw)
	{
	case WAIT_FAILED:
		// ����WaitForMultipleObjects����ʧ��(�����Ч��)
		break;
	case WAIT_TIMEOUT:
		// ��5����û��һ���ں˶�������
		break;
	case WAIT_OBJECT_0 + 0:
		// ���h[0]��Ӧ���ں˶�������
		break;
	case WAIT_OBJECT_0 + 1:
		// ���h[1]��Ӧ���ں˶�������
		break;
	}
*/