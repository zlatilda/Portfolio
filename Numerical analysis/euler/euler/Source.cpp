#include <iostream>
#include <cmath>
#include <iomanip> 
using namespace std;

double F(double x, double y) {
	return ((y/x) - 2*pow(y, 2));
}

double f(double x)
{
	return (x/(pow(x,2) + 3));
}

int main() {
	double a = 1; double b = 2; double h = 0.1;
	double n = (b - a) / h;
	double *X = new double[(int)n];
	double *Y = new double[(int)n];
	double *exact = new double[(int)n];
	X[0] = a; Y[0] = f(1); exact[0] = f(1);
	for (int i = 1; i <= n; i++) {
		X[i] = a + i*h;
		Y[i] = Y[i - 1] + h*F(X[i - 1], Y[i - 1]);
		exact[i] = f(a + i*h);
	}
	cout << "a = " << a << setw(15) << "b = " << b << setw(15) << "h = " << h << endl << endl;
	cout << "X[i]" << setw(30) << "Y[i]" << setw(30) << "Exact Y[i]" << setw(30) << "Error" << endl;
	cout << "=========================================================================================================" << endl;
	for (int i = 0; i <= n; i++) {
		cout << X[i] << setw(30) << Y[i] << setw(30) << exact[i] << setw(30) << fabs(Y[i] - exact[i]) << endl;
	}
	cout << endl;
	/*for (int i = 0; i <= n; i++) {
		cout << "Y[" << i << "]=" << Y[i] << " ";
	}*/

	system("pause");
	return 0;
}