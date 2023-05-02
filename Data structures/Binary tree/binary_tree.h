#include <iostream>
using namespace std;

template <class T>
class binary_tree
{
    public:
        T data;
        binary_tree* left_child;
        binary_tree* right_child;

        binary_tree(T data)
        {
            this->data = data;
            left_child = NULL;
            right_child = NULL;
        }
};
