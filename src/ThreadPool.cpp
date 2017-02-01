
#include <unistd.h>
#include "../headers/ThreadPool.h"

static void *startTasks(void *arg) {
    ThreadPool *threadPool = (ThreadPool *)arg;
    threadPool->doTasks();
    return NULL;
}

ThreadPool::ThreadPool(int poolSize): poolSize(poolSize) {
    for (int i=0; i<poolSize; i++) {
        pthread_t tID;
        int ret = pthread_create(&tID, NULL, startTasks, (void*)this);
        if (ret != 0) {
            threads.push_back(tID);
        }
    }
    stop = false;
    pthread_mutex_init(&tasksLock, NULL);
    sem_init(&notifyTaskSemaphore, 0, 0);
}

ThreadPool::~ThreadPool() {
    terminate();
    pthread_mutex_destroy(&tasksLock);
    sem_destroy(&notifyTaskSemaphore);
};

void ThreadPool::doTasks() {
    while(!stop) {
        sem_wait(&notifyTaskSemaphore);
        pthread_mutex_lock(&tasksLock);
        if (!tasks.empty()) {
            Task* task = tasks.front();
            tasks.pop_front();
            pthread_mutex_unlock(&tasksLock);
            task->execute();
            delete task;
        }
        else {
            pthread_mutex_unlock(&tasksLock);
        }
    }
}

void ThreadPool::addTask(Task* task) {
    tasks.push_back(task);
    sem_post(&notifyTaskSemaphore);
}

void ThreadPool::terminate() {
    stop = true;
}


