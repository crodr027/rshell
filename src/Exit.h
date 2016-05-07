//  =============== BEGIN ASSESSMENT HEADER ================
/// @file Assignment 2/Exit.h
/// @author <Haripriya Vasireddy> [hvasi001@ucr.edu]
/// @date <April 30, 2016>
//  ================== END ASSESSMENT HEADER ===============
#ifndef EXIT_H
#define EXIT_H

#include "BuiltIn.h"
class Exit: public BuiltIn{
    public:
        /* Constructors */
        
        int execute(Command *c);
};
#endif