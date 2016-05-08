//  =============== BEGIN ASSESSMENT HEADER ================
/// @file Assignment 2/Executable.cpp
/// @author <Haripriya Vasireddy> [hvasi001@ucr.edu]
/// @date <April 30, 2016>
//  ================== END ASSESSMENT HEADER ===============

#include "Executable.h"
#include "LeafCommand.h"
#include <signal.h>
#include <sys/types.h>
#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <iostream>
#include <sys/wait.h>
using namespace std;
//Destructor
Executable::~Executable(){}

int Executable::execute(Command *c)
{
    char **arg = new char*[static_cast<LeafCommand*>(c)->argList->size() + 1];
    copy(static_cast<LeafCommand*>(c)->argList->begin(), static_cast<LeafCommand*>(c)->argList->end(), arg);
    arg[static_cast<LeafCommand*>(c)->argList->size()] = '\0';
    
    pid_t pid;
    //int f_status = 0;
    int evp_status = 0;
    int status;
    
    //fork
    pid = fork(); 
    if (pid < 0) //fork failure
        ;
    else if (pid == 0) //child process
        evp_status = execvp(*arg, arg);
    else //parent waiting for the child
        waitpid(pid, &status, 0);
        
    return evp_status;
}