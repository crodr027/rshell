//  =============== BEGIN ASSESSMENT HEADER ================
/// @file Assignment 2/Exit.cpp
/// @author <Haripriya Vasireddy> [hvasi001@ucr.edu]
/// @date <April 30, 2016>
//  ================== END ASSESSMENT HEADER ===============
#include "Exit.h"
#include "LeafCommand.h"
#include <cstdlib>
#include <string>
#include <iostream>
#include <exception>
using namespace std;

//Destructor
Exit::~Exit(){}
//Exit the shell
int Exit::execute(Command *c)
{
    //cout << "in exit" << endl;
    (void)c;
    //exit(0);
    throw std::exception();
    return 0;
}