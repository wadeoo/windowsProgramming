#include "Queue.h"


Queue::Queue(int queueSize)
{
	this->queueSize = queueSize + 1;
	q = (Customer*)malloc(sizeof(Customer)*queueSize);
	tail = 0;
	head = 0;
}


int Queue::IsQueueEmpty(){
	if (head == tail){
		return 1;
	}
	else{
		return 0;
	}
}

int Queue::IsQueueFull(){
	if ((tail + 1) % queueSize == head){
		return 1;
	}
	else{
		return 0;
	}
}

void Queue::PushQueue(Customer customer){
	//int tempTail = (tail + 1) % queueSize;
	//if (tempTail == head){
	//	cout << "队列已经满了!" << endl;
	//}
	//else{
	//	q[tail] = key;
	//	tail = tempTail;
	//}

	if (IsQueueFull()){
		cout << "队列已经满了!" << endl;
	}
	else{
		q[tail] = customer;
		tail = (tail + 1) % queueSize;
	}
}

Customer Queue::PopQueue(){//并移动头部指针
	//int temp;
	//if (tail == head){
	//	cout << "队列为空!" << endl;
	//}
	//else{
	//	temp = q[head];
	//	head = (head + 1) % queueSize;
	//}
	//return temp;

	Customer temp;
	if (IsQueueEmpty()){
		cout << "队列为空!" << endl;
	}
	else{
		temp = q[head];
		head = (head + 1) % queueSize;
	}
	return temp;

}

Customer Queue::GetHead(){
	if (IsQueueEmpty()){
		cout << "队列为空!" << endl;
		return Customer();
	}
	else{
		return q[head];
	}
}

//void Queue::ShowQueueContent(){
//	if (IsQueueEmpty()){
//		cout << "队列为空!" << endl;
//	}
//	else{
//		int count = tail - head;
//		for (int i = head; i < count+head; i++){
//			cout << "下标: " << i << " 值: " << q[i] << endl;
//		}
//	}
//}

Queue::~Queue()
{
	free(q);
	q = nullptr;
}
