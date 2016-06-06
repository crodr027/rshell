//  =============== BEGIN ASSESSMENT HEADER ================
/// @file Assignment 2/Ors.h
/// @author <Haripriya Vasireddy> [hvasi001@ucr.edu]
/// @date <April 30, 2016>
//  ================== END ASSESSMENT HEADER ===============
#ifndef OREDIRECT_H
#define OREDIRECT_H

#include "Connector.h"

class ORedirect: public Connector{
    public:
        int execute();
};
#endif