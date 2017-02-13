#include "ToDoListApp.h"

#include <cstdlib>
#include <cstring>
#include <fstream>
#include <sstream>
#include <iostream>

// Runs application based on the user's input commands and terminates under condition of EXIT
void ToDoListApp::run() {
    while (true) {
        AppCommand command = readAppCommand();
        switch (command) {
            case ADD:
                handleAdd();
                break;
            case PRINT:
                handlePrint();
                break;
            case DETAILED:
                handleDetailed();
                break;
            case REMOVE:
                handleRemove();
                break;
            case COMPLETE:
                handleComplete();
                break;
            case COMPLETED:
                handleCompleted();
                break;
            case UNDO:
                handleUndo();
                break;
            case REDO:
                handleRedo();
                break;
            case SAVE:
                handleSave();
                break;
            case LOAD:
                handleLoad();
                break;
            case EXIT:
                handleExit();
                return;
            case HELP:
                handleHelp();
                break;
            default:
                handleUndefined();
        }
    }
}

// Destructor to prevent memory leaks
ToDoListApp::~ToDoListApp() {
    clear(commandsToUndo);
    clear(commandsToRedo);
    for (unsigned i = 0, n = tasks.size(); i < n; i++) {
        delete tasks[i];
    }
}
void ToDoListApp::clear(stack<Command*>& commands){
    while(!commands.empty()){
        Command* command = commands.top();
        commands.pop();
        delete command;
    }
}

// HELPER READING FUCNTIONS

unsigned int ToDoListApp::readUnsignedInt() {
    unsigned int ui;
    cout << "> ";
    cin >> ui;
    cin.ignore();
    return ui;
}
char ToDoListApp::readChar() {
    char c;
    cout << "> ";
    cin >> c;
    cin.ignore();
    return c;
}
string ToDoListApp::readString() {
    string s;
    cout << "> ";
    getline(cin, s);
    return s;
}

// Reads command to perform from the user
ToDoListApp::AppCommand ToDoListApp::readAppCommand(){
    string command = readString();
    if(command == "ADD" || command == "add"){
        return ADD;
    }
    else if (command == "PRINT" || command == "print"){
        return PRINT;
    }
    else if (command == "DETAILED" || command == "detailed"){
        return DETAILED;
    }
    else if (command == "REMOVE" || command == "remove"){
        return REMOVE;
    }
    else if (command == "COMPLETE" || command == "complete"){
        return COMPLETE;
    }
    else if (command == "COMPLETED" || command == "completed"){
        return COMPLETED;
    }
    else if (command == "UNDO" || command == "undo"){
        return UNDO;
    }
    else if (command == "REDO" || command == "redo"){
        return REDO;
    }
    else if (command == "SAVE" || command == "save"){
        return SAVE;
    }
    else if (command == "LOAD" || command == "load"){
        return LOAD;
    }
    else if (command == "EXIT" || command == "exit"){
        return EXIT;
    }
    else if (command == "HELP" || command == "help"){
        return HELP;
    }
    else{
        return UNDEFINED;
    }
}

// Handles adding of a new task by using helper function to read the task from user.
void ToDoListApp::handleAdd(){
    Task* task = readTask();
    if(task){
        Command* command = new AddCommand(&driver, task);
        command->execute();
        commandsToUndo.push(command);
        clear(commandsToRedo);
        tasks.push_back(task);
        cout << "Task added successfully" << endl;
    }
    else{
        cout << "Invalid task!" << endl;
    }
    cout << endl;
}
// Reads user specified task’s type, deadline, description,
// and additional information if it is a specialized task
Task* ToDoListApp::readTask() {
    cout << "What type of task is this? [G: Generic, S: Shopping, E: Event, H: Homework]" << endl;
    char type = readChar();
    if (strchr("GSEH", type)){
        cout << "In how many days is this task due?" << endl;
        // calls helper function to get deadline
        unsigned int deadline = readUnsignedInt();
        cout << "How would you describe this task?" << endl;
        // calls helper function to get description
        string description = readString();
        Task* task = 0;
        if(type == 'S'){
            cout << "What items do you need to buy? "
                 << "[Type your item and press ENTER to add another item. Type DONE to complete the list.]" << endl;
            vector<string> items;
            // adds items to buy untill user enters DONE
            while(true){
                string item = readString();
                if(item == "DONE") {
                    break;
                }
                items.push_back(item);
            }
            task = new ShoppingTask(deadline, description, items);
        }
        else if(type == 'E'){
            cout << "Where is this event taking place?" << endl;
            string location = readString();
            cout << "When is this event taking place?" << endl;
            string time = readString();
            task = new EventTask(deadline, description, location, time);
        }
        else if(type == 'H'){
            cout << "What subject is this homework task for?" << endl;
            string subject = readString();
            task = new HomeworkTask(deadline, description, subject);
        }
        else{
            task = new Task(deadline, description);
        }
        return task;
    }
    else{
        return 0;
    }
}

// Handles the printing of all of the incomplete tasks in order of deadline.
void ToDoListApp::handlePrint() const{
    if(driver.outstandingTasksEmpty()){
        cout << "You have no incomplete tasks!" << endl;
    }
    else{
        driver.printOutstandingTasks();
    }
    cout << endl;
}
// Handles the printing of all of the incomplete tasks and also displays
// any specialized task information
void ToDoListApp::handleDetailed() const{
    if (driver.outstandingTasksEmpty()){
        cout << "You have no incomplete tasks!" << endl;
    }
    else{
        driver.printOutstandingTasks(true);
    }
    cout << endl;
}

// Deletes an existing incomplete task, the task number is specified by user
void ToDoListApp::handleRemove(){
    if(driver.outstandingTasksEmpty()){
        cout << "You have no incomplete tasks!" << endl;
    }
    else{
        cout << "Which task would you like to remove?" << endl;
        unsigned int position = readUnsignedInt();
        if (position >= 1 && position <= driver.outstandingTasksSize()){
            Command* command = new RemoveCommand(&driver, position - 1);
            command->execute();
            commandsToUndo.push(command);
            clear(commandsToRedo);
            cout << "Task removed successfully." << endl;
        }
        else{
            cout << "Invalid task!" << endl;
        }
    }
    cout << endl;
}

// Marks a specific incomplete task as complete, the task number is specified by user
void ToDoListApp::handleComplete() {
    if (driver.outstandingTasksEmpty()) {
        cout << "You have no incomplete tasks!" << endl;
    }
    else {
        cout << "Which task would you like to complete?" << endl;
        unsigned int position = readUnsignedInt();
        if (position >= 1 && position <= driver.outstandingTasksSize()) {
            Command* command = new CompleteCommand(&driver, position - 1);
            command->execute();
            commandsToUndo.push(command);
            clear(commandsToRedo);
            cout << "Task marked complete successfully." << endl;
        }
        else {
            cout << "Invalid task!" << endl;
        }
    }
    cout << endl;
}

// Displays all of the completed tasks
void ToDoListApp::handleCompleted() const {
    if (driver.completedTasksEmpty()) {
        cout << "You have no completed tasks!" << endl;
    }
    else {
        driver.printCompletedTasks();
    }
    cout << endl;
}

// Undoes the last ADD, REMOVE, or COMPLETE action. The user can undo actions
// multiple times, so long as there are actions left to undo. If there is
// nothing left to undo, indicates so to the user.
void ToDoListApp::handleUndo() {
    if (commandsToUndo.empty()) {
        cout << "You have no commands to undo!" << endl;
    }
    else {
        Command* command = commandsToUndo.top();
        commandsToUndo.pop();
        command->undo();
        commandsToRedo.push(command);
        cout << command->getType() << " command undone successfully." << endl;
    }
    cout << endl;
}

// Redoes an action that was previously undone.
void ToDoListApp::handleRedo() {
    if (commandsToRedo.empty()) {
        cout << "You have no commands to redo!" << endl;
    }
    else {
        Command* command = commandsToRedo.top();
        commandsToRedo.pop();
        command->redo();
        commandsToUndo.push(command);
        cout << command->getType() << " command redone successfully." << endl;
    }
    cout << endl;
}

// Saves all of the incomplete tasks to a file. The user specifies the name of the file to create.
void ToDoListApp::handleSave() const {
    if (driver.outstandingTasksEmpty()) {
        cout << "You have no outstanding tasks!\n";
    }
    else {
        cout << "Where would you like to save your outstanding tasks?" << endl;
        string filename = readString();
        ofstream fout(filename);
        if (fout.is_open()) {
            driver.dumpOutstandingTasks(fout);
            cout << "Tasks saved successfully!" << endl;
        }
        else {
            cout << "Error opening file!" << endl;
        }
    }
    cout << endl;
}

// Loads all of the tasks from a file as incomplete tasks
void ToDoListApp::handleLoad() {
    cout << "What file would you like to load incomplete tasks from?" << endl;
    string filename = readString();
    ifstream fin(filename);
    if (!fin.is_open()) {
        cout << "Error opening file!" << endl;
    }
    else {
        istringstream sin;
        string line;
        // read a file line by line
        while (getline(fin, line)) {
            sin.clear();
            sin.str(line);
            vector<string> fields;
            string field;
            while (getline(sin, field, '|')) {
                fields.push_back(field);
            }
            if (fields.size() < 3) {
                continue;
            }
            Task* task = 0;
            string type = fields[0];
            //  convert a C-string to an integer
            unsigned int deadline = atoi(fields[1].c_str());
            string description = fields[2];
            if (type == "G") {
                task = new Task(deadline, description);
            }
            else if (type == "S") {
                for (unsigned int i = 0; i < 3; i++) {
                    fields.erase(fields.begin());
                }
                task = new ShoppingTask(deadline, description, fields);
            }
            else if (type == "E") {
                string location = fields[3];
                string time = fields[4];
                task = new EventTask(deadline, description, location, time);
            }
            else if (type == "H") {
                string subject = fields[3];
                task = new HomeworkTask(deadline, description, subject);
            }
            if (task) {
                AddCommand(&driver, task).execute();
                tasks.push_back(task);
            }
        }
        cout << "Tasks loaded successfully!" << endl;
    }
    cout << endl;
}

// Handles the exit of the program
void ToDoListApp::handleExit() {
    cout << "Thank you for using To-Do List!\n" << endl;
}

//  Displays all of the available commands and their descriptions
void ToDoListApp::handleHelp() {
    cout << "ADD - Adds a new task to your To-Do list\n"
         << "PRINT - Displays your outstanding tasks succinctly\n"
         << "DETAILED - Displays your outstanding tasks with specialized task details\n"
         << "REMOVE - Removes an outstanding task\n"
         << "COMPLETE - Marks an outstanding task as complete\n"
         << "COMPLETED - Displays your completed tasks\n"
         << "UNDO - Undoes the last ADD, DELETE, or COMPLETE command\n"
         << "REDO - Redoes the last undone command\n"
         << "SAVE - Saves your outstanding tasks to a file\n"
         << "LOAD - Loads a file of outstanding tasks\n"
         << "EXIT - Exits the application immediately\n" << endl;
}

// Handles unknown commands
void ToDoListApp::handleUndefined() {
    cout << "Unknown command!\n" << endl;
}
