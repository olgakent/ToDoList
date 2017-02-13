#include "TaskLish.h"

// implements the operator() function which returns the result of a "less than"
// comparison ( *obj1 < *obj2 )
bool TaskComparator::operator()(const Task* firstTask, const Task* secondTask) const {
    if (firstTask->getDeadline() < secondTask->getDeadline()) {
        return true;
    }
    else if (firstTask->getDeadline() == secondTask->getDeadline()) {
        return firstTask->getDescription() < secondTask->getDescription();
    }
    else {
        return false;
    }
}

void TaskList::print(bool detailed) const {
    unsigned int i = 1;
    for (auto it = tasks.begin(), it_end = tasks.end(); it != it_end; ++it, i++) {
        cout << i << ". ";
        (*it)->print(detailed);
    }
}

void TaskList::dump(ostream& out) const {
    for (auto it = tasks.begin(), it_end = tasks.end(); it != it_end; ++it) {
        (*it)->dump(out);
        out << "\n";
    }
}
