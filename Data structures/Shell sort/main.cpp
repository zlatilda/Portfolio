#include <iostream>
#include <cmath>
#include <stdio.h>
#include <string.h>
using namespace std;

void _swap(int* arr, int i, int j)
{
    cout << "start: " << arr[i] << "    end: " << arr[j] << endl;
    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}

void shell_sort(int* arr, int n)
{
    int span = ceil(double(n)/2);
    int start = 0;
    int k = 1;
    while(span > 0)
    {
        while(start+span < n )
        {
            if(arr[start] > arr[start+span])
                _swap(arr, start, start+span);

            start++;
        }
        for(int i=0; i<n; i++)
        {
            cout << arr[i] << " ";
        }cout << endl;

        k++;
        start = 0;
        span -= 1;
    }
}

int main()
{
    try
    {
        int n = 7;
        int* arr = new int[n];
        arr[0] = 42;
        arr[1] = 33;
        arr[2] = 23;
        arr[3] = 74;
        arr[4] = 44;
        arr[5] = 67;
        arr[6] = 49;

        shell_sort(arr, n);
    }
    catch(const char* ch)
    {
        cerr << ch;
    }

    return 0;
}
