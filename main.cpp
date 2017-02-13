#include "ToDoListApp.h"

#include <iostream>
using namespace std;

int main() {

    cout << "Welcome to your To-Do List! For a full list of commands, type \"HELP\".\n" << endl;

    ToDoListApp app;
    app.run();
    return 0;
}
