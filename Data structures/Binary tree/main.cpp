#include <iostream>
#include "binary_tree.h"
using namespace std;

int main()
{
    binary_tree<int>* root = new binary_tree<int>(100);
    binary_tree<int>* a = root;

    /*for(int i=3; i<5; i++)
    {
        a->add_right(i);
        a->add_left(i*10);
        a=a->right_child;
    }
    a=root->left_child;
    for(int i=1; i<=2; i++)
    {
        a->add_right(i);
        a->add_left(i*10);
        a=a->left_child;
    }*/

    cout << root->get_height(root) << endl;
    root->print(root);

    return 0;
}
