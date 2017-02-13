#ifndef COMMAND_H
#define COMMAND_H

#include "Task.h"
#include "ToDoListDriver.h"

#include <string>

using namespace std;

/*
Command is a data container class that tracks a single (reversible)
command invoked by the user—i.e., ADD, COMPLETE, and REMOVE.
It is meant to aid in the process of undoing and redoing actions.

Command contains a  specific task affected by the invoked command.

Each of the commands: AddCommand, RemoveCommand, CompleteCommand is a separate
object defined in terms of generic class, it knows how to execute/undo/redo itself).
*/
class Command {
protected:
    ToDoListDriver* driver;
public:
    Command(ToDoListDriver* driver): driver(driver) {}
    virtual void execute() = 0;
    virtual void undo() = 0;
    virtual void redo() = 0;
    virtual string getType() const = 0;
    virtual ~Command() {}
};

class AddCommand : public Command {
private:
    Task* task;
public:
    AddCommand(ToDoListDriver* driver, Task* task)
        : Command(driver), task(task) {}
    void execute() { driver->addOutstandingTask(task); }
    void undo() { driver->removeOutstandingTask(task); }
    void redo() { driver->addOutstandingTask(task); }
    string getType() const { return "ADD"; }
};

class RemoveCommand : public Command {
private:
    unsigned int position;
    Task* task;
public:
    RemoveCommand(ToDoListDriver* driver, unsigned int position)
        : Command(driver), position(position), task(0) {}
    void execute() { task = driver->removeOutstandingTask(position); }
    void undo() { driver->addOutstandingTask(task); }
    void redo() { driver->removeOutstandingTask(task); }
    string getType() const { return "REMOVE"; }
};

class CompleteCommand : public Command {
private:
    unsigned int position;
    Task* task;
public:
    CompleteCommand(ToDoListDriver*  driver, unsigned int position)
        : Command(driver), position(position), task(0) {}
    void execute() { task = driver->removeOutstandingTask(position);
                     driver->addCompletedTask(task); }
    void undo() { driver->removeCompletedTask(task); driver->addOutstandingTask(task); }
    void redo() { driver->removeOutstandingTask(task); driver->addCompletedTask(task);}
    string getType() const { return "COMPLETE"; }
};

#endif
