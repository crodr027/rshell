#ifndef COMPOSITE_H
#define COMPOSITE_H
#include <iostream>
using namespace std;

class Connector: public Command {
    public:
        //Whatever else the Command class has
        virtual void execute();
        int nextExecute;
};

class SemiColon: public Connector {
    public: 
        virtual void execute();
        int nextExecute;
};

class Ands: public Connector {
    public: 
        virtual void execute();
        int nextExecute;
};

class Ors: public Connector {
    public:
        virtual void execute();
        int nextExecute;
};
#endif