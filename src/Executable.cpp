//  =============== BEGIN ASSESSMENT HEADER ================
/// @file Assignment 2/Executable.h
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

int Executable::execute(Command *c)
{
    cout << "In Executable" << endl;
    //int size = static_cast<LeafCommand*>(c)->argList.size();
    //char **arg = &(static_cast<LeafCommand*>(c)->argList[0]);
    
    char **arg = new char*[static_cast<LeafCommand*>(c)->argList->size()];
    copy(static_cast<LeafCommand*>(c)->argList->begin(), static_cast<LeafCommand*>(c)->argList->end(), arg);
    //arg[static_cast<LeafCommand*>(c)->argList->size()] = '\0';
    
    cout << "\n" << arg[0] ;
    cout << "\t" << arg[1] <<endl;
    pid_t pid;
    int f_status = 0;
    int evp_status = 0;
    int status;
    
    pid = fork(); 
    if (pid < 0) 
    {   
        f_status = 1;
        cout << f_status << endl;
    }
    else if (pid == 0) 
    {   
        cout << "\nIn child process\n" << endl;
        evp_status = execvp(*arg, arg);
        cout << "Child process" << evp_status << endl;
    }
    else 
    {                                  
        /* for the parent:      */
        waitpid(pid, &status, 0);
    }
    return evp_status;
}