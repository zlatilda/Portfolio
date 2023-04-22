#include <iostream>
#include <cmath>
#include "Integrals.h"

using namespace std;
using namespace Integrals;


double f(double x)
{
	return sqrt(6*x - 5);
}
double F(double x)
{
	return ((1/9)*sqrt(pow((6*x-5),3)));
}

int main()
{
	double a = 3;
	double b = 9;
	double e;

	cout << "e = ";
	cin >> e;
	cout << endl;

	cout.precision(10);

	double approx;
	double exact = F(b) - F(a);
	cout << "Exact I = " << exact << endl;
	cout << endl;

	Integrate::Run(Integrate::Rectangles, f, a, b, e, exact, "Rectangle");
	Integrate::Run(Integrate::Trapezes, f, a, b, e, exact, "Trapezes");
	Integrate::Run(Integrate::Parabolas, f, a, b, e, exact, "Parabolas");
	Integrate::Run(Integrate::Gauss4, f, a, b, e, exact, "Gauss with 4 points");
	Integrate::Run(Integrate::Gauss5, f, a, b, e, exact, "Gauss with 5 points");

	system("pause");
	return 0;
}