//  =============== BEGIN ASSESSMENT HEADER ================
/// @file Assignment 2/OExecutable.h
/// @author <Haripriya Vasireddy> [hvasi001@ucr.edu]
/// @date <May 30, 2016>
//  ================== END ASSESSMENT HEADER ===============
#ifndef O_EXECUTABLE_H
#define O_EXECUTABLE_H

#include "CmdExecutor.h"

class OExecutable: public CmdExecutor{
    public:
        const char* fname;
        OExecutable();
        //Virtual destructor
        virtual ~OExecutable();
        int execute(Command *c);
};
#endif
