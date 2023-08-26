#include <iostream>
#include <cmath>
#include <stdio.h>
#include <string.h>
using namespace std;

void _swap(int* arr, int i, int j)
{
    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}

void print(int* arr, int n)
{
    for(int i=0; i<n; i++)
    {
        cout << arr[i] << " ";
    }cout << endl;
}

int _partition(int* arr, int start, int _end)
{
    int pivot = arr[_end];

    int i = (start - 1);

    for (int j = start; j < _end; j++)
    {
        if (arr[j] <= pivot)
        {
            i++;
            _swap(arr, i, j);
        }
    }

    _swap(arr, i + 1, _end);

    return (i + 1);
}

void quick_sort(int* arr, int start, int _end)
{
    if (start < _end)
    {
        int pi = _partition(arr, start, _end);

        quick_sort(arr, start, pi - 1);

        quick_sort(arr, pi + 1, _end);
    }
}


int main()
{
    int n = 7;
    int* arr = new int[n];
    arr[0] = 8;
    arr[1] = 7;
    arr[2] = 6;
    arr[3] = 1;
    arr[4] = 0;
    arr[5] = 9;
    arr[6] = 2;

    quick_sort(arr, 0, n);
    print(arr, n);

    return 0;
}
