
#ifndef TRANSPORTATION_THREADPOOL_H
#define TRANSPORTATION_THREADPOOL_H


#include <vector>
#include <deque>
#include <pthread.h>
#include <semaphore.h>
#include "Task.h"

class ThreadPool {
private:
    int poolSize;
    std::vector<pthread_t> threads;
    std::deque<Task*> tasks;
    pthread_mutex_t tasksLock;
    sem_t notifyTaskSemaphore;
    bool stop;
public:
    ThreadPool(int poolSize);
    ~ThreadPool();
    void doTasks();
    void addTask(Task * task);
    void terminate();
};

#endif //TRANSPORTATION_THREADPOOL_H
