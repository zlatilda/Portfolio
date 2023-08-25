#include <iostream>
#include <typeinfo>
#include <vector>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
#include <sstream>
#include "arr_stack.h"
using namespace std;

void string_to_ints(arr_stack<int>& obj, string str)
{
    vector<int> numbers;

    std::stringstream ss(str);

    for (int i; ss >> i;) {
        numbers.push_back(i);
        if (ss.peek() == ',')
            ss.ignore();
    }

    for (auto i = numbers.begin(); i != numbers.end(); ++i)
    {
        obj.push(*i);
    }
}

void stack_operations()
{
      try
    {
        char exit = 'n';
        int _size = 0;
        cout << "set size: " ; cin >> _size;
        system("CLS");
        arr_stack<int> obj(_size);
        int choice;
        string values;
        while( exit == 'n')
        {
            cout << "push:" << '\t' << '\t' << "1" << endl;
            cout << "pop:" << '\t' << '\t' << "2" << endl;
            cout << "get top:" << '\t' << "3" << endl;
            cout << "get size:" << '\t' << "4" << endl;
            cout << "get capacity:" << '\t' << "5" << endl;
            cout << "display:" << '\t' << "6" << endl << endl;
            cout << "choice: "; cin >> choice;

            switch(choice)
            {
                case 1:
                    cout << "enter values separated with coma ',' : "; cin >> values;
                    string_to_ints(obj, values);
                    break;
                case 2: obj.pop(); break;
                case 3 : cout << obj.get_top() << endl; break;
                case 4: cout << obj.get_size() << endl; break;
                case 5: cout << obj.get_capacity() << endl; break;
                case 6: obj.print_arr();cout << endl;
            }
            cout << "exit? : "; cin >> exit;
            system("CLS");
        }
    }
    catch(const char* msg)
    {
        cerr << msg << endl;
    }
}

void inf_to_postf()
{
    char exit = 'n';
     while(exit == 'n')
    {
        string expr;
        cout << "Write expression: ";
        cin >> expr;
        cout << endl << endl;
        postfix p(expr, 30);
        cout << p.infix_to_postfix() << endl<<endl;

        cout << "exit? : "; cin >> exit;
        system("CLS");
    }
}

int main()
{
    char exit = 'n';
    int choice;
    while(exit == 'n')
    {
        cout << "stack operations: " << '\t' << '\t' << '\t' << "1" << endl;
        cout << "infix to postfix expression: " << '\t' << '\t' << "2" << endl << endl;
        cout << "choice: "; cin >> choice;
        system("CLS");
        if(choice == 1)
        {
            stack_operations();
        }
        if(choice == 2)
        {
            inf_to_postf();
        }
        cout << "exit? : "; cin >> exit;
        system("CLS");
    }

    return 0;
}
