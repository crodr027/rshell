#include "RShell.h"
#include <unistd.h>
using namespace std;
int main()
{
    RShell* rs = new RShell();
    rs->display();
    rs->parse();

    rs->execute();
    return 0;
}
