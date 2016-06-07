//  =============== BEGIN ASSESSMENT HEADER ================
/// @file Assignment 2/CompositeCommand.cpp
/// @author <Haripriya Vasireddy> [hvasi001@ucr.edu]
/// @date <April 30, 2016>
//  ================== END ASSESSMENT HEADER ===============
#include "OILeafCommands.h"
#include "PipeExecutable.h"
#include "OExecutable.h"
#include "CompositeCommand.h"
#include "PipeExecutable.h"
#include "LeafCommand.h"
#include "Test.h"
#include "IRedirect.h"
#include "ORedirect.h"
#include "OARedirect.h"
#include "Pipe.h"
#include "PipeCommand.h"
#include <vector>
#include <iostream>
using namespace std;


//Destructor deletes all dynamically allocated vector elements
CompositeCommand::~CompositeCommand()
{
    for(vector<Command*>::iterator it = cmdList.begin(); it != cmdList.end(); ++it)
        delete(*it);
    cmdList.clear();
}

int CompositeCommand::execute()
{
    int success = 0;
    string fname;
    //Iterate through the cmdList vector and call execute function of each
    for(unsigned i = 0; i < cmdList.size(); i++)
    {
        if(i < cmdList.size() - 1)
        {
            if(dynamic_cast<ORedirect*>(cmdList.at(i + 1)))
            {
                //cout << "In here" << endl;
                OILeafCommands *oc = new OILeafCommands();
                oc->set_executor(new OExecutable());
                LeafCommand *l = static_cast<LeafCommand*>(cmdList.at(i));
                oc->argList->resize(l->argList->size());
                copy(l->argList->begin(),l->argList->end(),oc->argList->begin());
                
                oc->fname = static_cast<LeafCommand*>(cmdList.at(i + 2))->argList->at(0);
                oc->type = 2;
                cmdList.erase(cmdList.begin() + i, cmdList.begin() + i + 3);
                cmdList.insert(cmdList.begin() + i, oc);
            }
            else if(dynamic_cast<OARedirect*>(cmdList.at(i + 1)))
            {
                //cout << "In here" << endl;
                OILeafCommands *oc = new OILeafCommands();
                oc->set_executor(new OExecutable());
                LeafCommand *l = static_cast<LeafCommand*>(cmdList.at(i));
                oc->argList->resize(l->argList->size());
                copy(l->argList->begin(),l->argList->end(),oc->argList->begin());

                oc->fname = static_cast<LeafCommand*>(cmdList.at(i + 2))->argList->at(0);
                oc->type = 3;
                cmdList.erase(cmdList.begin() + i, cmdList.begin() + i + 3);
                cmdList.insert(cmdList.begin() + i, oc);
            }
            else if(dynamic_cast<IRedirect*>(cmdList.at(i + 1)))
            {
                if(cmdList.size() > (i + 3))
                {
                    if(dynamic_cast<ORedirect*>(cmdList.at(i + 3)) || dynamic_cast<OARedirect*>(cmdList.at(i + 3)))
                    {
                        OILeafCommands *oc = new OILeafCommands();
                        oc->set_executor(new OExecutable());
                        LeafCommand *l = static_cast<LeafCommand*>(cmdList.at(i));
                        vector<char*>::iterator it = l->argList->begin(); 
                        l->argList->insert(it + l->argList->size(),static_cast<LeafCommand*>(cmdList.at(i + 2))->argList->at(0));
                        oc->argList->resize(l->argList->size());
                        copy(l->argList->begin(),l->argList->end(),oc->argList->begin());
                        
                        oc->fname = static_cast<LeafCommand*>(cmdList.at(i + 4))->argList->at(0);
                        if(dynamic_cast<ORedirect*>(cmdList.at(i + 3)))
                            oc->type = 2;
                        else
                            oc->type = 3;
                        cmdList.erase(cmdList.begin() + i, cmdList.begin() + i + 5);
                        cmdList.insert(cmdList.begin() + i, oc);
                    }
                }
                else
                {
                    OILeafCommands *oc = new OILeafCommands();
                    oc->set_executor(new OExecutable());
                    LeafCommand *l = static_cast<LeafCommand*>(cmdList.at(i));
                    oc->argList->resize(l->argList->size());
                    copy(l->argList->begin(),l->argList->end(),oc->argList->begin());
    
                    oc->fname = static_cast<LeafCommand*>(cmdList.at(i + 2))->argList->at(0);
                    oc->type = 1;
                    cmdList.erase(cmdList.begin() + i, cmdList.begin() + i + 3);
                    cmdList.insert(cmdList.begin() + i, oc);
                }
            }
        }
    }
    for(unsigned i = 0; i < cmdList.size(); i++)
    {
        if(i < cmdList.size() - 1)
        {
            if(dynamic_cast<Pipe*>(cmdList.at(i + 1)))
            {
                PipeCommand *pc = new PipeCommand();
                pc->set_executor(new PipeExecutable());
                pc->addCmd(cmdList.at(i));
                unsigned j;
                for(j = i + 2; j < cmdList.size() - 1; j++)
                {
                    if(dynamic_cast<Pipe*>(cmdList.at(j + 1)))
                    {
                        pc->addCmd(cmdList.at(j));
                        j++;
                    }
                    else
                    {
                        break;
                    }
                }
                pc->addCmd(cmdList.at(j));
                cmdList.erase(cmdList.begin() + i, cmdList.begin() + j + 1);
                cmdList.insert(cmdList.begin() + i, pc);
            }
        }
    }
    
    for(unsigned i = 0; i < cmdList.size(); i++)
    {
        success = cmdList.at(i)->execute();
        if(success >= 0)
            prevRetVal = success;
        else if(success == -5) //semi-colon
            ;
        else if(success == -6) //ands
        {
            if(prevRetVal > 0)
                i++;
        }
        else //ors
        {
            if(prevRetVal == 0)
                i++;
        }
        prevRetVal = success;
    }
        //cout << i << endl;
    if(success != -1 && !(success > 0))
        success = 0;
    return success;
}

//Add command to the vector
void CompositeCommand::addCmd(Command *c)
{
    cmdList.push_back(c);
    return;
}
