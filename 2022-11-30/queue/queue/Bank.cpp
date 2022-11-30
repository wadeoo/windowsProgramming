#include "Bank.h"

using namespace std;
void Bank::Create_Customer_thread()//;//多线程版本 产生用户放入队列 需要一个生产者线程
{
	while (1)
	{
		int arrive = rand() % 8 + 1 + arr_time;//随机产生一个用户进入队列 1-8内来一个
		std::this_thread::sleep_for(std::chrono::milliseconds(arrive - arr_time + 500));
		//std::this_thread::sleep_for(std::chrono::seconds(arrive- arr_time));
		if (arrive > close_time2)
		{
			print_time(arrive);
			cout << "已经关门了 明个再来" << endl;
			exit = true;
			break;
		}

		arr_time = arrive;
		//bool empty = que.empty();//判断之前是否为空
		std::unique_lock<std::mutex> lk(mutex_t);//锁住
		Customer cust(num_customer, arrive);//多线程版本 办理业务时间在线程函数中生成
		//que.push(cust);
		queue.PushQueue(cust);
		num_customer++;
		cond.notify_one();

	}
}
void Bank::Create_thread()
{
	for (int i = 0; i < num_win; i++)
	{
		printf("窗口%d就绪\n", i + 1);
		wins_thread.emplace_back(std::thread(&Bank::Customer_into_thread, this, i));
		std::condition_variable temp;
		//conds.push_back(temp);
	}
};
void Bank::Del_thread() //中止线程
{
	for (int i = 0; i < wins_thread.size(); i++)
	{
		wins_thread[i].join();

	}
}
void Bank::Customer_into_thread(int i)//;//顾客处理函数 i窗口下标
{
	while (1)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		std::unique_lock<std::mutex> lk(mutex_t);//互斥锁 锁住

		//事实上用于不会很忙
		//while (que.empty() || win_v[i].is_busy())//如果队列空或者窗口很忙 等待
		while (queue.IsQueueEmpty() || win_v[i].is_busy())//如果队列空或者窗口很忙 等待
		{
			//if(win_v[i].is_busy())printf("窗口%d繁忙\n",i+1);
			//if(que.empty())printf("队列空 窗口%d空闲\n",i+1);
			cond.wait(lk);
		}

		//if (que.empty() && exit)
		if (queue.IsQueueEmpty() && exit)
		{
			cond.notify_all();
			break;//银行下班了
		}
		//不忙且队列不空
		Customer c = queue.GetHead();
		//Customer c = que.front();
		//que.pop();
		queue.PopQueue();
		//lk.unlock();
		if (c.get_arrive_time() > last)
		{
			cout << c.get_id() << "号 到达:";
			print_time(c.get_arrive_time());
			cout << "准备关门了 明个再来" << endl;
			cond.notify_all();
		}
		else
		{
			int process = rand() % 20 + 1 + 5;//业务办理时间  5-25min
			c.set_process_time(process);
			Win_Customer_thread(i, c);
		}

	}
	//Del_thread();
}

void Bank::Win_Customer_thread(int pos, Customer c)//顾客办理业务  这个w必须传实参 因为窗口会变的
{
	win_v[pos].set_busy();
	c.set_wait_time(win_v[pos].get_last_time());
	cout << "窗口:" << win_v[pos].get_num() + 1 << " ";
	print_cust(c);
	win_v[pos].set_last_time(c.get_leave_time());//窗口更新时间
	cout << endl;
	std::this_thread::sleep_for(std::chrono::milliseconds(c.get_process_time()));
	win_v[pos].set_nobusy();
}


void Bank::Main_thread()//;
{
	Create_thread();
	Create_Customer_thread();
	//Create_thread();
}

// void Bank::Main()
// {

//     Create_Customer();
//     Customer_into();
// }

void Bank::print_time(int time)//time是分钟
{
	int hour = time / 60 + open_time;
	int min = time % 60;
	cout << hour << ":" << min << " ";
};

void Bank::print_cust(Customer c)
{
	cout << c.get_id() << "号 到达:";
	print_time(c.get_arrive_time());
	cout << " 离开:";
	print_time(c.get_leave_time());
	cout << " 等待:" << c.get_wait_time();

	//print_time(c.get_wait_time());
	cout << " 开始办理:";
	print_time(c.get_start_time());
	cout << " 业务时间:" << c.get_process_time();
	//print_time(c.get_process_time());
	cout << " 总时间:" << c.get_total_time()<<endl;
	cout << c.get_id()<<" 号客户已完成," << c.get_id()+1<<"号客户可以接受业务服务"<<endl;
	//print_time(c.get_total_time());
}