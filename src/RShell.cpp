//  =============== BEGIN ASSESSMENT HEADER ================
/// @file Assignment 2/RShell.p
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

RShell::RShell()
{
    cmd = new CompositeCommand();
}

void RShell::display()
{
    char *login;
    char *hostname = new char[1000]();
    string commandStr = "$";

    //login = getuid();
    login = getlogin();

    if(!gethostname(hostname, 1000) && login)
        commandStr = string(login) + "@" + string(hostname) + commandStr;

    cout << commandStr;
    getline(cin, cmdStr);

    delete[] hostname;
    return;
}
void RShell::parse()
{
    size_t pos1, pos2, lpos1, lpos2;
    string currStr, str1, str2, lstr1;
    pos1 = 0;
    pos2 = cmdStr.find_first_of(";&|", pos1);
    LeafCommand* lc;
    int set = 0;
    
    while(pos2 != string::npos)
    {
        str1 = cmdStr.substr(pos1, (pos2 - pos1));
        //cout << "\"" << str1 << "\"" << endl;
        trim(str1);
        //cout << str1 << endl;
        
        lc = new LeafCommand();
        
        lpos1 = 0;
        lpos2 = str1.find_first_of(" ", lpos1);
        cout << lpos2 <<endl;
        //lstr1 = str1.substr(lpos1, (lpos2 - lpos1));
        //cout << lstr1 << endl;
        //lpos1 = lpos2 + 1;
        //lpos2 = str1.find_first_of(" ", lpos1);
        while(lpos2 != string::npos)
        {
            set = 1;
            lstr1 = str1.substr(lpos1, (lpos2 - lpos1));
            if(lstr1 == "exit")
                lc->set_executor(new Exit());
            else
                lc->set_executor(new Executable());
            cout << "   arg - " << lstr1 << endl;
            lc->addArg(const_cast<char*>(lstr1.c_str()));
            lpos1 = lpos2 + 1;
            lpos2 = str1.find_first_of(" ", lpos1);
        }
        lstr1 = str1.substr(lpos1);
        //cout << lstr1 << endl;
        if(!set)
        {
            if(lstr1 == "exit")
                lc->set_executor(new Exit());
            else
            {
                //cout << "here" << endl;
                lc->set_executor(new Executable());
            }
        }
        
        cout << "   arg - " << lstr1 << endl;
        lc->addArg(const_cast<char*>(lstr1.c_str()));
        lc->addArg('\0');
        static_cast<CompositeCommand*>(cmd)->addCmd(lc);
        
        str2 = cmdStr.substr(pos2, 1);
        pos1 = pos2 + 1;
        
        if(str2 != ";")
        {
            str2 = cmdStr.substr(pos2, 2);
            pos1 += 1;
        }
        
        cout << str2 << endl;
        Connector *con;
        if(str2 == ";")
            con = new SemiColon();
        else if(str2 == "&&")
            con = new Ands();
        else 
            con = new Ors();
       
        static_cast<CompositeCommand*>(cmd)->addCmd(con);     
        //cout << "pos1: " << pos1 << ", pos2: " << pos2 << endl;
        pos2 = cmdStr.find_first_of(";&|", pos1);
        //cout << pos2 << endl;
        set = 0;
    }
    str1 = cmdStr.substr(pos1);
    //cout << str1 << endl;
    trim(str1);
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
        cout << "   arg - " << lstr1 << endl;
        lc->addArg(const_cast<char*>(lstr1.c_str()));
        lpos1 = lpos2 + 1;
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
    
    cout << "   arg - " << lstr1 << endl;
    lc->addArg(const_cast<char*>(lstr1.c_str()));
    lc->addArg('\0');
    static_cast<CompositeCommand*>(cmd)->addCmd(lc);
    
    return;
}

void RShell::trim(string &s)
{
    if(s.substr(0,1) == " ")
        {
            //cout << "here1" << endl;
            s = s.substr(1);
        }
        //cout << "\"" << str1 << "\"" << endl;
        //cout << str1.find_last_of(" ", 0) << "size: " << str1.size() - 1 << endl;
        if(s.substr(s.size() - 1) == " ")
        {
            //cout << "here2" << endl;
            s = s.substr(0, (s.size() - 1));
        }
}
void RShell::execute()
{
    cmd->execute();
}
