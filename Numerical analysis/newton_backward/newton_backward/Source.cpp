#include <iostream>
#include <iomanip>
#include<vector>
#include<cmath>
using namespace std;

float u_cal(float u, int n)
{
	float temp = u;
	for (int i = 1; i < n; i++)
		temp = temp * (u + i);
	return temp;
}


int fact(int n)
{
	int f = 1;
	for (int i = 2; i <= n; i++)
		f *= i;
	return f;
}

double formula(double x)
{
	return (x / 2 + 1)*sin(x);
}

void main()
{
	const int n = 5;
	float x[] = { 1,1.5, 2, 2.5, 3 };
	float value;

	cout << "set value: ";
	cin >> value;

	float y[n][n];

	for (int i = 0; i < n; i++)
	{
		y[i][0] = formula(x[i]);
	}
	int counter = 0;

	for (int i = 1; i < n; i++) {
		for (int j = n - 1; j >= i; j--)
		{
			y[j][i] = y[j][i - 1] - y[j - 1][i - 1];
			counter++;
		}
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j <= i; j++)
			cout << setw(4) << y[i][j]
			<< "\t";
		cout << endl;
	}

	float sum = y[n - 1][0];
	float u = (value - x[n - 1]) / (x[1] - x[0]);
	for (int i = 1; i < n; i++) {
		sum = sum + (u_cal(u, i) * y[n - 1][i]) /
			fact(i);
	}
	cout << endl << endl;
	cout << "sum for value " << value << " = " << setprecision(4) << sum;
	cout << "\nMistake : " << "|" << formula(value) << "- " << sum << "| = " << abs(((value / 2 + 1)*sin(value)) - sum) << endl;
	system("Pause");
}