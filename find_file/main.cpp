#include "search.h"
#include <exception>
#include <stdio.h>
#include <cstdlib>
using namespace std;

int main()
{
    try
    {
        _search();
        system("PAUSE");
    }
    catch(exception& ex)
    {
        printf(ex.what());
    }

    return 0;
}


