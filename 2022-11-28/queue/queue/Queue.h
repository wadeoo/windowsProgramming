#pragma once
#include <stdlib.h>
#include <iostream>
using namespace std;
class Queue
{
public:
	Queue(int queueSize=1);
	~Queue();
	void PushQueue(int key);
	int PopQueue();
	int IsQueueEmpty();
	int IsQueueFull();
	void ShowQueueContent();
private:
	int queueSize;
	int head, tail;
	int *q;
};

