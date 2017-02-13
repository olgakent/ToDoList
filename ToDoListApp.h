#ifndef TO_DO_LIST_APP_H
#define TO_DO_LIST_APP_H

#include "Command.h"
#include "Task.h"
#include "ToDoListDriver.h"

#include <stack>
#include <string>
#include <vector>

using namespace std;

/*
ToDoListApp is the main entry point into the application. It exposes one public
function, run(), that executes the main program loop ad infinitum. It serves as
the main interaction point with the user,controlling input and output in the program.

ToDoListApp contains an instance of ToDoListDriver that gets manipulated based
on the user's input commands. This class keeps track of commands in order to
accomplish undo and redo actions. The most natural and convenient data structure
used is a stack of commands.

*/


class ToDoListApp{
private:
    ToDoListDriver driver;
    vector<Task*> tasks;
    stack<Command*> commandsToUndo;
    stack<Command*> commandsToRedo;
public:
    enum AppCommand {ADD, PRINT, DETAILED, REMOVE, COMPLETE, COMPLETED, UNDO, REDO, SAVE, LOAD, EXIT, HELP, UNDEFINED};
    void run();
    ~ToDoListApp();
private:
    static unsigned int readUnsignedInt();
    static char readChar();
    static string readString();
    static AppCommand readAppCommand();
    Task* readTask();
    static void clear(stack<Command*>& commands);
    void handleAdd();
    void handlePrint() const;
    void handleDetailed() const;
    void handleRemove();
    void handleComplete();
    void handleCompleted() const;
    void handleUndo();
    void handleRedo();
    void handleSave() const;
    void handleLoad();
    static void handleExit();
    static void handleHelp();
    static void handleUndefined();
};

#endif
