///////////////////////////////////////////////////////////////
// 02MemRepair.cpp�ļ�

#include "stdafx.h"
#include "windows.h"
#include "stdio.h"
#include <iostream>

#include "MemRepair.h"

//BOOL FindFirst(DWORD dwValue);	// ��Ŀ����̿ռ���е�һ�β���
//BOOL FindNext(DWORD dwValue);	// ��Ŀ����̵�ַ�ռ���е�2��3��4�����β���

//DWORD g_arList[1024];		// ��ַ�б�
//int g_nListCnt;			// ��Ч��ַ�ĸ���
//HANDLE g_hProcess;		// Ŀ����̾��

CMemFinder memFinder;


//////////////////////

//BOOL WriteMemory(DWORD dwAddr, DWORD dwValue);
void ShowList();


int main(int argc, char* argv[])
{
	// ����02testor����
	char szFileName[] = "02testor.exe";
	STARTUPINFO si = { sizeof(si) };
	PROCESS_INFORMATION pi;
	::CreateProcess(NULL, szFileName, NULL, NULL, FALSE,
		CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi);
	// �ر��߳̾������Ȼ���ǲ�ʹ����
	::CloseHandle(pi.hThread);
	//memFinder.GetProcessHandle = pi.hProcess;

	// ����Ҫ�޸ĵ�ֵ
	int	iVal;
	printf(" Input val = ");
	scanf("%d", &iVal);

	// ���е�һ�β���
	memFinder.FindFirst(iVal);

	// ��ӡ�������Ľ��
	ShowList();


	while (memFinder.GetListCount() > 1)
	{
		printf(" Input val = ");
		scanf("%d", &iVal);

		// �����´�����
		memFinder.FindNext(iVal);

		// ��ʾ�������
		ShowList();
	}


	// ȡ����ֵ
	printf(" New value = ");
	scanf("%d", &iVal);

	// д����ֵ
	if (memFinder.WriteMemory(memFinder.operator[](0), iVal))
		printf(" Write data success \n");


	::CloseHandle(memFinder.GetProcessHandle());
	return 0;
}





// ��ӡ���������ĵ�ַ
void ShowList()
{
	for (int i = 0; i< memFinder.GetListCount(); i++)
	{
		printf("%08lX \n", memFinder.operator[](i));
	}
}
