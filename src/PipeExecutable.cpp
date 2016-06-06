//  =============== BEGIN ASSESSMENT HEADER ================
/// @file Assignment 2/Executable.cpp
/// @author <Haripriya Vasireddy> [hvasi001@ucr.edu]
/// @date <April 30, 2016>
//  ================== END ASSESSMENT HEADER ===============
#include "PipeExecutable.h"
#include "Executable.h"
#include "LeafCommand.h"
#include "PipeCommand.h"
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

PipeExecutable::PipeExecutable(){}
//Destructor
PipeExecutable::~PipeExecutable(){}

int PipeExecutable::execute(Command *c)
{
    //int i;
    pid_t pid;
    int fd [2];
    int in_fd = 0;
    char **arg;
    unsigned i = 0;
    int status = 0;
    bool oi_command;
    const char *filename;
    int evp_status;
    
    int save_stdin = dup(0);
    int save_stdout = dup(1);
    while(i < (static_cast<PipeCommand*>(c)->cmdList.size() - 1))
    {
        Command *nc = static_cast<PipeCommand*>(c)->cmdList.at(i);
        
        if(dynamic_cast<OILeafCommands*>(nc))
        {
            arg = new char*[static_cast<OILeafCommands*>(nc)->argList->size() + 1];
            copy(static_cast<OILeafCommands*>(nc)->argList->begin(), static_cast<OILeafCommands*>(nc)->argList->end(), arg);
            arg[static_cast<OILeafCommands*>(nc)->argList->size()] = '\0';
            oi_command = true;
            filename = static_cast<OILeafCommands*>(nc)->fname;
        }
        else
        {
            arg = new char*[static_cast<LeafCommand*>(nc)->argList->size() + 1];
            copy(static_cast<LeafCommand*>(nc)->argList->begin(), static_cast<LeafCommand*>(nc)->argList->end(), arg);
            arg[static_cast<LeafCommand*>(nc)->argList->size()] = '\0';
            oi_command = false;
        }
        pipe (fd);

        pid = fork();
        if(pid == 0)
        {
            //close(1);
            if(oi_command)
            {
                if(static_cast<OILeafCommands*>(nc)->type == 1)
            	{
                    in_fd = open(filename, O_CREAT | O_RDONLY, 0777);
                    dup2(in_fd, 0);
                    close(in_fd);
                    if(fd[1] != 0)
                    {
                        dup2(fd[1], 1);
                        close(fd[1]);
                    }
            	}
            	else if(static_cast<OILeafCommands*>(nc)->type == 2)
            	{
                    fd[1] = open(filename, O_TRUNC | O_CREAT | O_WRONLY, 0777);
                    dup2(fd[1], 1);
                    close (fd[1]);
                    i = static_cast<PipeCommand*>(c)->cmdList.size();
            	}
            	else if(static_cast<OILeafCommands*>(nc)->type == 3)
            	{
                    fd[1] = open(filename, O_APPEND | O_CREAT | O_WRONLY, 0777);
                    dup2(fd[1], 1);	
                    close (fd[1]);
                    i = static_cast<PipeCommand*>(c)->cmdList.size();
            	}
            }
            else 
            {
                if(in_fd != 0)
                {
                    dup2(in_fd, 0);
                    close(in_fd);
                }
                if(fd[1] != 0)
                {
                    dup2(fd[1], 1);
                    close(fd[1]);
                }
            }
            
            evp_status = execvp(*arg, arg);
            cout << evp_status << endl;
        }
        else
        {
            waitpid(pid, &status, 0);   
            close (fd [1]);
            close (in_fd);
            in_fd = fd [0];
        }
        
        i++;
    }
    if(i <static_cast<PipeCommand*>(c)->cmdList.size())
    {
        Command *nc = static_cast<PipeCommand*>(c)->cmdList.at(i);
        //int evp_status;
        if(dynamic_cast<OILeafCommands*>(nc))
        {
            arg = new char*[static_cast<OILeafCommands*>(nc)->argList->size() + 1];
            copy(static_cast<OILeafCommands*>(nc)->argList->begin(), static_cast<OILeafCommands*>(nc)->argList->end(), arg);
            arg[static_cast<OILeafCommands*>(nc)->argList->size()] = '\0';
            oi_command = true;
            filename = static_cast<OILeafCommands*>(nc)->fname;
        }
        else
        {
            arg = new char*[static_cast<LeafCommand*>(nc)->argList->size() + 1];
            copy(static_cast<LeafCommand*>(nc)->argList->begin(), static_cast<LeafCommand*>(nc)->argList->end(), arg);
            arg[static_cast<LeafCommand*>(nc)->argList->size()] = '\0';
            oi_command = false;
        }
        
        pipe(fd);
        pid = fork();
        if(pid == 0)
        {
            if(in_fd != 0)
            {
                dup2 (in_fd, 0);
                close(in_fd);
            }
            if(oi_command)
            {
                if(static_cast<OILeafCommands*>(nc)->type == 2)
            	{
                    fd[1] = open(filename, O_TRUNC | O_CREAT | O_WRONLY, 0777);
                    dup2(fd[1], 1);
                    close(fd[1]);
            	}
            	else if(static_cast<OILeafCommands*>(nc)->type == 3)
            	{
                    fd[1] = open(filename, O_APPEND | O_CREAT | O_WRONLY, 0777);
                    dup2(fd[1], 1);
                    close(fd[1]);
            	}
            }
            //cout << "Before final execute" << endl;
            evp_status = execvp(*arg, arg);
            cout << evp_status << endl;
        }
        else
        {
            waitpid(pid, &status, 0);   
            close (fd [1]);
            close (fd [0]);
            close(in_fd);
            //cout << "Ending Parent" << endl;
            dup2(save_stdin, 0);
            dup2(save_stdout, 1);
        }
    }
    return status;
}

