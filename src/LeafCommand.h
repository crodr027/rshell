//  =============== BEGIN ASSESSMENT HEADER ================
/// @file Assignment 2/LeafCommand.h
/// @author <Haripriya Vasireddy> [hvasi001@ucr.edu]
/// @date <April 30, 2016>
//  ================== END ASSESSMENT HEADER ===============
#ifndef LEAF_COMMAND_H
#define LEAF_COMMAND_H

#include <vector>
#include "Command.h"
#include "CmdExecutor.h"

class LeafCommand: public Command{
    public:
        /* Constructors */
        LeafCommand();
        //void set_executor(CmdExecutor *ex);
        /* Pure Virtual Functions */
        int execute();
        
        void addArg(char* c);
        
    //public:
        std::vector<char*> *argList;
};
#endif