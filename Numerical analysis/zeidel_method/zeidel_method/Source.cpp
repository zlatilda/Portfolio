#include<iostream>
#include<iomanip>
#include<cmath>
using namespace std;
int main()
{
	cout.precision(4);
	cout.setf(ios::fixed);
	int i, j, k, flag = 0, count = 0;
	const int n = 4;             
	double a[n][n + 1] = {  0.12, -1, 0.32, -0.18, 0.72, 0.08, -0.12,-0.77,0.32, 0.58, 0.25, 0.22,
		0.14,-1,-1.56, -0.77 ,-0.14, 0.06,-0.12,-1.21 };
	double x[n] = { 0,0,0,0 };
	double eps, y;
	
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j <= n; j++)
		{
			cout << a[i][j] << " ";
		}
		cout << endl;
	}
	cout << "\nEnter the accuracy:\n";
	cin >> eps;
	for (i = 0; i<n; i++)                    
		for (k = i + 1; k<n; k++)
			if (abs(a[i][i])<abs(a[k][i]))
				for (j = 0; j <= n; j++)
				{
					double temp = a[i][j];
					a[i][j] = a[k][j];
					a[k][j] = temp;
				}
	cout << "Iter" << setw(10);
	for (i = 0; i<n; i++)
		cout << "x" << i << setw(18);
	cout << "\n-------------------------------------------------------------------------------------";
	do                            
	{
		cout << "\n" << count + 1 << "." << setw(16);
		for (i = 0; i<n; i++)                
		{
			y = x[i];
			x[i] = a[i][n];
			for (j = 0; j<n; j++)
			{
				if (j != i)
					x[i] = x[i] - a[i][j] * x[j];
			}
			x[i] = x[i] / a[i][i];
			if (abs(x[i] - y) <= eps)            
				flag++;
			cout << x[i] << setw(18);
		}
		cout << "\n";
		count++;
	} while (flag<n);                   

	cout << "\n The solution is as follows:\n";
	for (i = 0; i<n; i++)
		cout << "x" << i << " = " << x[i] << endl;  
	system("pause");
	return 0;
}