//  =============== BEGIN ASSESSMENT HEADER ================
/// @file Assignment 2/Test.h
/// @author <Haripriya Vasireddy> [hvasi001@ucr.edu]
/// @date <April 30, 2016>
//  ================== END ASSESSMENT HEADER ===============
#ifndef TEST_H
#define TEST_H

#include "BuiltIn.h"
class Test: public BuiltIn{
    public:
        //virtual destructor
        virtual ~Test();
        int execute(Command *c);
};
#endif