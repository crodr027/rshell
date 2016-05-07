#include "Exit.h"
#include "LeafCommand.h"
#include <cstdlib>
#include <string>
using namespace std;

int Exit::execute(Command *c)
{
    //char *chr = static_cast<LeafCommand*>(c)->argList[0];
    //string str(chr);
    //string str = static_cast<LeafCommand*>(c)->argList[0].c_str();
    //std::cout << static_cast<LeafCommand*>(c)->argList[0];
    //if(str == "exit")
    (void)c;
    exit(0);
    return 0;
}
