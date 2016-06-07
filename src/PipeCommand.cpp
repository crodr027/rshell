//  =============== BEGIN ASSESSMENT HEADER ================
/// @file Assignment 2/PipeCommand.cpp
/// @author <Haripriya Vasireddy> [hvasi001@ucr.edu]
/// @date <May 30, 2016>
//  ================== END ASSESSMENT HEADER ===============
#include "PipeCommand.h"
#include "LeafCommand.h"
#include "Test.h"
#include "IRedirect.h"
#include "ORedirect.h"
#include "OARedirect.h"
#include "Pipe.h"
#include <vector>
#include <iostream>
using namespace std;


//Destructor deletes all dynamically allocated vector elements
PipeCommand::~PipeCommand()
{
    for(vector<Command*>::iterator it = cmdList.begin(); it != cmdList.end(); ++it)
        delete(*it);
    cmdList.clear();
}

//Add command to the vector
void PipeCommand::addCmd(Command *c)
{
    cmdList.push_back(c);
    return;
}

//Execute
int PipeCommand::execute()
{
    int i = Command::exec->execute(this);
    return i;
}
