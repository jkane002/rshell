#include <iostream>
#include <iterator>
#include <queue>
#include "../header/Shell.h"
#include "../header/And.h"
#include "../header/Or.h"
#include "../header/Command.h"
#include "../header/Test.h"
#include "../header/Parentheses.h"

#define FOUND false
#define NOTFOUND true

using namespace std;

Shell::Shell() : success(false) {}

void Shell::read(){
	bool cont = NOTFOUND;

	cout << "CS100$ ";

	//While user input
	while(getline(cin,cmdLine)){
		//Parses anything after #
		Shell::parse(cmdLine);
		//If exit is found sets cont to false
		cont = Shell::cont();
		//Parses user input
		Shell::parse();
		//Executes input
		Shell::execute();
		if(!cont)
		    break;

		cout << "CS100$ ";
	}
}

void Shell::parse(){
	if(cmdLine.find("exit") != string::npos){
	    cmdLine.erase( cmdLine.find("exit"), cmdLine.size() - 1 );
		if(cmdLine.size() == 1){
			cmdLine.clear();
		}
	}
	//While commands are still in string
	while(cmdLine.length() != 0) {
		//If multiple commands found
		if( cmdLine.find(';') != string::npos) {
			//Store begining upto first semicolon of string into a substring
			string temp = cmdLine.substr(0, cmdLine.find(";"));
			//If substring contains test, creates Shell* of type Test and push back into queue

			if( temp.find('(') != string::npos ){
				cout << "Temp before " << temp << endl;
				Shell* newParen = new Parentheses(temp);
				commands.push(newParen);
				cout << "Temp after " << temp << endl;
			}
			//If substring contains && go create Shell* of type And and push back into queue
			if( temp.find("&&") != string::npos ){
				Shell* tempAnd = new And(temp);
				commands.push(tempAnd);
			}
			//If substring contains || create a Shell* of type Or and push back into queue
			else if( temp.find("||") != string::npos){
				Shell* tempOr = new Or(temp);
				commands.push(tempOr);
			} else if( temp.find("test") != string::npos ){
				Shell* tempTest = new Test(temp);
				commands.push(tempTest);
			}
			//If substring is just a simple command create a Shell* of type Command and push back into queue
			else{
				Shell* tempCmd = new Command(temp);
				commands.push(tempCmd);
			}
			//Erases the substring and reduces the string down
			cmdLine.erase( 0, cmdLine.find(";") + 1 );
			cmdLine.clear();
		}
		else{
			//Push back a semicolon to go into if statment so we do not rewrite same code again
			cmdLine.push_back(';');
		}
	}
}

bool Shell::cont(){
	if(cmdLine.find("exit") != string::npos)
		return FOUND;
	else
		return NOTFOUND;
}

bool Shell::getSuccess(int index){
	return false;
}
void Shell::getCommand() {
	queue<Shell*> temp(commands);
	while(!temp.empty()) {
		temp.front()->getCommand();
		temp.pop();
	}

}

void Shell::execute(){
	while(commands.size() != 0){
		// cout << "Shell execute\n";
		commands.front()->execute();
		commands.pop();
	}
}

string Shell::getNewCmd(){
	string temp = "EMPTY";
	return temp;
}

void Shell::parse(string strParse){
	//Filter out comments and exit
	if(cmdLine.find("#") != string::npos){
		cmdLine.erase( cmdLine.find("#"), cmdLine.size() - 1 );
		if(cmdLine.size() == 1)
			cmdLine.clear();
	}
}
