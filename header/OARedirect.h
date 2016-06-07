//  =============== BEGIN ASSESSMENT HEADER ================
/// @file Assignment 2/OARedirect.h
/// @author <Haripriya Vasireddy> [hvasi001@ucr.edu]
/// @date <May 30, 2016>
//  ================== END ASSESSMENT HEADER ===============
#ifndef OAREDIRECT_H
#define OAREDIRECT_H

#include "Connector.h"

class OARedirect: public Connector{
    public:
        int execute();
};
#endif
