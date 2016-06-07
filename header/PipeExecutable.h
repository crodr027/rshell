//  =============== BEGIN ASSESSMENT HEADER ================
/// @file Assignment 2/PipeExecutable.h
/// @author <Haripriya Vasireddy> [hvasi001@ucr.edu]
/// @date <May 30, 2016>
//  ================== END ASSESSMENT HEADER ===============
#ifndef PIPE_EXECUTABLE_H
#define PIPE_EXECUTABLE_H

#include "CmdExecutor.h"

class PipeExecutable: public CmdExecutor{
    public:
        //const char* fname;
        PipeExecutable();
        //Virtual destructor
        virtual ~PipeExecutable();
        int execute(Command *c);
};
#endif
