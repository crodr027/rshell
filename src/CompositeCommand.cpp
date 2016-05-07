#include "CompositeCommand.h"
#include <vector>
#include <iostream>
using namespace std;

/*
CompositeCommand::CompositeCommand()
{
    prevRetVal = 0;
}
*/
int CompositeCommand::execute()
{
    int success = 0;
    for(unsigned i = 0; i < cmdList.size(); i++)
    {
        cout << "In composite command" << endl;
        //if(dynamic_cast<LeafCommand*>(cmd))
        /*
        for(unsigned j = 0; j < cmdList.at(i)->argList.size(); j++)
        {
            cout << "\n" << endl;
            cout << cmdList.at(i)->argList[j] << endl;
            
        }
        */
        success = cmdList.at(i)->execute();
        if(success < 5)
            prevRetVal = success;
        else if(success == 5)
            ;
        else if(success == 6)
        {
            if(prevRetVal == -1)
                i++;
        }
        else
        {
            if(prevRetVal != -1)
                i++;
        }
    }
    return success;
}
void CompositeCommand::addCmd(Command *c)
{
    cmdList.push_back(c);
    return;
}
