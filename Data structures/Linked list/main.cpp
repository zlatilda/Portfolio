#include <iostream>
#include "linked_list.h"
#include "doubly_linked_list.h"
using namespace std;

int main()
{
    try
    {
        doubly_linked_list<int>* a = new doubly_linked_list<int>();
        a->insert_front(1);
        a->insert_front(2);
        a->insert_front(3);
        a->insert_front(4);
        a->print();
        cout << endl;
        a->_reverse();
        a->print();
    }
    catch(const char* ch)
    {
        cerr<<ch;
    }
    return 0;
}
