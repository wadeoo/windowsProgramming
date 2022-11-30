#include "Queue.h"


Queue::Queue(int queueSize)
{
	this->queueSize = queueSize + 1;
	q = (int*)malloc(sizeof(int)*queueSize);
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

void Queue::PushQueue(int key){
	//int tempTail = (tail + 1) % queueSize;
	//if (tempTail == head){
	//	cout << "�����Ѿ�����!" << endl;
	//}
	//else{
	//	q[tail] = key;
	//	tail = tempTail;
	//}

	if (IsQueueFull()){
		cout << "�����Ѿ�����!" << endl;
	}
	else{
		q[tail] = key;
		tail = (tail + 1) % queueSize;
	}
}

int Queue::PopQueue(){
	//int temp;
	//if (tail == head){
	//	cout << "����Ϊ��!" << endl;
	//}
	//else{
	//	temp = q[head];
	//	head = (head + 1) % queueSize;
	//}
	//return temp;

	int temp;
	if (IsQueueEmpty()){
		cout << "����Ϊ��!" << endl;
	}
	else{
		temp = q[head];
		head = (head + 1) % queueSize;
	}
	return temp;

}

void Queue::ShowQueueContent(){
	if (IsQueueEmpty()){
		cout << "����Ϊ��!" << endl;
	}
	else{
		int count = tail - head;
		for (int i = head; i < count+head; i++){
			cout << "�±�: " << i << " ֵ: " << q[i] << endl;
		}
	}
}

Queue::~Queue()
{
	free(q);
	q = nullptr;
}
