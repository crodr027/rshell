//  =============== BEGIN ASSESSMENT HEADER ================
/// @file Assignment 2/BuiltIn.h
/// @author <Haripriya Vasireddy> [hvasi001@ucr.edu]
/// @date <April 30, 2016>
//  ================== END ASSESSMENT HEADER ===============
#ifndef BUILTIN_H
#define BUILTIN_H

#include "CmdExecutor.h"
#include "Command.h"

class Command;
class BuiltIn: public CmdExecutor{
    public:
        /* Constructors */
        
        virtual int execute(Command *c) = 0;
};
#endif