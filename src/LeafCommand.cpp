//  =============== BEGIN ASSESSMENT HEADER ================
/// @file Assignment 2/LeafCommand.cpp
/// @author <Haripriya Vasireddy> [hvasi001@ucr.edu]
/// @date <April 30, 2016>
//  ================== END ASSESSMENT HEADER ===============
#include "LeafCommand.h" 
#include "Executable.h"
#include "Exit.h"
#include <iostream>
using namespace std;

//Constructor
LeafCommand::LeafCommand()
{
    argList = new vector<char*>();
}
//Destructor
LeafCommand::~LeafCommand()
{
    for(vector<char*>::iterator it = argList->begin(); it != argList->end(); ++it)
        delete(*it);
    argList->clear();
    delete argList;
}
//Call the execute method of the relevant CmdExecutor object
int LeafCommand::execute()
{
    int i;
    if(dynamic_cast<Executable*>(exec))
        i = Command::exec->execute(this);
    else if(dynamic_cast<Exit*>(exec))
        i = Command::exec->execute(this);
    //else
        //cout << "NONE" << endl;
    return i;
}
//adds arguments to the argList
void LeafCommand::addArg(char* c)
{
    this->argList->push_back(c);
}