#ifndef COMMAND_H
#define COMMAND_H

#include <iostream>
#include "Shell.h"

class Command : public Shell {
private:
    char* cmd[];
public:
    Command();
    void parse();
    void read();
    void execute();
};

#endif
