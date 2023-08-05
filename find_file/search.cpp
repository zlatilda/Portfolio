#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include "search.h"
using namespace std;

mutex m;
static bool exit_thread_flag = false;

bool ListDirectoryContents(const char* sDir, const char* f, int start_from)
{
    int folders_num = 0;

    WIN32_FIND_DATA fdFile;
    HANDLE hFind = NULL;

    char sPath[2048];

    sprintf(sPath, "%s\\*.*", sDir);

    if((hFind = FindFirstFile(sPath, &fdFile)) == INVALID_HANDLE_VALUE)
    {
        //printf("Path not found: [%s]\n", sDir);
        return false;
    }

   do
    {
        if(strcmp(fdFile.cFileName, ".") != 0
                && strcmp(fdFile.cFileName, "..") != 0)
        {

            sprintf(sPath, "%s\\%s", sDir, fdFile.cFileName);


            if(fdFile.dwFileAttributes &FILE_ATTRIBUTE_DIRECTORY)
            {
               // printf("Directory: %s\n", sPath);
                folders_num++;
                if(folders_num >= start_from)
                {
                    ListDirectoryContents(sPath, f, start_from);
                }
            }
            else{
                //printf("File: %s\n", sPath);
            }

            m.lock();
            if(strcmp(fdFile.cFileName, f) == 0)
            {

                printf("File path: %s\n", sPath);

                exit_thread_flag = true;
            }
            m.unlock();
        }

    }while(FindNextFile(hFind, &fdFile)&&(exit_thread_flag == false));

    FindClose(hFind);
    folders_num = 0;

    return true;
}

int get_directories_num()
{
    int num = 0;

    WIN32_FIND_DATA fdFile;
    HANDLE hFind = NULL;

    char sPath[2048];

    sprintf(sPath, "%s\\*.*", "C:\\");
    hFind = FindFirstFile(sPath, &fdFile);

    while (FindNextFileA(hFind, &fdFile) != 0)
    {
        num++;
    }
    FindClose(hFind);

    return num;
}

void _search()
{
    string search_file;
    printf("File to search: ");
    cin >> search_file;
    const char* c_search_file = search_file.c_str();

    int _size =  get_directories_num();

    thread thread_1(ListDirectoryContents, "C:\\", c_search_file, 0);
    thread thread_2(ListDirectoryContents, "C:\\", c_search_file, (_size/1.5));
    thread thread_3(ListDirectoryContents, "C:\\", c_search_file, (_size/2.5));
    thread thread_4(ListDirectoryContents, "C:\\", c_search_file, (_size/4));

    thread_1.join();
    thread_2.join();
    thread_3.join();
    thread_4.join();

    if(exit_thread_flag == false)
    {
        printf("Nothing found \n");
    }
}



