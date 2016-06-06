//  =============== BEGIN ASSESSMENT HEADER ================
/// @file Assignment 2/RShell.cpp
/// @author <Haripriya Vasireddy> [hvasi001@ucr.edu]
/// @date <April 30, 2016>
//  ================== END ASSESSMENT HEADER ===============

#include <iostream>
#include <string>
#include <unistd.h>
#include <pwd.h>
#include <cstddef>
#include <stack>
#include "RShell.h"
#include "Ands.h"
#include "Ors.h"
#include "SemiColon.h"
#include "Command.h"
#include "LeafCommand.h"
#include "CompositeCommand.h"
#include "Connector.h"
#include "Exit.h"
#include "Test.h"
#include "Executable.h"
#include "IRedirect.h"
#include "ORedirect.h"
#include "OARedirect.h"
#include "Pipe.h"

using namespace std;

//Constructor
RShell::RShell()
{
    cmd = new CompositeCommand();
}

RShell::~RShell()
{
    delete cmd;
}

//Display the shell prompt 
void RShell::display()
{
    char *login;
    char *hostname = new char[1000]();
    string commandStr = "$ ";

    //get user login
    login = getlogin();

    //get the hostname and print the prompt
    if(!gethostname(hostname, 1000) && login)
        commandStr = string(login) + "@" + string(hostname) + commandStr;
    
    cout << commandStr;
    getline(cin, cmdStr);

    delete[] hostname;
    return;
}

//Parse the string from command line and create Command objects
void RShell::parse()
{
    createCompositeCommand(this->cmd, this->cmdStr);
}

//Creation of CompositeCommand objects called recursively 
void RShell::createCompositeCommand(Command* &cmd, string &cmdStr)
{
    size_t pos1, pos2, lpos1, lpos2, comment_pos, start_pos;
    string currStr, str1, str2, lstr1, newStr, str3;
    stack<int> stk;
    
    start_pos = 0;
    comment_pos = cmdStr.find_first_of("#", start_pos);//remove comment
    
    if(comment_pos != string::npos)
        setString(start_pos, comment_pos);
    
    if(cmdStr.size() == 0)
        return;
    
    if(!matchParens(cmdStr))
        return;
    pos1 = 0;
    pos2 = cmdStr.find_first_of(";&|(<>", pos1);
    LeafCommand* lc;
    int set = 0;
    
    // Check for parentheses in leftmost position
    if(pos2 != string::npos)
    {
        if(cmdStr.substr(pos2,1) == "(")
        {
            unsigned k;
            for(unsigned j = pos2; j < cmdStr.size(); j++)
            {
                if(cmdStr.substr(j, 1) == "(")
                    stk.push(j);
                if(cmdStr.substr(j, 1) == ")" && !stk.empty())
                {
                    k = stk.top();
                    stk.pop();
                }
                if(stk.empty())
                {
                    if(cmdStr.substr(k,1) == "(" && cmdStr.substr(k+1,1) == ")")
                        break;
                    Command *new_cmd = new CompositeCommand();
                    string new_str = cmdStr.substr(k+1, j-k-1);
                    createCompositeCommand(new_cmd, new_str);
                    static_cast<CompositeCommand*>(cmd)->addCmd(new_cmd);
                    
                    pos1 = j + 1;
                    pos2 = cmdStr.find_first_of(";&|(<>", pos1);
                    if(pos2 != string::npos)
                    {
                        str2 = cmdStr.substr(pos2, 1);
        
                        pos1 = pos2 + 1;
                        
                        if(str2 != ";" && str2 != "<")
                        {
                            if(str2 == ">" || str2 == "|" )
                            {
                                str3 = cmdStr.substr(pos2 + 1, 1);
                                if(str3 == ">" || str3 == "|")
                                {
                                    str2 = cmdStr.substr(pos2, 2);    
                                    pos1 += 1;
                                }
                            }
                            else
                            {
                                str2 = cmdStr.substr(pos2, 2);
                                pos1 += 1;
                            }
                        }
                        
                        if(str2 == ";")
                            static_cast<CompositeCommand*>(cmd)->addCmd(new SemiColon());
                        else if(str2 == "&&")
                            static_cast<CompositeCommand*>(cmd)->addCmd(new Ands());
                        else if(str2 == "||")
                            static_cast<CompositeCommand*>(cmd)->addCmd(new Ors());
                        else if(str2 == "<")
                            static_cast<CompositeCommand*>(cmd)->addCmd(new IRedirect());
                        else if(str2 == ">")
                            static_cast<CompositeCommand*>(cmd)->addCmd(new ORedirect());
                        else if(str2 == ">>")
                            static_cast<CompositeCommand*>(cmd)->addCmd(new OARedirect());
                        else if(str2 == "|")
                            static_cast<CompositeCommand*>(cmd)->addCmd(new Pipe());
                            
                        pos2 = cmdStr.find_first_of(";&|(<>", pos1);
                    }
                    
                    if((pos2 != string::npos) && (cmdStr.substr(pos2, 1) == "("))
                    {
                        j = pos2 - 1;
                        continue;
                    }
                    else
                        break;
                }
            }
        }
    }
    //parse the string and create Command* objects to populate the vector in CompositeCommand
    while(pos2 != string::npos)
    {
        str1 = cmdStr.substr(pos1, (pos2 - pos1));
        trim(str1);
        lc = new LeafCommand();
        
        lpos1 = 0;
        lpos2 = str1.find_first_of(" ", lpos1);
        
        while(lpos2 != string::npos)
        {
            lstr1 = str1.substr(lpos1, (lpos2 - lpos1));
            
            if(!set)
            {
                execSet(lc, lstr1, str1);
                set = 1;
            }
                
            char *argC = new char[lstr1.size() + 1];
            copy(lstr1.begin(), lstr1.end(), argC);
            argC[lstr1.size()] = '\0';
            lc->addArg(argC);
            lpos1 = lpos2 + 1;
            
            while(lpos1 < (str1.size() - 1) && str1.substr(lpos1, 1) == " ")
                lpos1++;
            
            lpos2 = str1.find_first_of(" ", lpos1);
        }
        
        lstr1 = str1.substr(lpos1);
        
        if(!set)
        {
            execSet(lc, lstr1, str1);
            set = 1;
        }
        
        char *argC = new char[lstr1.size() + 1];
        copy(lstr1.begin(), lstr1.end(), argC);
        argC[lstr1.size()] = '\0';
        lc->addArg(argC);
        
        static_cast<CompositeCommand*>(cmd)->addCmd(lc);
        
        str2 = cmdStr.substr(pos2, 1);
        
        pos1 = pos2 + 1;
        
        if(str2 != ";" && str2 != "<")
        {
            if(str2 == ">" || str2 == "|" )
            {
                str3 = cmdStr.substr(pos2 + 1, 1);
                if(str3 == ">" || str3 == "|")
                {
                    str2 = cmdStr.substr(pos2, 2);    
                    pos1 += 1;
                }
            }
            else
            {
                str2 = cmdStr.substr(pos2, 2);
                pos1 += 1;
            }
        }
        
        if(str2 == ";")
            static_cast<CompositeCommand*>(cmd)->addCmd(new SemiColon());
        else if(str2 == "&&")
            static_cast<CompositeCommand*>(cmd)->addCmd(new Ands());
        else if(str2 == "||")
            static_cast<CompositeCommand*>(cmd)->addCmd(new Ors());
        else if(str2 == "<")
            static_cast<CompositeCommand*>(cmd)->addCmd(new IRedirect());
        else if(str2 == ">")
            static_cast<CompositeCommand*>(cmd)->addCmd(new ORedirect());
        else if(str2 == ">>")
            static_cast<CompositeCommand*>(cmd)->addCmd(new OARedirect());
        else if(str2 == "|")
            static_cast<CompositeCommand*>(cmd)->addCmd(new Pipe());
       
        pos2 = cmdStr.find_first_of(";&|(<>", pos1);
        
        if(pos2 != string::npos)
        {
            if(cmdStr.substr(pos2,1) == "(")
            {
                unsigned k;
                for(unsigned j = pos2; j < cmdStr.size(); j++)
                {
                    if(cmdStr.substr(j, 1) == "(")
                        stk.push(j);
                    if(cmdStr.substr(j, 1) == ")" && !stk.empty())
                    {
                        k = stk.top();
                        stk.pop();
                    }
                    if(stk.empty())
                    {
                        if(cmdStr.substr(k,1) == "(" && cmdStr.substr(k+1,1) == ")")
                            break;

                        Command *new_cmd = new CompositeCommand();
                        string new_str = cmdStr.substr(k+1, j-k-1);
                        createCompositeCommand(new_cmd, new_str);
                        static_cast<CompositeCommand*>(cmd)->addCmd(new_cmd);
                        
                        pos1 = j + 1;
                        pos2 = cmdStr.find_first_of(";&|(<>", pos1);
                        if(pos2 != string::npos)
                        {
                            str2 = cmdStr.substr(pos2, 1);
            
                            pos1 = pos2 + 1;
                            
                            if(str2 != ";" && str2 != "<")
                            {
                                if(str2 == ">" || str2 == "|" )
                                {
                                    str3 = cmdStr.substr(pos2 + 1, 1);
                                    if(str3 == ">" || str3 == "|")
                                    {
                                        str2 = cmdStr.substr(pos2, 2);    
                                        pos1 += 1;
                                    }
                                }
                                else
                                {
                                    str2 = cmdStr.substr(pos2, 2);
                                    pos1 += 1;
                                }
                            }
                        
                            if(str2 == ";")
                                static_cast<CompositeCommand*>(cmd)->addCmd(new SemiColon());
                            else if(str2 == "&&")
                                static_cast<CompositeCommand*>(cmd)->addCmd(new Ands());
                            else if(str2 == "||")
                                static_cast<CompositeCommand*>(cmd)->addCmd(new Ors());
                            else if(str2 == "<")
                                static_cast<CompositeCommand*>(cmd)->addCmd(new IRedirect());
                            else if(str2 == ">")
                                static_cast<CompositeCommand*>(cmd)->addCmd(new ORedirect());
                            else if(str2 == ">>")
                                static_cast<CompositeCommand*>(cmd)->addCmd(new OARedirect());
                            else if(str2 == "|")
                                static_cast<CompositeCommand*>(cmd)->addCmd(new Pipe());
                           
                            pos2 = cmdStr.find_first_of(";&|(<>", pos1);
                        }
                        
                        if((pos2 != string::npos) && (cmdStr.substr(pos2, 1) == "("))
                        {
                            j = pos2 - 1;
                            continue;
                        }
                        else
                            break;
                    }
                }
            }
        }
        set = 0;
    }
    
    if((pos2 != string::npos) || (pos1 < cmdStr.size()))
    {
        str1 = cmdStr.substr(pos1);
        
        trim(str1);
        lc = new LeafCommand();
        lpos1 = 0;
        lpos2 = str1.find_first_of(" ", lpos1);
        
        while(lpos2 != string::npos && lpos2 < str1.size())
        {
            lstr1 = str1.substr(lpos1, (lpos2 - lpos1));
            if(!set)
            {
                execSet(lc, lstr1, str1);
                set = 1;
            }
             
            char *argC = new char[lstr1.size() + 1];
            copy(lstr1.begin(), lstr1.end(), argC);
            argC[lstr1.size()] = '\0';
            
            lc->addArg(argC);
            
            lpos1 = lpos2 + 1;
            while(lpos1 < (str1.size() - 1) && str1.substr(lpos1, 1) == " ")
                lpos1++;
            
            lpos2 = str1.find_first_of(" ", lpos1);
        }
        if(lpos1 < str1.size())
            lstr1 = str1.substr(lpos1);
            
        if(!set)
        {
            execSet(lc, lstr1, str1);
        }
        
        char *argC = new char[lstr1.size() + 1];
        copy(lstr1.begin(), lstr1.end(), argC);
        argC[lstr1.size()] = '\0';
        lc->addArg(argC);
        static_cast<CompositeCommand*>(cmd)->addCmd(lc);
    }
    return;
}

//Trims the leading and trailing spaces
void RShell::trim(string &s)
{
    size_t len1 = 0, len2 = 1;
    
    if(s.substr(len1, len2) == " " && s.size() > 0)
    {
        len1++;
        
        while(s.substr(len1, len2) == " " && s.size() > 0)
            len1++;
            
        s = s.substr(len1);
    }
    
    len1 = s.size() - 1;
    if(s.substr(len1, len2) == " ")
    {
        while(s.substr(len1, len2) == " ")
            len1--;
    }
    len1++;
    s = s.substr(0, len1);
}


//Call the execute method on Command* object which applies recursively
void RShell::execute()
{
    cmd->execute();
}

void RShell::execSet(LeafCommand* &l, string &ls, string &str)
{
    if(ls == "exit")
        l->set_executor(new Exit());
    else if(ls == "[")
    {
        if(str.substr(0,2) == "[ " && str.substr(str.size() - 2, 2) == " ]")
        {
            str = str.substr(0, str.size()-2);
            l->set_executor(new Test());
            ls = "test";
        }
        else
        {
            l->set_executor(new Executable());
            ls = "nonsense";
        }
    }
    else if(ls == "test")
        l->set_executor(new Test());
    else
        l->set_executor(new Executable());
}
//Truncate the string to remove the commented part
void RShell::setString(size_t pos, size_t len)
{
    cmdStr = cmdStr.substr(pos, len);
}

bool RShell::matchParens(string &str)
{
    stack<int> stk;
    bool match = true;
    for(unsigned j = 0; j < str.size(); j++)
    {
        if(str.substr(j, 1) == "(")
            stk.push(j);
        if(str.substr(j, 1) == ")")
        {
            if(!stk.empty())
                stk.pop();
            else
            {
                match = false;
                cout << "syntax error near unexpected token ')'" << endl;
                return match;
            }
        }
    }
        
    if(!stk.empty())
    {
       match = false;
       cout << "syntax error near unexpected token '('" << endl;
    }
    return match;
}