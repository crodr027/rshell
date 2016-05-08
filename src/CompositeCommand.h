//  =============== BEGIN ASSESSMENT HEADER ================
/// @file Assignment 2/CompositeCommand.h
/// @author <Haripriya Vasireddy> [hvasi001@ucr.edu]
/// @date <April 30, 2016>
//  ================== END ASSESSMENT HEADER ===============
#ifndef COMPOSITE_COMMAND_H
#define COMPOSITE_COMMAND_H

#include "Command.h"
#include <vector>

//Derived class of Command
class CompositeCommand: public Command{
    //Destructor
    ~CompositeCommand();
    public:
        int execute();
        void addCmd(Command *c);
        
    protected:
        std::vector<Command*> cmdList;
        int prevRetVal;
};
#endif