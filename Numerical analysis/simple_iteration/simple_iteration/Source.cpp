#include <iostream>
#include <cmath>
using namespace std;

double y_fi(double x, double y)
{
	return (10 * (log10(y)) + 4 - 2 * x);
}

double x_fi(double x, double  y)
{
	return ((6 * y - 20 * (log10(x)) - 16) / 5);
}

int main()
{
	double x, y;
	cout << "x: "; cin >> x;
	cout << "y: "; cin >> y;

	double eps;
	cout << "eps: "; cin >> eps;
	double x_last, y_last;
	double dX, dY;
	int iter = 0;
	bool f1 = false;
	bool f2 = false;
	bool f = false;
	do
	{
		x_last = x;
		y_last = y;
		x = fabs(x_fi(x_last, y_last));
		y = fabs(y_fi(x_last, y_last));
		dX = x - x_last;
		dY = y - y_last;
		iter++;

		if (pow(dX, 2) <= eps) { f1 = true; }     
		if (pow(dY, 2) <= eps) { f2 = true; } /*pow(dX, 2) > eps && pow(dY, 2) > eps*/
		f = f1 && f2;
	} while (f == false);

	cout << "x = " << x << endl;
	cout << "y = " << y << endl;
	cout << "iteratoins: " << iter << endl;
	system("pause");
}

