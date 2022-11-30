#include "Queue.h"
#include <iostream>
#include <string>
#include "Bank.h"
static std::string  getCurrentTimeStr()
{
	time_t t = time(NULL);
	char ch[64] = { 0 };
	strftime(ch, sizeof(ch)-1, "%Y-%m-%d %H:%M:%S", localtime(&t));     //年-月-日 时-分-秒
	return ch;
}

int main(int argc, const char * argv[])
{
	 int win_num = 4;
	//std::cout <<   getCurrentTimeStr()<<"\n";
	int time1, time2;
	std::cout << "======================欢迎光临大福银行======================" << std::endl;
	std::cout << "请输入银行开门和关门时间，9:00-12:00，请输入9 12" << "\n";
	cin >> time1 >> time2;
	std::cout << "窗口数量:" <<  std::endl;
	cin >> win_num;
	Bank b(time1, time2, win_num);
	b.Main_thread();
	return 0;
}