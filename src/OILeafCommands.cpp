//  =============== BEGIN ASSESSMENT HEADER ================
/// @file Assignment 2/LeafCommand.cpp
/// @author <Haripriya Vasireddy> [hvasi001@ucr.edu]
/// @date <April 30, 2016>
//  ================== END ASSESSMENT HEADER ===============
#include "OILeafCommands.h" 
#include "Executable.h"
#include "Exit.h"
#include "Test.h"
#include <iostream>
using namespace std;

//Constructor
OILeafCommands::OILeafCommands()
{
    argList = new vector<char*>();
}
//Destructor
OILeafCommands::~OILeafCommands()
{
    for(vector<char*>::iterator it = argList->begin(); it != argList->end(); ++it)
        delete(*it);
    argList->clear();
    delete argList;
}
//Call the execute method of the relevant CmdExecutor object
int OILeafCommands::execute()
{
    int i = Command::exec->execute(this);
    return i;
}
//adds arguments to the argList
void OILeafCommands::addArg(char* c)
{
    this->argList->push_back(c);
}