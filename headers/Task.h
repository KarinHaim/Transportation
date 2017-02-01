
#ifndef TRANSPORTATION_TASK_H
#define TRANSPORTATION_TASK_H

class Task {
private:
    void* (*func)(void * arg);
    void* arg;
public:
    Task(void* (*func)(void *), void* arg);
    ~Task();
    void execute();
};


#endif //TRANSPORTATION_TASK_H
