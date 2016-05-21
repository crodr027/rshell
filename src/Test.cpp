//  =============== BEGIN ASSESSMENT HEADER ================
/// @file Assignment 2/Test.cpp
/// @author <Haripriya Vasireddy> [hvasi001@ucr.edu]
/// @date <May 19, 2016>
//  ================== END ASSESSMENT HEADER ===============
#include "Test.h"
#include "LeafCommand.h"
#include <cstdlib>
#include <string>
#include <cstring>
#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

using namespace std;

//Destructor
Test::~Test(){}
//Exit the shell
int Test::execute(Command *c)
{
    int retValue;
    char **arg = new char*[static_cast<LeafCommand*>(c)->argList->size() + 1];
    copy(static_cast<LeafCommand*>(c)->argList->begin(), static_cast<LeafCommand*>(c)->argList->end(), arg);
    arg[static_cast<LeafCommand*>(c)->argList->size()] = '\0';
    
    struct stat result;
    
    //cout << "TEsting here " << endl;
    
    if(strcmp(arg[1], "-e") == 0)
    {
        if(stat(arg[2], &result) == 0)
        {
            retValue = 0;
            cout << "(True)" << endl;
        }
        else 
        {
            retValue = 25;
            cout << "(False)" << endl;
        }
    }
    else if(strcmp(arg[1], "-f") == 0)
    {
        if(stat(arg[2], &result) == 0)
        {
            if(S_ISREG(result.st_mode))
            {
                retValue = 0;
                cout << "(True)" << endl;
            }
            else
            {
                retValue = 25;
                cout << "(False)" << endl;
            }
        }
        else
        {
            retValue = 25;
            cout << "(False)" << endl;
        }
    }
    else if(strcmp(arg[1], "-d") == 0)
    {
        if(stat(arg[2], &result) == 0)
        {
            if(S_ISDIR(result.st_mode))
            {
                retValue = 0;
                cout << "(True)" << endl;
            }
            else
            {
                retValue = 25;
                cout << "(False)" << endl;
            }
        }
        else
        {
            retValue = 25;
            cout << "(False)" << endl;
        }
    }
    else
    {
        if(stat(arg[1], &result) == 0)
        {
            retValue = 0;
            cout << "(True)" << endl;
        }
        else 
        {
            retValue = 25;  
            cout << "(False)" << endl;
        }
    }
    return retValue;
}