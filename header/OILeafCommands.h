//  =============== BEGIN ASSESSMENT HEADER ================
/// @file Assignment 2/LeafCommand.h
/// @author <Haripriya Vasireddy> [hvasi001@ucr.edu]
/// @date <April 30, 2016>
//  ================== END ASSESSMENT HEADER ===============
#ifndef OI_LEAF_COMMANDS_H
#define OI_LEAF_COMMANDS_H

#include <vector>
#include "Command.h"
#include "CmdExecutor.h"

class OILeafCommands: public Command{
    public:
        //Constructor
        OILeafCommands();
        //Destructor
        ~OILeafCommands();
        int execute();
        void addArg(char* c);
        
    //public:
        std::vector<char*> *argList;
        const char *fname;
        int type;
};
#endif