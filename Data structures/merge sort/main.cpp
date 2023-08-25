#include <iostream>
#include <cmath>
#include <stdio.h>
#include <string.h>
using namespace std;

void print(int* arr, int n)
{
    for(int i=0; i<n; i++)
    {
        cout << arr[i] << " ";
    }cout << endl;
}

void _merge(int* arr, int l, int m, int r)
{
    int i = l;
    int j = m+1;
    int k = l;

    int temp[r+1];
    while(i <= m && j <= r)
    {
        if(arr[i] <= arr[j])
        {
            temp[k] = arr[i];
            i++;
            k++;
        }
        else
        {
            temp[k] = arr[j];
            j++;
            k++;
        }
    }
    while(i <= m)
    {
        temp[k] = arr[i];
        i++;
        k++;
    }
    while(j <= r)
    {
        temp[k] = arr[j];
        j++;
        k++;
    }
    for(int s=l; s<=r; s++)
    {
        arr[s] = temp[s];
    }
}

void merge_sort(int* arr, int l, int r)
{
    if(l < r)
    {
        int m = (l+r)/2;
        merge_sort(arr, 0, m);
        merge_sort(arr, m+1, r);
        _merge(arr, l, m, r);
    }
}

int main()
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

    merge_sort(arr, 0, n-1);
    print(arr, n);

    return 0;
}
