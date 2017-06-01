#ifndef COMMAND_H
#define COMMAND_H

#define SIZE_OF_ARRAY 100

#include "Shell.h"

class Command : public Shell{
protected:
	string cmd;
	char* command[SIZE_OF_ARRAY];
public:
	Command();
	Command(string);
	//Inherited
	void parse(string);
	void getCommand();
	void execute();
	bool getSuccess(int);
	//Unique to Class
	void exec();
};

#endif
