#include <iostream>
using namespace std;

void _swap(int* arr, int i, int j)
{
    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}

void insertion_sort(int* arr, int n)
{
    int k = 0;
    for(int i=1; i<n; i++)
    {
        k = i;
        for(int j = i-1; j>=0; j--)
        {
            if(arr[k] < arr[j])
            {
                _swap(arr, k, j);
                k--;
            }
        }

        for(int i=0; i<n; i++)
        {
            cout << arr[i] << " ";
        }cout << endl;
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

    insertion_sort(arr, n);

    return 0;
}
