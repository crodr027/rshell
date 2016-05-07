//  =============== BEGIN ASSESSMENT HEADER ================
/// @file Assignment 2/Executable.h
/// @author <Haripriya Vasireddy> [hvasi001@ucr.edu]
/// @date <April 30, 2016>
//  ================== END ASSESSMENT HEADER ===============
#ifndef EXECUTABLE_H
#define EXECUTABLE_H

#include "CmdExecutor.h"

class Executable: public CmdExecutor{
    public:
        /* Constructors */
        
        int execute(Command *c);
};
#endif