#include <cmath>
#include <iostream>
#include "Integrals.h"

using namespace std;

namespace Integrals
{
	int IntegrationMethod::IterationsCount() const
	{
		return count;
	}

	double IntegrationMethod::Iterative(func f, double a, double b, double e)
	{
		double curr = Small(f, a, b);
		double prev;

		int n = 1;
		do
		{
			n++;
			prev = curr;
			curr = Full(f, a, b, n);
		} while (abs(curr - prev) > e);
		count = n - 1;

		return curr;
	}

	double IntegrationMethod::Order(func f, double a, double b) const
	{
		int n = count;
		return log((Full(f, a, b, n) - Full(f, a, b, n * 2)) /
			(Full(f, a, b, n * 2) - Full(f, a, b, n * 4))) / log(2.0);
	}

	double RectanglesMethod::Small(func f, double a, double b) const
	{
		return (b - a)*f((a + b) / 2);
	}
	double RectanglesMethod::Full(func f, double a, double b, int n) const
	{
		double h = (b - a) / n;
		double result = 0;
		for (int i = 1; i <= n; ++i)
			result += f(a + (2 * i - 1) * h / 2);
		result *= (b - a) / n;
		return result;
	}

	double TrapezesMethod::Small(func f, double a, double b) const
	{
		return 0.5*(b - a)*(f(a) + f(b));
	}
	double TrapezesMethod::Full(func f, double a, double b, int n) const
	{
		double h = (b - a) / n;
		double result = f(a) + f(b);
		for (int i = 1; i < n; ++i)
			result += 2 * f(a + i * h);
		result *= (b - a) / (2 * n);
		return result;
	}

	double ParabolasMethod::Small(func f, double a, double b) const
	{
		return (b - a) / 6 * (f(a) + 4 * f((a + b) / 2) + f(b));
	}
	double ParabolasMethod::Full(func f, double a, double b, int n) const
	{
		double h = (b - a) / (2 * n);
		double result = f(a) + f(b);
		for (int i = 1; i < 2 * n; ++i)
		{
			double elem = 2 * f(a + i * h);
			if (i % 2 == 1)
				elem *= 2;
			result += elem;
		}
		result *= (b - a) / (6 * n);
		return result;
	}

	template<int N>
	double GaussMethod<N>::Small(func f, double a, double b) const
	{
		double result = 0;
		for (int i = 0; i < N; ++i)
			result += w[i] * f(((b - a)*x[i] + (b + a)) * 0.5);
		return result * (b - a) * 0.5;
	}
	template<int N>
	double GaussMethod<N>::Full(func f, double a, double b, int n) const
	{
		double result = 0;
		double h = (b - a) / n;
		for (int i = 0; i < n; ++i)
			result += Small(f, a + i * h, a + (i + 1)*h);
		return result;
	}

	template<>
	GaussMethod<4>::GaussMethod()
	{
		x[0] = -0.8611363115940526;
		x[1] = -0.3399810435848563;
		x[2] = -x[1];
		x[3] = -x[0];

		w[0] = 0.3478548451374538;
		w[1] = 0.6521451548625461;
		w[2] = w[1];
		w[3] = w[0];
	}

	template<>
	GaussMethod<5>::GaussMethod()
	{
		x[0] = -0.9061798459386640;
		x[1] = -0.5384693101056831;
		x[2] = 0.0000000000000000;
		x[3] = -x[1];
		x[4] = -x[0];

		w[0] = 0.2369268850561891;
		w[1] = 0.4786286704993665;
		w[2] = 0.5688888888888889;
		w[3] = w[1];
		w[4] = w[0];
	}

	RectanglesMethod Integrate::Rectangles;
	TrapezesMethod Integrate::Trapezes;
	ParabolasMethod Integrate::Parabolas;
	GaussMethod<4> Integrate::Gauss4;
	GaussMethod<5> Integrate::Gauss5;

	void Integrate::Run(IntegrationMethod& method, func f, double a, double b, double e, double exact, string title)
	{
		double approx;
		cout << title << " method" << endl;
		cout << "  I     = " << (approx = method.Iterative(f, a, b, e)) << endl;
		cout << "  delta = " << abs(exact - approx) << endl;
		cout << "  count = " << method.IterationsCount() << endl;
		cout << "  k     = " << method.Order(f, a, b) << endl;
		cout << endl;
	}
}
