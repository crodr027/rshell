//  =============== BEGIN ASSESSMENT HEADER ================
/// @file Assignment 2/Ors.h
/// @author <Haripriya Vasireddy> [hvasi001@ucr.edu]
/// @date <April 30, 2016>
//  ================== END ASSESSMENT HEADER ===============
#ifndef ORS_H
#define ORS_H

#include "Connector.h"

class Ors: public Connector{
    public:
        /* Constructors */
        
        /* Pure Virtual Functions */
        int execute();
};
#endif