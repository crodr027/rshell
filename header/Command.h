//  =============== BEGIN ASSESSMENT HEADER ================
/// @file Assignment 2/Command.h
/// @author <Haripriya Vasireddy> [hvasi001@ucr.edu]
/// @date <April 30, 2016>
//  ================== END ASSESSMENT HEADER ===============
#ifndef COMMAND_H
#define COMMAND_H

#include "CmdExecutor.h"

class CmdExecutor;
class Command{
    public:
        //virtual Destructor
        virtual ~Command(){}
        
        void set_executor(CmdExecutor *ex)
        {
            exec = ex;
        }
        //Pure Virtual Functions 
        virtual int execute() = 0;
        
    protected:
        CmdExecutor *exec;
};

#endif