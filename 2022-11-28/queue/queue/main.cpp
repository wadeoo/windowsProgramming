#include "Queue.h"
int main(){
	Queue queue(4);
	queue.PushQueue(666);
	queue.PushQueue(123);
	queue.PushQueue(12);
	queue.PopQueue();
	queue.ShowQueueContent();




	return 0;
}