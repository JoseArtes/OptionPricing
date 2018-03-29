#ifndef BLACKSCHOLES_H
#define BLACKSCHOLES_H

#include "NormalCDF.h"

namespace BlackScholes {
	// Base class:
	class BlackScholes
	{
	protected:
		double S, E, r, sigma;
		int T;

		// S - initial stock price
		// E - strike price
		// r - risk-free rate
		// sigma - volatility
		// T - contract maturity length
	public:
		// Default constructor
		BlackScholes();

		// Virtual destructor
		virtual ~BlackScholes();

		// Setter methods
		virtual void setS(const double& S) = 0;
		virtual void setE(const double& E) = 0;
		virtual void setR(const double& r) = 0;
		virtual void setSigma(const double& sigma) = 0;
		virtual void setT(const int& T) = 0;

		// Option price
		virtual double OptionPrice() const = 0;
	};

	// Derived class 1:
	class EuropeanCall : public BlackScholes
	{
	public:
		// Parameterised constructor
		EuropeanCall(const double& S, const double& E, const double& r, const double& sigma,
			const int& T);
		// Virtual destructor
		virtual ~EuropeanCall();

		// Setter methods
		virtual void setS(const double& S);
		virtual void setE(const double& E);
		virtual void setR(const double& r);
		virtual void setSigma(const double& sigma);
		virtual void setT(const int& T);

		// Option price
		virtual double OptionPrice() const;
	};

	// Derived class 2:
	class EuropeanPut : public BlackScholes
	{
	private:
		BlackScholes * blackscholes;
	public:
		// Parameterised constructor
		EuropeanPut(const double& S, const double& E, const double& r, const double& sigma,
			const int& T);

		// Virtual destructor
		virtual ~EuropeanPut();

		// Setter methods
		virtual void setS(const double& S);
		virtual void setE(const double& E);
		virtual void setR(const double& r);
		virtual void setSigma(const double& sigma);
		virtual void setT(const int& T);

		// Option price
		virtual double OptionPrice() const;
	};
}

#endif

