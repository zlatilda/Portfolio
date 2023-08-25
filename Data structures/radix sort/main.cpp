#include <iostream>
#include <bits/stdc++.h>
using namespace std;

void print(int* arr, int _size)
{
    for(int i=0; i<_size; i++)
    {
        cout << arr[i] << " ";
    }cout << endl;
}

void counting_sort(int* arr, int _size, int div)
{
    int output[_size];
    int _count[10] = {0};

    for(int i=0; i < _size; i++)
    {
        _count[(arr[i]/div)%10]++;
    }

    for(int i = 1; i < 10; i++)
    {
        _count[i] += _count[i-1];
    }

    for(int i = _size - 1; i >= 0; i--)
    {
        output[_count[(arr[i]/div)%10] - 1] = arr[i];
        _count[(arr[i]/div)%10]--;
    }

    for(int i=0; i<_size; i++)
    {
        arr[i] = output[i];
    }
}

void radix_sort(int* arr, int _size)
{
    int m = *max_element(arr, arr + _size);
    for(int div = 1; m/div > 0; div *= 10)
    {
        counting_sort(arr, _size, div);
    }
}

int main()
{
    int _size;
    cout << "size: ";
    cin >> _size;
    int* arr = new int[_size];
    cout << "enter numbers" << endl;
    for(int i=0; i<_size; i++)
    {
        cout << "arr[" << i << "]: ";
        cin >> arr[i];
    }
    print(arr, _size);
    radix_sort(arr, _size);
    print(arr, _size);
    return 0;
}
