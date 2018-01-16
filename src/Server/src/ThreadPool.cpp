/*
*  ThreadPool.cpp
*
*/

#include <unistd.h>
#include <iostream>
#include <cstdlib>
#include "../include/ThreadPool.h"
#include "../include/Logging.h"

using std::cout;
using std::endl;

ThreadPool::ThreadPool(int threadsNum) : stopped(false) {
	threads = new pthread_t[threadsNum];
    // create threads for the pool
	for (int i = 0; i < threadsNum; i++) {
		int rc = pthread_create(threads + i, NULL, execute, this);
		if (rc) {
			cout << "Error: unable to create thread, " << rc << endl;
			exit(-1);
		}
	}
	pthread_mutex_init(&taskQueueLock, NULL);
}
void* ThreadPool::execute(void *arg) {
	ThreadPool *pool = (ThreadPool *)arg;
	pool->executeTasks();
}
void ThreadPool::addTask(Task *task) {
	tasksQueue.push(task);
}
void ThreadPool::executeTasks() {
	while (!stopped) {
		pthread_mutex_lock(&taskQueueLock);
		if (!tasksQueue.empty()) {
			Task* task = tasksQueue.front();
			tasksQueue.pop();
			pthread_mutex_unlock(&taskQueueLock);
			LOG("thread is executing task");
			task->execute();
			LOG("task finished executing, deleting task arguments");
			free(task->arg);
			delete(task);
			LOG("deleted task arguments");
		}
		else {
			pthread_mutex_unlock(&taskQueueLock);
			sleep(1);
		}
	}
}
void ThreadPool::terminate() {
	stopped = true;
	pthread_mutex_destroy(&taskQueueLock);
}
ThreadPool::~ThreadPool() {
	delete[] threads;
}