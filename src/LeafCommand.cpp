//  =============== BEGIN ASSESSMENT HEADER ================
/// @file Assignment 2/LeafCommand.h
/// @author <Haripriya Vasireddy> [hvasi001@ucr.edu]
/// @date <April 30, 2016>
//  ================== END ASSESSMENT HEADER ===============
#include "LeafCommand.h" 
#include "Executable.h"
#include "Exit.h"
#include <iostream>
using namespace std;

LeafCommand::LeafCommand()
{
    argList = new vector<char*>;
}
int LeafCommand::execute()
{
    cout << "In LeafCommand" << endl;
    int i;
    if(dynamic_cast<Executable*>(exec))
        i = Command::exec->execute(this);
    else if(dynamic_cast<Exit*>(exec))
        i = Command::exec->execute(this);
    else
        cout << "NONE" << endl;
    cout << "In LeafCommand" << endl;
    return i;
}

void LeafCommand::addArg(char* c)
{
    cout << "pushing: " << c << endl;
    argList->push_back(c);
}