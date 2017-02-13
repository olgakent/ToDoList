#include "ToDoListDriver.h"

void ToDoListDriver::printOutstandingTasks(bool detailed) const {
    outstandingTasks.print(detailed);
}

void ToDoListDriver::printCompletedTasks(bool detailed) const {
    completedTasks.print(detailed);
}
