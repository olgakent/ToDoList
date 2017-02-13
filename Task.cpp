#include "Task.h"

/* PRINT FUNCTIONS that display any specialized task information */

void Task::print(bool detailed) const {
    string type = getType();
    if (type != "") {
        type = " [" + type + "] ";
    }
    else {
        type = " ";
    }
    cout << "(" << deadline << " day" << (deadline != 1 ? "s" : "") << " from now)"
         << type << description << "\n";
}

void ShoppingTask::print(bool detailed) const {
    Task::print(detailed);
    if (detailed) {
        cout << "\tITEMS TO PURCHASE:\n";
        for (unsigned int i = 0, n = items.size(); i < n; i++) {
            cout << "\t" << items[i] << "\n";
        }
    }
}

void EventTask::print(bool detailed) const {
    Task::print(detailed);
    if (detailed) {
        cout << "\tWHERE: " << location << "\n"
             << "\tWHEN: " << time << "\n";
    }
}

void HomeworkTask::print(bool detailed) const {
    Task::print(detailed);
    if (detailed) {
        cout << "\tSUBJECT: " << subject << "\n";
    }
}

// Outputs task’s data to a file.
// Each individual component of a task’s data is separated by a pipe character
void ShoppingTask::dump(ostream& out) const {
    out << "S|" << deadline << "|" << description;
    for (unsigned int i = 0, n = items.size(); i < n; i++) {
        out << "|" << items[i];
    }
}
