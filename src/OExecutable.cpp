//  =============== BEGIN ASSESSMENT HEADER ================
/// @file Assignment 2/Executable.cpp
/// @author <Haripriya Vasireddy> [hvasi001@ucr.edu]
/// @date <April 30, 2016>
//  ================== END ASSESSMENT HEADER ===============

#include "OExecutable.h"
#include "Executable.h"
#include "LeafCommand.h"
#include "OILeafCommands.h"
#include <signal.h>
#include <sys/types.h>
#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <iostream>
#include <sys/wait.h>
#include <cerrno>
#include <sys/stat.h>
#include <fcntl.h>
using namespace std;

OExecutable::OExecutable(){}
//Destructor
OExecutable::~OExecutable(){}

int OExecutable::execute(Command *c)
{
    //int fd[2];
    const char *filename = static_cast<OILeafCommands*>(c)->fname;
    
    //close(1);
    //dup(fd);
    //errno = 0;
    //char ch = '\0';
    int evp_status;
    char **arg = new char*[static_cast<OILeafCommands*>(c)->argList->size() + 1];
    copy(static_cast<OILeafCommands*>(c)->argList->begin(), static_cast<OILeafCommands*>(c)->argList->end(), arg);
    arg[static_cast<OILeafCommands*>(c)->argList->size()] = NULL;
    
    pid_t pid;
    int status = 0;
    
    //fork
    pid = fork(); 
    if (pid < 0) //fork failure
        ;
    else if (pid == 0) //child process
    {
    	int fd = 0;
    	if(static_cast<OILeafCommands*>(c)->type == 1)
    	{
            fd = open(filename, O_CREAT | O_RDONLY, 0777);
            dup2(fd, 0);
    	}
    	else if(static_cast<OILeafCommands*>(c)->type == 2)
    	{
            fd = open(filename, O_TRUNC | O_CREAT | O_WRONLY, 0777);
            dup2(fd, 1);
    	}
    	else if(static_cast<OILeafCommands*>(c)->type == 3)
    	{
            fd = open(filename, O_APPEND | O_CREAT | O_WRONLY, 0777);
            dup2(fd, 1);	
    	}
        
    	close(fd);
        evp_status = execvp(*arg, arg);
        if(evp_status == -1)
        {
            cout << "command not found" << endl;
            status = -1;
            _Exit(3);
        }
    	else
    		;
    }
    else //parent waiting for the child
    {
        waitpid(pid, &status, 0);
    }
        
    return status;
}