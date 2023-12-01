#include <iostream>
#include "server_socket.h"
using namespace std;

int main()
{
    server_socket obj;
    obj.binding();
    obj.listening(10);
    obj.accept_connection();
    obj.receive_text();

    printf("Write name of a file you want to download: ");
    string file_name;
    cin >> file_name;

    obj.send_text(file_name.c_str());
    obj.~server_socket();

    printf("\n\n");

    server_socket new_obj(7505);
    new_obj.binding();
    new_obj.listening(10);
    new_obj.accept_connection();
    new_obj.receive_file(file_name.c_str());

    return 0;
}
