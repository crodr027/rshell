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
#include "RShell.h"
#include "Ands.h"
#include "Ors.h"
#include "SemiColon.h"
#include "Command.h"
#include "LeafCommand.h"
#include "CompositeCommand.h"
#include "Connector.h"
#include "Exit.h"
#include "Executable.h"

using namespace std;

//Constructor
RShell::RShell()
{
    cmd = new CompositeCommand();
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
    size_t pos1, pos2, lpos1, lpos2, comment_pos, start_pos;
    string currStr, str1, str2, lstr1;
    
    //delete the string after the '#' for comments
    start_pos = 0;
    comment_pos = cmdStr.find_first_of("#", start_pos);
    
    if(comment_pos != string::npos)
        setString(start_pos, comment_pos);
    
    if(cmdStr.size() == 0)
        return;
        
    pos1 = 0;
    pos2 = cmdStr.find_first_of(";&|", pos1);
    LeafCommand* lc;
    int set = 0;
    
    //parse the string and create Command* objects to populate the vector in CompositeCommand
    while(pos2 != string::npos)
    {
        str1 = cmdStr.substr(pos1, (pos2 - pos1));
        trim(str1);
        
        //cout << str1 <<endl;
        lc = new LeafCommand();
        
        lpos1 = 0;
        lpos2 = str1.find_first_of(" ", lpos1);
        
        while(lpos2 != string::npos)
        {
            set = 1;
            lstr1 = str1.substr(lpos1, (lpos2 - lpos1));
            
            if(lstr1 == "exit")
                lc->set_executor(new Exit());
            else
                lc->set_executor(new Executable());
                
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
            if(lstr1 == "exit")
                lc->set_executor(new Exit());
            else
                lc->set_executor(new Executable());
        }
        
        char *argC = new char[lstr1.size() + 1];
        copy(lstr1.begin(), lstr1.end(), argC);
        argC[lstr1.size()] = '\0';
        lc->addArg(argC);
        
        static_cast<CompositeCommand*>(cmd)->addCmd(lc);
        
        str2 = cmdStr.substr(pos2, 1);
        
        pos1 = pos2 + 1;
        
        if(str2 != ";")
        {
            str2 = cmdStr.substr(pos2, 2);
            pos1 += 1;
        }
        
        if(str2 == ";")
            static_cast<CompositeCommand*>(cmd)->addCmd(new SemiColon());
        else if(str2 == "&&")
            static_cast<CompositeCommand*>(cmd)->addCmd(new Ands());
        else
            static_cast<CompositeCommand*>(cmd)->addCmd(new Ors());
       
        pos2 = cmdStr.find_first_of(";&|", pos1);
        set = 0;
    }
    
    if((pos2 != string::npos) || (pos1 < cmdStr.size()))
    {
        str1 = cmdStr.substr(pos1);
        trim(str1);
        //cout << str1 <<endl;
        lc = new LeafCommand();
        lpos1 = 0;
        lpos2 = str1.find_first_of(" ", lpos1);
    
        while(lpos2 != string::npos)
        {
            set = 1;
            lstr1 = str1.substr(lpos1, (lpos2 - lpos1));
            
            if(lstr1 == "exit")
                lc->set_executor(new Exit());
            else
                lc->set_executor(new Executable());
             
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
            if(lstr1 == "exit")
                lc->set_executor(new Exit());
            else
                lc->set_executor(new Executable());
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
    //size_t len1, len2;
    
    size_t len1 = 0, len2 = 1;
    
    if(s.substr(len1, len2) == " " && s.size() > 0)
    {
        len1++;
        
        while(s.substr(len1, len2) == " " && s.size() > 0)
            len1++;
            
        s = s.substr(len1);
    }
    /*
    len1 = s.size() - 2;
    if(s.substr(len1, len2) == " " && len1 > 0)
    {
        while(s.substr(len1, len2) == " " && len1 > 0)
            len1--;
    }
    len1++;
    s = s.substr(0, len1);
    */
    
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

//Truncate the string to remove the commented part
void RShell::setString(size_t pos, size_t len)
{
    cmdStr = cmdStr.substr(pos, len);
}