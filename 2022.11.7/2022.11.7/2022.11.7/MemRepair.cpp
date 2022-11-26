///////////////////////////////////////////////////////////////
// 02MemRepair.cpp文件

#include "stdafx.h"
#include "windows.h"
#include "stdio.h"
#include <iostream>

#include "MemRepair.h"

//BOOL FindFirst(DWORD dwValue);	// 在目标进程空间进行第一次查找
//BOOL FindNext(DWORD dwValue);	// 在目标进程地址空间进行第2、3、4……次查找

//DWORD g_arList[1024];		// 地址列表
//int g_nListCnt;			// 有效地址的个数
//HANDLE g_hProcess;		// 目标进程句柄

CMemFinder memFinder;


//////////////////////

//BOOL WriteMemory(DWORD dwAddr, DWORD dwValue);
void ShowList();


int main(int argc, char* argv[])
{
	// 启动02testor进程
	char szFileName[] = "02testor.exe";
	STARTUPINFO si = { sizeof(si) };
	PROCESS_INFORMATION pi;
	::CreateProcess(NULL, szFileName, NULL, NULL, FALSE,
		CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi);
	// 关闭线程句柄，既然我们不使用它
	::CloseHandle(pi.hThread);
	//memFinder.GetProcessHandle = pi.hProcess;

	// 输入要修改的值
	int	iVal;
	printf(" Input val = ");
	scanf("%d", &iVal);

	// 进行第一次查找
	memFinder.FindFirst(iVal);

	// 打印出搜索的结果
	ShowList();


	while (memFinder.GetListCount() > 1)
	{
		printf(" Input val = ");
		scanf("%d", &iVal);

		// 进行下次搜索
		memFinder.FindNext(iVal);

		// 显示搜索结果
		ShowList();
	}


	// 取得新值
	printf(" New value = ");
	scanf("%d", &iVal);

	// 写入新值
	if (memFinder.WriteMemory(memFinder.operator[](0), iVal))
		printf(" Write data success \n");


	::CloseHandle(memFinder.GetProcessHandle());
	return 0;
}





// 打印出搜索到的地址
void ShowList()
{
	for (int i = 0; i< memFinder.GetListCount(); i++)
	{
		printf("%08lX \n", memFinder.operator[](i));
	}
}
