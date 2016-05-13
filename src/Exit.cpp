//  =============== BEGIN ASSESSMENT HEADER ================
/// @file Assignment 2/Exit.cpp
/// @author <Haripriya Vasireddy> [hvasi001@ucr.edu]
/// @date <April 30, 2016>
//  ================== END ASSESSMENT HEADER ===============
#include "Exit.h"
#include "LeafCommand.h"
#include <cstdlib>
#include <string>
using namespace std;

//Destructor
Exit::~Exit(){}
//Exit the shell
int Exit::execute(Command *c)
{
    (void)c;
    exit(0);
    return 0;
}