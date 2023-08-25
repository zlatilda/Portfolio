#include <iostream>
#include <cstdlib>
#include <bits/stdc++.h>
using namespace std;

template <class T>
class arr_stack
{
    private:

        int stack_size;
        int top;
        T* arr;

        void add_size()
        {
            stack_size += 10;
            T* temp = new T[stack_size];

            for(int i=0; i <= top; i++)
            {
                temp[i] = this->arr[i];
            }
            delete arr;

            arr = new T[stack_size];

            for(int i=0; i <= top; i++)
            {
                this->arr[i] = temp[i];
            }

            delete temp;
        }

    public:

        arr_stack(): stack_size(10), top(-1)
        {
            arr = new T[stack_size];
        }

        arr_stack(int _size): stack_size(_size), top(-1)
        {
            arr = new T[stack_size];
        }

        arr_stack & operator=(const arr_stack& obj)
        {
            if(this->stack_size != obj.stack_size)
            {
                throw "sizes are not equal";
            }
            else
            {
                top = obj.top;
                for(int i=top; i>-1; i--)
                {
                    this->arr[i] = obj.arr[i];
                }
            }
             return *this;
        }

        void push(T data)
        {
            if(top == stack_size-1)
            {
                add_size();
            }

            top += 1;
            arr[top] = data;
        }

        void pop()
        {
            if(top < 0)
            {
                throw "stack is empty";
            }
            else
            {
                arr[top] = rand() % 1000;
                top -= 1;
            }
        }

        void print_arr() const
        {
            for(int i=0; i <= top; i++)
            {
                cout << arr[i] << " ";
            }
            //cout << endl;
        }

        int get_size() const
        {
            return top+1;
        }

        int get_capacity()
        {
            return stack_size;
        }

        T get_top() const
        {
            return arr[top];
        }

        ~arr_stack()
        {
            delete arr;
        }
};

//=====================================================================================

class postfix
{
    private:
        arr_stack<char> _stack;
        string infix_expr;
        string postfix_expr;

        bool is_letter(char c)
        {
            if((c >= 'a'&& c <= 'z') || (c >= 'A' && c <= 'Z'))
            {
                return true;
            }
            else
            {
                return false;
            }
        }

        int get_priority(char c)
        {
            if (c == ')'){return 0;}
            else if( c == '+' || c == '-'){return 1;}
            else if( c == '*' || c == '/'){return 2;}
            else if( c == '^'){return 3;}
            else if(c == '('){return 4;}
        }

    public:
        postfix()
        {
            infix_expr = postfix_expr = "";
        }

        postfix(string infix, int stack_size): infix_expr(infix), _stack(stack_size)
        {
            postfix_expr = "";
        }

        string get_infix() const
        {
            return infix_expr;
        }

        string get_postfix() const
        {
            return postfix_expr;
        }

        void print_stack()
        {
            _stack.print_arr();
        }

        string infix_to_postfix()
        {
            _stack.push('(');
            string p = "";
            infix_expr.erase(remove(infix_expr.begin(), infix_expr.end(), ' '), infix_expr.end());
            cout << "CHAR SCANNED" << '\t' << "STACK" << '\t' << '\t' << "POSTFIX EXPR" << endl << endl;
            for(int i=0; i < infix_expr.length(); i++)
            {
                if(is_letter(infix_expr[i]))
                {
                    p += infix_expr[i];
                }
                if(infix_expr[i] == '(')
                {
                    _stack.push(infix_expr[i]);
                }
                if(!is_letter(infix_expr[i]) && infix_expr[i] != '(')
                {
                    if(get_priority(infix_expr[i]) > get_priority(_stack.get_top()) || _stack.get_top() == '(')
                    {
                        _stack.push(infix_expr[i]);
                    }
                    else
                    {
                        while (get_priority(infix_expr[i]) <= get_priority(_stack.get_top()) && _stack.get_top() != '(')
                        {
                            p += _stack.get_top();
                            _stack.pop();

                            if(_stack.get_size() == 0) {break;}
                        }
                        if(infix_expr[i] == ')')
                        {
                             _stack.pop();
                        }
                        else
                        {
                            _stack.push(infix_expr[i]);
                        }
                    }
                }

                if( i == infix_expr.length() - 1)
                {
                    while (get_priority(')') <= get_priority(_stack.get_top()))
                    {
                        p += _stack.get_top();
                        _stack.pop();

                        if(_stack.get_size() == 0) {break;}
                    }
                }
                p.erase(remove(p.begin(), p.end(), ')'), p.end());
                p.erase(remove(p.begin(), p.end(), '('), p.end());
                cout << infix_expr[i] << '\t' << '\t'; _stack.print_arr(); cout << '\t' << '\t' << p << endl;
            }
            cout << endl;

            postfix_expr = p;
            return postfix_expr;
        }
};
