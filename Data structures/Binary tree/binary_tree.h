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

        int get_height(binary_tree* root)
        {
            if (!root)
                return 0;
            else
            {
                int left_height = get_height(root->left_child);
                int right_height = get_height(root->right_child);
                if (left_height >= right_height)
                    return left_height + 1;
                else
                    return right_height + 1;
            }
        }

        void print(binary_tree* root)
        {
            if (root)
            {
                cout << root->data << " ";
                print(root->left_child);
                print(root->right_child);
            }
        }

        void add_left(T l_data=NULL)
        {
            left_child = new binary_tree(l_data);
        }

        void add_right(T r_data=NULL)
        {
            right_child = new binary_tree(r_data);
        }
};
