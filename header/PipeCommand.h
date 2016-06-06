//  =============== BEGIN ASSESSMENT HEADER ================
/// @file Assignment 2/CompositeCommand.h
/// @author <Haripriya Vasireddy> [hvasi001@ucr.edu]
/// @date <April 30, 2016>
//  ================== END ASSESSMENT HEADER ===============
#ifndef PIPE_COMMAND_H
#define PIPE_COMMAND_H

#include "Command.h"
#include <vector>

//Derived class of Command
class PipeCommand: public Command{
    //Destructor
    ~PipeCommand();
    public:
        int execute();
        void addCmd(Command *c);
        std::vector<Command*> cmdList;
        
    protected:
        
        int prevRetVal;
};
#endif