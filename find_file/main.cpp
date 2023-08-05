#include "search.h"
#include <exception>
#include <stdio.h>
using namespace std;

int main()
{
    try
    {
        _search();
    }
    catch(exception& ex)
    {
        printf(ex.what());
    }

    return 0;
}


