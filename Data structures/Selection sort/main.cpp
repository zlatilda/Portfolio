#include <iostream>
using namespace std;

void _swap(int* arr, int i, int j)
{
    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}

int find_min(int* arr, int start_pos, int n)
{
    int min_pos = start_pos;
    int min_val = arr[start_pos];

    for(int i=start_pos; i<n; i++)
    {
        if(arr[i] < min_val)
        {
            min_val = arr[i];
            min_pos = i;
        }
    }

    return min_pos;
}

void selection_sort(int* arr, int n)
{
    for(int i=0; i<n; i++)
    {
        _swap(arr, i, find_min(arr, i, n));

        for(int i=0; i<n; i++)
        {
            cout << arr[i] << " ";
        }
        cout << endl;
    }
}

int main()
{
    int n;
    cout << "size: ";
    cin >> n;
    cout << "enter arr elements:" << endl;
    int* arr = new int[n];
    for(int i=0; i<n; i++)
    {
        cin >> arr[i];
    }
    cout << endl;
    selection_sort(arr, n);


    return 0;
}
