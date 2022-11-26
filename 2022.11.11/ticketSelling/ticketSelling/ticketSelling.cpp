///////////////////////////////////////////////////////////////
// CriticalSection.cpp文件

#include "stdafx.h"
#include <stdio.h>
#include <windows.h>
#include <process.h>
#include <iostream>
#include <string>

BOOL g_bContinue = TRUE;
int g_nCount = 0;
int c1 = 0, c2 = 0, c3 = 0;
int count4 = 0;

UINT uId1,uId2,uId3;
CRITICAL_SECTION g_cs; // 对存在同步问题的代码段使用临界区对象

UINT __stdcall ThreadFunc(LPVOID);

int main(int argc, char* argv[])
{

	HANDLE h[3];

	// 初始化临界区对象
	::InitializeCriticalSection(&g_cs);


	h[0] = (HANDLE)::_beginthreadex(NULL, 0, ThreadFunc, NULL, 0, &uId1);
	h[1] = (HANDLE)::_beginthreadex(NULL, 0, ThreadFunc, NULL, 0, &uId2);
	h[2] = (HANDLE)::_beginthreadex(NULL, 0, ThreadFunc, NULL, 0, &uId3);



	::WaitForMultipleObjects(3, h, TRUE, INFINITE);
	::CloseHandle(h[0]);
	::CloseHandle(h[1]);
	::CloseHandle(h[2]);

	// 删除临界区对象
	::DeleteCriticalSection(&g_cs);

		std::cout << "票已经售罄" << std::endl;
		std::cout << "1号窗口卖出" << c1 << "票" << std::endl;
		std::cout << "2号窗口卖出" << c2 << "票" << std::endl;
		std::cout << "3号窗口卖出" << c3 << "票" << std::endl;
		std::cout << count4<<std::endl;
	



	system("pause");

	return 0;
}

UINT __stdcall ThreadFunc(LPVOID)
{
	while (g_bContinue)
	{
		::EnterCriticalSection(&g_cs);
		if (g_nCount < 60){

			UINT threadId = GetCurrentThreadId();

			if (threadId == uId1){
				g_nCount++;
				c1++;
				std::cout << "1号窗售出第"<<g_nCount<<"票" << std::endl;
			}
			else if (threadId == uId2){
				g_nCount++;
				c2++;
				std::cout << "2号窗售出第"<<g_nCount<<"票" << std::endl;
			}
			else if (threadId == uId3){
				g_nCount++;
				c3++;
				std::cout << "3号窗售出第"<<g_nCount<<"票" << std::endl;
			}
		}
		else
		{
			g_bContinue = false;
		}
		::Sleep(30);
		::LeaveCriticalSection(&g_cs);
	}

	return 0;
}



//
//// SellTickets.cpp : 定义控制台应用程序的入口点。
////
//
//#include "stdafx.h"
//#include<process.h>
//#include<Windows.h>
//
//UINT __stdcall SellThread(LPVOID);
//CRITICAL_SECTION g_cs;
//int ticket = 1;
//BOOL bContinue = true;
//
//
//int _tmain(int argc, _TCHAR* argv[])
//{
//	UINT uId;
//	HANDLE h[3];
//
//	// 初始化临界区对象
//	::InitializeCriticalSection(&g_cs);
//
//	//创建售票窗口
//	h[0] = (HANDLE)::_beginthreadex(NULL, 0, SellThread, NULL, 0, &uId);
//	h[1] = (HANDLE)::_beginthreadex(NULL, 0, SellThread, NULL, 0, &uId);
//	h[2] = (HANDLE)::_beginthreadex(NULL, 0, SellThread, NULL, 0, &uId);
//	printf("%s", "《独行月球》售票开始！\n");
//
//
//	//等待三个线程执行完毕
//	WaitForMultipleObjects(3, h, TRUE, INFINITE);
//
//	//票售罄，输出卖票结束
//	::CloseHandle(h[0]);
//	::CloseHandle(h[1]);
//	::CloseHandle(h[2]);
//
//	// 删除临界区对象
//	::DeleteCriticalSection(&g_cs);
//
//	printf("%s", "《独行月球》售票结束！\n");
//
//	system("pause");
//
//	return 0;
//}
//
//UINT __stdcall SellThread(LPVOID) {
//
//	while (bContinue) {
//		::EnterCriticalSection(&g_cs);
//		if (ticket<61)
//		printf("窗口%d 卖出第%d张票,还剩%d张票\n", GetCurrentThreadId(), ticket++, 61 - ticket);
//		else
//		{
//			bContinue = false;
//		}
//		::LeaveCriticalSection(&g_cs);
//		Sleep(30);
//	}
//
//
//	return 0;
//}