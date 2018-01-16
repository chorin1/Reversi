/**
*  Reversi - Advanced Programming 1
*  Ex: #7
*  Thread pool to handle server threads efficiently.
*  task assigned to the pool will be queued until a thread will be available to handle that task
*  long-term tasks should not be handled by the pool as they will lock the queue.
*/

#pragma once
#include "Task.h"
#include <queue>
#include <pthread.h>

using std::queue;

class ThreadPool {
public:
	// create a thread pool of threadsNum threads
	ThreadPool(int threadsNum);
	// add a new task to the queue
	void addTask(Task *task);
	// terminate the threadPool
	void terminate();
	virtual ~ThreadPool();
private:
	queue<Task *> tasksQueue;
	pthread_t* threads;
	// start executing tasks in the queue
	void executeTasks();
	bool stopped;
	pthread_mutex_t taskQueueLock;
	// static for pthread_create
	static void *execute(void *arg);
};