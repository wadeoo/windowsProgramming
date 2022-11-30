#pragma once
#ifndef Bank_h
#define Bank_h

#include <stdio.h>
#include <iostream>
#include <queue>
#include <cstdlib>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>
#include "Customer.h"
#include "Queue.h"
#include "Win.h"

class Bank
{
private:
	bool exit;//是否销毁所有线程
	std::mutex mutex_t;
	std::condition_variable cond;//队列空的条件变量
	//std::condition_variable conds;//每个窗口繁忙的条件变量
	std::vector<std::thread> wins_thread;//线程窗口 每个线程对应下标相同的窗口


	int open_time;//开门时间 输入多少 就是几点
	int close_time;//关门时间 输入多少 就是几点
	int close_time2;//关门时间 开门后分钟
	int last;//  转换成开门后的分钟 最后被允许取号的时间
	int arr_time;//( 上一个顾客来的时间) 通过它来随机产生顾客顺序到来
	int num_customer;//顾客数量
	int num_win;//窗口数量
	std::vector<Win> win_v;//窗口数量
	//std::queue<Customer> que;//顾客队列
	Queue queue;

public:
	Bank(int t1, int t2, int num) :open_time(t1), close_time(t2), num_win(num)
	{
		close_time2 = (close_time - open_time) * 60;
		last = (close_time - open_time) * 60 - 20;//提前二十分钟不能取号
		arr_time = 0;
		num_customer = 0;
		for (int i = 0; i<num_win; i++)
		{
			Win w;
			w.set_num(i);
			win_v.emplace_back(w);
		}
	};
	~Bank() { Del_thread(); };
	void Create_Customer_thread();//多线程版本 产生用户放入队列 需要一个生产者线程
	void Create_thread();//创造线程
	void Del_thread(); //中止线程
	void Customer_into_thread(int i);//顾客处理函数 i窗口下标
	void Win_Customer_thread(int pos, Customer c);
	void Main_thread();

	//void Main();
	//void Create_Customer();//产生用户放入队列
	//void Customer_into();//顾客处理函数
	//void Win_Customer(int pos, Customer);//顾客办理业务
	void print_time(int time);//打印时间为时分秒那种
	void print_cust(Customer c);//顾客离开 打印顾客信息

};
#endif /* Bank_h */