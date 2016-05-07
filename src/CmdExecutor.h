//  =============== BEGIN ASSESSMENT HEADER ================
/// @file Assignment 2/CmdExecutor.h
/// @author <Haripriya Vasireddy> [hvasi001@ucr.edu]
/// @date <April 25, 2016>
//  ================== END ASSESSMENT HEADER ===============
#ifndef CMD_EXECUTOR_H
#define CMD_EXECUTOR_H

#include "Command.h"

class Command;
class CmdExecutor{
    public:
        /* Constructors */
        //Sort();
        
        /* Pure Virtual Functions */
        virtual int execute(Command *c) = 0;
};
#endif