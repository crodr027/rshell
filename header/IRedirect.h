//  =============== BEGIN ASSESSMENT HEADER ================
/// @file Assignment 2/Ors.h
/// @author <Haripriya Vasireddy> [hvasi001@ucr.edu]
/// @date <April 30, 2016>
//  ================== END ASSESSMENT HEADER ===============
#ifndef IREDIRECT_H
#define IREDIRECT_H

#include "Connector.h"

class IRedirect: public Connector{
    public:
        int execute();
};
#endif