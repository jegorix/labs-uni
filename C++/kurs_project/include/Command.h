// Command.h
#ifndef COMMAND_H
#define COMMAND_H

#include "Person.h"
#include "HRContainer.h"
#include <memory>

class Command {
public:
    enum Type { ADD, DELETE, EDIT };

private:
    Type type;
    int id;
    std::unique_ptr<Person> snapshotBefore;
    std::unique_ptr<Person> snapshotAfter;

public:
    Command(Type t, int id, std::unique_ptr<Person> before, std::unique_ptr<Person> after);
    Command(const Command& other);
    Command& operator=(const Command& other);
    void undo(HRContainer&);
    void redo(HRContainer&);
};

#endif // COMMAND_H