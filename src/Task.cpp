
#include "../headers/Task.h"

Task::Task(void* (*func)(void *), void* arg): func(func), arg(arg) {
}

Task::~Task() {
}

void Task::execute() {
    func(arg);
}

