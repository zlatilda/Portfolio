#include <iostream>
#include "complex.h"
using namespace std;

int main()
{
    Complex a(1,2);
    Complex res = a.power(0.1);

    cout << res << endl;

    return 0;
}
