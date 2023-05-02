#include <iostream>
#include "binary_tree.h"
using namespace std;

int get_heigt(binary_tree<int>* root)
{
    int height = 0;
}

int main()
{
    binary_tree<int>* root = new binary_tree<int>(10);
    root->left_child = new binary_tree<int>(5);
    root->right_child = new binary_tree<int>(15);

    cout << root->data << "     " << root->left_child << "    " << root->right_child << endl;
    cout << root->left_child->data << "     " << root->left_child->left_child << "    " << root->left_child->right_child << endl;
    cout << root->right_child->data << "     " << root->right_child->left_child << "    " << root->right_child->right_child << endl;

    return 0;
}
