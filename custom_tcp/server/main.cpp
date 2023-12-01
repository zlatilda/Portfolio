#include "server.h"

int main(int argc, char** argv)
{
    server obj;
    obj.Send(argv);

    return 0;
}
