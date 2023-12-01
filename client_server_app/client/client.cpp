#include <iostream>
#include "client_socket.h"
#include <dirent.h>
#include <string>
#include <fstream>
using namespace std;

const char* list_of_files(const char* folder_path)
{
    string files;

    DIR *dir;
    struct dirent *ent;
    dir = opendir(folder_path);

    if (dir != NULL)
    {
        while ((ent = readdir (dir)) != NULL)
        {
            printf ("%s\n", ent->d_name);
            files = files + string(ent->d_name) + " ";
        }
        closedir (dir);
    }
    else
    {
        perror ("Could not open directory");
    }

    char* ccx = new char[files.length() + 1];
    copy(files.begin(), files.end(), ccx);

    return ccx;
}

int main()
{
    client_socket obj;
    obj.connect_to_server();
    obj.send_text(list_of_files("."));
    string file = string(obj.receive_text());
    obj.~client_socket();

    printf("\n\n");

    client_socket new_obj(7505);
    new_obj.connect_to_server();
    new_obj.send_file(file.c_str());

    return 0;
}
