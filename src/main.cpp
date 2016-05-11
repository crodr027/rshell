//  =============== BEGIN ASSESSMENT HEADER ================
/// @file Assignment 2/main.cpp
/// @author <Haripriya Vasireddy> [hvasi001@ucr.edu]
/// @date <April 30, 2016>
//  ================== END ASSESSMENT HEADER ===============
#include "RShell.h"
#include <unistd.h>
using namespace std;

//Launch the program by creating RShell object and calling its methods
int main()
{
    while(1)
    {
        RShell rs;
        rs.display();
        rs.parse();

        rs.execute();
    }
    
    return 0;
}
