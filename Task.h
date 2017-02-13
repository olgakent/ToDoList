#ifndef TASK_H
#define TASK_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

/*
Task is a generic data container class that wraps information related to
all tasks — a deadline and a description. Shopping, Event, and Homework tasks
are defined in terms of generic class Task. They inherit description and deadline
methods, and new appropriate fields are added to each of the inherited classes:
list of items ( vector) to be purchased for ShoppingTask,
a location (string) and a time(string) for EventTask , and a class subject(string) for HomeworkTask.
*/
class Task {
protected:
    unsigned int deadline;
    string description;
public:
    Task(unsigned int deadline, const string& description)
        : deadline(deadline), description(description) {}
    unsigned int getDeadline() const { return deadline; }
    const string& getDescription() const { return description; }
    // displays task information
    virtual void print(bool=false) const;
    // outputs task’s data to a file. Each individual component of a task’s data is separated by a pipe character
    virtual void dump(ostream& out) const { out << "G|" << deadline << "|" << description; }
    virtual ~Task() {}
protected:
    virtual string getType() const { return ""; }
};


// ShoppingTask is a subclass of Task. It introduces a data member "items" necessary
// for recording items to purchase.
class ShoppingTask : public Task {
private:
    vector<string> items;
public:
    ShoppingTask(unsigned int deadline, const string& description, const vector<string>& items)
        : Task(deadline, description), items(items) {}
    const vector<string>& getItems() const { return items; }
    void print(bool=false) const;
    virtual void dump(ostream&) const;
protected:
    string getType() const { return "Shopping"; }
};


// EventTask is a subclass of Task. It introduces data members "location" and "time"
//  necessary for knowing the event location and time.
class EventTask : public Task {
private:
    string location;
    string time;
public:
    EventTask(unsigned int deadline, const string& description, const string& location, const string& time)
        : Task(deadline, description), location(location), time(time) {}
    const string& getLocation() const { return location; }
    const string& getTime() const { return time; }
    void print(bool=false) const;
    virtual void dump(ostream& out) const { out << "E|" << deadline << "|" << description << "|" << location << "|" << time; }
protected:
    string getType() const { return "Event"; }
};


// HomeworkTask is a subclass of Task. It introduces a new data member "subject"
// necessary for acknowledging the relevant course subject.
class HomeworkTask : public Task {
private:
    string subject;
public:
    HomeworkTask(unsigned int deadline, const string& description, const string& subject)
        : Task(deadline, description), subject(subject) {}
    const string& getSubject() const { return subject; }
    void print(bool=false) const;
    virtual void dump(ostream& out) const { out << "H|" << deadline << "|" << description << "|" << subject; }
protected:
    string getType() const { return "Homework"; }
};

#endif
