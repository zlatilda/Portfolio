#include <iostream>
using namespace std;

template <typename T>
struct node
{
    T data;
    node* next_ptr;
};

template <class T>
class linked_list
{
    private:
        node<T>* head;

    public:
        linked_list()
        {
            head = NULL;
        }

        void insert_front(T data)
        {
            node<T>* new_node = new node<T>;
            new_node->data = data;
            new_node->next_ptr = head;
            head = new_node;
        }

        void position_insert(T data, int position)
        {
            node<T>* temp = new node<T>;
            temp = head;
            int j = 1;
            while(j<position)
            {
                temp = temp->next_ptr;
                j++;
            }
            node<T>* new_node = new node<T>;
            new_node->data = data;
            new_node->next_ptr = temp->next_ptr;
            temp->next_ptr = new_node;
        }

        void print() const
        {
            node<T>* head_1 = new node<T>;
            head_1 = head;
            cout << "DATA" << '\t' << "CURRENT PTR" << '\t' << "NEXT PTR" << endl << endl;
            while(true)
            {
                cout << head_1->data << '\t' << head_1 << '\t' << head_1->next_ptr << endl;
                if(head_1->next_ptr == NULL) {break;}
                head_1 = head_1->next_ptr;
            }
        }

        void _reverse()
        {
            node<T>* p_1 = new node<T>;
            node<T>* p_2 = new node<T>;
            node<T>* p_3 = new node<T>;

            p_1 = head;
            p_2 = p_1->next_ptr;
            p_3 = p_2->next_ptr;
            p_1->next_ptr = NULL;
            p_2->next_ptr = p_1;
            while(p_3 != NULL)
            {
                p_1 = p_2;
                p_2 = p_3;
                p_3 = p_3->next_ptr;
                p_2->next_ptr = p_1;
            }
            head = p_2;
        }

        int get_size() const
        {
            if(head != NULL)
            {
                node<T>* head_1 = new node<T>;
                head_1 = head;
                int i = 1;
                while(true)
                {
                    if(head_1->next_ptr == NULL) {break;}
                    head_1 = head_1->next_ptr;
                    i++;
                }
                return i;
            }
            return 0;
        }

        T get_by_pos(int position) const
        {
            node<T>* head_1 = new node<T>;
            head_1 = head;
            for(int i=0; i<position; i++)
            {
                head_1 = head_1->next_ptr;
                if(head_1->next_ptr == NULL){break;}
            }
            return head_1->data;
        }

        int get_by_value(T value) const
        {
            node<T>* head_1 = new node<T>;
            head_1 = head;
            int i = 0;
            while(head_1 != NULL)
            {
                if(head_1->data == value){break;}
                head_1 = head_1->next_ptr;
                i++;
            }
            if(head_1 == NULL){return NULL;}
            else{return i;}
        }

        void delete_front()
        {
            node<T>* x = head;
            head= head->next_ptr;
            free(x);
        }

        void delete_specific(int position)
        {
            node<T>* prev = new node<T>;
            node<T>* curr = new node<T>;
            node<T>* next = new node<T>;
            prev, curr, next = head;
            int i = 0;

            if(head->next_ptr == NULL || position == 0){delete_front();}
            if(position == 1)
            {
                curr = head->next_ptr;
                next = head->next_ptr->next_ptr;
                free(curr);
                head->next_ptr = next;
            }
            if(position > 1)
            {
                curr = head->next_ptr;
                next = head->next_ptr->next_ptr;
                int i=1;
                while(i<position)
                {
                    prev = curr;
                    curr = next;
                    next = next->next_ptr;
                    i++;
                }
                free(curr);
                prev->next_ptr = next;
            }
        }

        ~linked_list()
        {
            node<T>* x = head;

            while(x != NULL)
            {
                head= head->next_ptr;
                free(x);
                x = head;
            }
        }
};
