/**
*  Reversi - Advanced Programming 1
*  Ex: #7
*  Task interface used to assign tasks to the thread pool
*/

#pragma once

class Task {
public:
    Task(void* (*func)(void *arg), void* arg) :
            func(func), arg(arg) {}
    void execute() {
        func(arg);
    }
    virtual ~Task() {}
private:
    // function that the task executes
    void *(*func)(void *arg);
    // argument for the function
    void *arg;
    // so threadPool can free arguments after execution
    friend class ThreadPool;
};