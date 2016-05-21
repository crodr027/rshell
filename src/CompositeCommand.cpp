//  =============== BEGIN ASSESSMENT HEADER ================
/// @file Assignment 2/CompositeCommand.cpp
/// @author <Haripriya Vasireddy> [hvasi001@ucr.edu]
/// @date <April 30, 2016>
//  ================== END ASSESSMENT HEADER ===============
#include "CompositeCommand.h"
#include "Test.h"
#include <vector>
#include <iostream>
using namespace std;


//Destructor deletes all dynamically allocated vector elements
CompositeCommand::~CompositeCommand()
{
    for(vector<Command*>::iterator it = cmdList.begin(); it != cmdList.end(); ++it)
        delete(*it);
    cmdList.clear();
}

int CompositeCommand::execute()
{
    int success = 0;
    //Iterate through the cmdList vector and call execute function of each
    for(unsigned i = 0; i < cmdList.size(); i++)
    {
        //cout << "In Composite" << endl;
        //cout << dynamic_cast<Test*>(cmdList.at(i)) << endl;
        success = cmdList.at(i)->execute();
        if(success >= 0)
            prevRetVal = success;
        else if(success == -5) //semi-colon
            ;
        else if(success == -6) //ands
        {
            if(prevRetVal > 0)
                i++;
        }
        else //ors
        {
            if(prevRetVal == 0)
                i++;
        }
    }
    return success;
}

//Add command to the vector
void CompositeCommand::addCmd(Command *c)
{
    cmdList.push_back(c);
    return;
}
