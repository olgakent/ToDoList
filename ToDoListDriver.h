#ifndef TO_DO_LIST_DRIVER_H
#define TO_DO_LIST_DRIVER_H

#include "TaskLish.h"

#include <iostream>

/*
ToDoListDriver provides an interface over two TaskLists—one that represents the
outstanding tasks and another that represents the completed tasks.

It provides functionality such as:
- creating a new outstanding task,
- removing a specific outstanding task,
- marking a specific outstanding task as complete, and
- outputting the outstanding/completed tasks in non-detailed/detailed manners.
*/


class ToDoListDriver {
private:
    TaskList outstandingTasks;
    TaskList completedTasks;
public:

    void addOutstandingTask(Task* task) { outstandingTasks.add(task); }
    void addCompletedTask(Task* task) { completedTasks.add(task); }
    Task* removeOutstandingTask(unsigned int position) { return outstandingTasks.remove(position); }
    void removeOutstandingTask(Task* task) { return outstandingTasks.remove(task); }
    Task* removeCompletedTask(unsigned int position) { return completedTasks.remove(position); }
    void removeCompletedTask(Task* task) { return completedTasks.remove(task); }
    unsigned int outstandingTasksSize() const { return outstandingTasks.size(); }
    bool outstandingTasksEmpty() const { return outstandingTasks.empty(); }
    unsigned int completedTasksSize() const { return completedTasks.size(); }
    bool completedTasksEmpty() const { return completedTasks.empty(); }
    void printOutstandingTasks(bool=false) const;
    void printCompletedTasks(bool=false) const;
    void dumpOutstandingTasks(ostream& out) const { outstandingTasks.dump(out); }
    void dumpCompletedTasks(ostream& out) const { completedTasks.dump(out); }
};

#endif
