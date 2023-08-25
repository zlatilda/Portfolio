#include <iostream>
using namespace std;

template <typename T>
struct Node
{
    T data;
    Node* l_ptr;
    Node* r_ptr;

    print()
    {
        cout << "ADDRESS" << '\t' << '\t' << "DATA" << '\t' <<  "L PTR" << '\t' << '\t' << "R PTR" << endl;
        cout << this << '\t' << data << '\t' << l_ptr << '\t' << r_ptr << endl;;
    }
};

template <class T>
class doubly_linked_list
{
    private:

        Node<T>* head;

    public:

        doubly_linked_list()
        {
            head = NULL;
        }

        void insert_front(T data)
        {
            if(head == NULL)
            {
                head = new Node<T>();
                head->data = data;
                head->l_ptr = NULL;
                head->r_ptr = NULL;
            }
            else
            {
                Node<T>* new_node = new Node<T>;
                head->l_ptr = new_node;
                new_node->data = data;
                new_node->r_ptr = head;
                new_node->l_ptr = NULL;
                head = new_node;
            }
        }

        void delete_front()
        {
            if(head == NULL)
            {
                throw "list is empty";
            }
            else
            {
                Node<T>* x = head;
                head= head->r_ptr;
                head->l_ptr = NULL;
                free(x);
            }
        }

        void delete_specific(int position)
        {
            if(head == NULL){throw "list is empty";}
            else
            {
               Node<T>* temp = head;
               for(int i = 0; i<position; i++)
               {
                   temp = temp->r_ptr;
               }
               temp->l_ptr->r_ptr = temp->r_ptr;
               temp->r_ptr->l_ptr = temp->l_ptr;
               free(temp);
            }
        }

        void print() const
        {
            if(head == NULL){throw "list is empty";}
            else
            {
                Node<T>* head_1 = new Node<T>;
                head_1 = head;
                cout << "DATA" << '\t' << "CURRENT PTR" << '\t' << "R PTR" << '\t' << '\t' << "L PTR" << endl << endl;
                while(true)
                {
                    cout << head_1->data << '\t' << head_1 << '\t' << head_1->r_ptr << '\t' << '\t' << head_1->l_ptr << endl;
                    if(head_1->r_ptr == NULL) {break;}
                    head_1 = head_1->r_ptr;
                }
            }
        }

        Node<T>* get_by_value(T value) const
        {
            Node<T>* head_1 = new Node<T>;
            head_1 = head;
            int i = 0;
            while(head_1 != NULL)
            {
                if(head_1->data == value){break;}
                head_1 = head_1->r_ptr;
                i++;
            }
            if(head_1 == NULL && i == 0){throw "list is empty";}
            else if(head_1 == NULL && i != 0){throw "no matches";}
            else
                return head_1;
        }

        int get_size() const
        {
            if(head != NULL)
            {
                Node<T>* head_1 = new Node<T>;
                head_1 = head;
                int i = 1;
                while(true)
                {
                    if(head_1->r_ptr == NULL) {break;}
                    head_1 = head_1->r_ptr;
                    i++;
                }
                return i;
            }
            return 0;
        }

        void _reverse()
        {
            if(head == NULL){throw "list is empty";}
            else
            {
                Node<T>* p_1 = new Node<T>;
                Node<T>* p_2 = new Node<T>;
                p_1 = head;
                p_2 = p_1->r_ptr;
                p_1->r_ptr = NULL;
                p_1->l_ptr = p_2;
                while(p_2 != NULL)
                {
                    p_2->l_ptr = p_2->r_ptr;
                    p_2->r_ptr = p_1;
                    p_1 = p_2;
                    p_2 = p_2->l_ptr;
                }
                head = p_1;
            }
        }

        ~doubly_linked_list()
        {
            Node<T>* x = head;

            while(x != NULL)
            {
                head= head->r_ptr;
                free(x);
                x = head;
            }
        }

};
