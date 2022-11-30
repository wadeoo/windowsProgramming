#pragma once
#include <stdlib.h>
#include <iostream>
#include "Customer.h"
using namespace std;
class Queue
{
public:
	Queue(int queueSize=1);
	~Queue();
	void PushQueue(Customer customer);
	Customer PopQueue();
	int IsQueueEmpty();
	int IsQueueFull();
	Customer GetHead();
	void ShowQueueContent();
private:
	int queueSize;
	int head, tail;
	Customer *q;
};

