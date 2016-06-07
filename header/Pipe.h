//  =============== BEGIN ASSESSMENT HEADER ================
/// @file Assignment 2/Pipe.h
/// @author <Haripriya Vasireddy> [hvasi001@ucr.edu]
/// @date <May 30, 2016>
//  ================== END ASSESSMENT HEADER ===============
#ifndef PIPE_H
#define PIPE_H

#include "Connector.h"

class Pipe: public Connector{
    public:
        int execute();
};
#endif
