//  =============== BEGIN ASSESSMENT HEADER ================
/// @file Assignment 2/RShell.h
/// @author <Haripriya Vasireddy> [hvasi001@ucr.edu]
/// @date <April 30, 2016>
//  ================== END ASSESSMENT HEADER ===============
#ifndef RSHELL_H
#define RSHELL_H

#include <string>
#include "Command.h"
#include "CompositeCommand.h"

class Command;
class RShell{
    public:
        /* Constructors */
        RShell();

        void display();
        void parse();
        void trim(std::string &s);
        void execute();
        
    private:
        Command *cmd;
        std::string cmdStr;
};
#endif
