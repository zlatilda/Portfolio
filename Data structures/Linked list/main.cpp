#include <iostream>
#include "linked_list.h"
using namespace std;

int main()
{
    linked_list<char>* a = new linked_list<char>;
    a->insert_front('a');
    a->insert_front('b');
    a->insert_front('c');
    a->insert_front('d');
    a->insert_front('e');
    cout << "================================== \n";
    a->print();
    cout << a->get_size() << endl;
    cout << endl;
    a->delete_specific(4);
    a->delete_specific(0);
    a->delete_specific(1);
    a->print();
    cout << "================================== \n";
    linked_list<char>* b = new linked_list<char>;
    b = a;
    b->print();
    cout << b->get_size() << endl;
    return 0;
}
