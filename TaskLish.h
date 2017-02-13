#ifndef TASK_LIST_H
#define TASK_LIST_H

#include "SortedLinkedList.h"
#include "Task.h"

#include <iostream>

/*
"Comparator" struct that implements the operator() function which
returns the result of a "less than" comparison (simply, *obj1 < *obj2!).
*/

struct TaskComparator {
    bool operator()(const Task* firstTask, const Task* secondTask) const;
};

/*
TaskList provides an interface over a data structure that stores many tasks.
It provides functionality such as getting a specific task from the list,
adding a new task to the list, removing a specific task from the list,
and outputting all of the tasks in the list.
*/

class TaskList {
private:
    SortedLinkedList<Task*, TaskComparator> tasks;
public:
    void add(Task* task) { tasks.insert(task); }
    const Task* get(unsigned int position) const { return tasks.at(position); }
    Task* remove(unsigned int position) { return tasks.remove(position); }
    void remove(Task* task) { tasks.remove(task); }
    unsigned int size() const { return tasks.size(); }
    bool empty() const { return tasks.empty(); }
    void print(bool=false) const;
    void dump(ostream& out) const;
};

#endif
