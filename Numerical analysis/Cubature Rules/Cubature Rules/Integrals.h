#pragma once
#include <string>

namespace Integrals
{
	typedef double(*func)(double x);

	class IntegrationMethod
	{
	protected:
		int count = 0;
	public:
		virtual double Small(func f, double a, double b) const = 0;
		virtual double Full(func f, double a, double b, int n) const = 0;
		virtual double Iterative(func f, double a, double b, double e);
		virtual double Order(func f, double a, double b) const;
		int IterationsCount() const;
	};

	class RectanglesMethod : public IntegrationMethod
	{
	public:
		virtual double Small(func f, double a, double b) const override;
		virtual double Full(func f, double a, double b, int n) const override;
	};
	class TrapezesMethod : public IntegrationMethod
	{
	public:
		virtual double Small(func f, double a, double b) const override;
		virtual double Full(func f, double a, double b, int n) const override;
	};
	class ParabolasMethod : public IntegrationMethod
	{
	public:
		virtual double Small(func f, double a, double b) const override;
		virtual double Full(func f, double a, double b, int n) const override;
	};

	template<int N>
	class GaussMethod : public IntegrationMethod
	{
		double x[N];
		double w[N];
	public:
		GaussMethod();
		virtual double Small(func f, double a, double b) const override;
		virtual double Full(func f, double a, double b, int n) const override;
	};

	class Integrate
	{
	public:

		static RectanglesMethod Rectangles;
		static TrapezesMethod Trapezes;
		static ParabolasMethod Parabolas;
		static GaussMethod<4> Gauss4;
		static GaussMethod<5> Gauss5;

		static void Run(IntegrationMethod& method, func f, double a, double b, double e, double exact, std::string title);
	};
}


