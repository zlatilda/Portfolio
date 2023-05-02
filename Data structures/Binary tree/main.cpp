#include <iostream>
#include "binary_tree.h"
using namespace std;


int main()
{
    binary_tree<int>* root = new binary_tree<int>(10);

    root->left_child = new binary_tree<int>(5);
    root->right_child = new binary_tree<int>(15);
    root->right_child->right_child = new binary_tree<int>(500);

    cout << root->get_height(root) << endl;

    return 0;
}
