#pragma once
#ifndef Customer_h
#define Customer_h
#include <stdio.h>
#include <iostream>
#include<cstdlib>
using namespace std;
class Customer
{
private:
	//时间全部为开门之后的多少分钟
	int id;//顾客id
	//int win;//在那个窗口办理
	int arrive_time;//到达时间
	int leave_time;//离开时间
	int wait_time;//等待时间
	int start_time;//开始办理业务时间
	int process_time;//办理业务过程时间
	int total_time;//在银行呆的时间
public:
	//Customer(int num, int time1, int time2) :id(num), arrive_time(time1), process_time(time2)
	//{

	//};
	Customer(int num, int time1) :id(num), arrive_time(time1)//多线程版本 业务时间不着急产生
	{

	};

	Customer(){};

	inline int get_id()
	{
		return id;
	}

	//到达时间
	inline void set_arrive_time(int time)
	{
		arrive_time = time;
	}
	inline int get_arrive_time()
	{
		return arrive_time;
	}
	//离开时间
	inline int get_leave_time()
	{
		leave_time = start_time + process_time;
		return leave_time;
	}
	//业务开始时间
	inline int get_start_time()
	{
		return start_time;
	}
	//等待时机
	inline void set_wait_time(int time)//参数是窗口上一个用户结束时间
	{
		if (arrive_time >= time)//不用等待
		{
			wait_time = 0;
		}
		else
		{
			wait_time = time - arrive_time;
		}
		start_time = arrive_time + wait_time;
	}
	inline int get_wait_time()
	{
		return wait_time;
	}
	//业务时机
	inline void set_process_time(int time)
	{
		process_time = time;
	}

	inline int get_process_time()
	{
		return process_time;
	}
	//总时间
	inline int get_total_time()
	{
		return leave_time - arrive_time;
	}

};
#endif /* Customer_h */