#include <iostream>
using namespace std;

void _swap(int* arr, int i, int j)
{
    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}

void bubble_sort(int* arr, int n)
{
    for(int k = 1; k<n; k++)
    {
        for(int i=0; i<n-k; i++)
        {
            if(arr[i] > arr[i+1])
            {
                _swap(arr, i, i+1);
            }

            for(int i=0; i<n; i++)
            {
                cout << arr[i] << " ";
            }cout << endl;
        }
        cout << "-------------------------------------------------" << endl;
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
    bubble_sort(arr, n);

    return 0;
}
