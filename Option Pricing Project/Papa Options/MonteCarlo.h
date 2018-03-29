#ifndef MONTECARLO_H
#define MONTECARLO_H

#include "PayOff.h"
#include "Random.h"
#include "NormalCDF.h"

namespace MonteCarlo {
	// Base class:
	class MonteCarlo
	{
	protected:
		double S, E, r, sigma;
		int T, jumps, sims;

		double d1, d2; // Necessary for the Greeks of vanilla Europeans.

		PayOff* payoff;

		const double pi = 4 * atan(1);

		// S - initial stock price
		// E - strike price
		// r - risk-free rate
		// sigma - volatility
		// T - contract maturity length
		// jumps - jumps
		// sims - number of simulations

		// payoff - option payoff pointer

		// pi - 3.14159...

	public:
		// Default constructor
		MonteCarlo();

		// Virtual destructor
		virtual ~MonteCarlo();

		// Setter methods
		virtual void setS(const double& S) = 0;
		virtual void setE(const double& E) = 0;
		virtual void setR(const double& r) = 0;
		virtual void setSigma(const double& sigma) = 0;
		virtual void setT(const int& T) = 0;
		virtual void setJumps(const int& jumps) = 0;
		virtual void setSims(const int& sims) = 0;

		// Option price
		virtual double OptionPrice() const = 0;
	};


	// Derived class 1:
	class EuropeanCall : public MonteCarlo
	{
	public:
		// Parameterised constructor
		EuropeanCall(const double& S, const double& E, const double& r, const double& sigma,
			const int& T, const int& jumps, const int& sims);

		// Virtual destructor
		virtual ~EuropeanCall();

		// Setter methods
		virtual void setS(const double& S);
		virtual void setE(const double& E);
		virtual void setR(const double& r);
		virtual void setSigma(const double& sigma);
		virtual void setT(const int& T);
		virtual void setJumps(const int& jumps);
		virtual void setSims(const int& sims);

		// Greeks
		double Delta() const;
		double Gamma() const;
		double Vega() const;
		double Theta() const;
		double Rho() const;

		// Option price
		virtual double OptionPrice() const;
	};

	// Derived class 2:
	class EuropeanPut : public MonteCarlo
	{
	public:
		// Parameterised constructor
		EuropeanPut(const double& S, const double& E, const double& r, const double& sigma,
			const int& T, const int& jumps, const int& sims);

		// Virtual destructor
		virtual ~EuropeanPut();

		// Setter methods
		virtual void setS(const double& S);
		virtual void setE(const double& E);
		virtual void setR(const double& r);
		virtual void setSigma(const double& sigma);
		virtual void setT(const int& T);
		virtual void setJumps(const int& jumps);
		virtual void setSims(const int& sims);

		// Greeks
		double Delta() const;
		double Gamma() const;
		double Vega() const;
		double Theta() const;
		double Rho() const;

		// Option price
		virtual double OptionPrice() const;
	};

	// Derived class 3:
	class ArthAsianCall : public MonteCarlo
	{
	public:
		// Parameterised constructor
		ArthAsianCall(const double& S, const double& E, const double& r, const double& sigma,
			const int& T, const int& jumps, const int& sims);

		// Virtual destructor
		virtual ~ArthAsianCall();

		// Setter methods
		virtual void setS(const double& S);
		virtual void setE(const double& E);
		virtual void setR(const double& r);
		virtual void setSigma(const double& sigma);
		virtual void setT(const int& T);
		virtual void setJumps(const int& jumps);
		virtual void setSims(const int& sims);

		// Option price
		virtual double OptionPrice() const;
	};

	// Derived class 4:
	class ArthAsianPut : public MonteCarlo
	{
	public:
		// Parameterised constructor
		ArthAsianPut(const double& S, const double& E, const double& r, const double& sigma,
			const int& T, const int& jumps, const int& sims);

		// Virtual destructor
		virtual ~ArthAsianPut();

		// Setter methods
		virtual void setS(const double& S);
		virtual void setE(const double& E);
		virtual void setR(const double& r);
		virtual void setSigma(const double& sigma);
		virtual void setT(const int& T);
		virtual void setJumps(const int& jumps);
		virtual void setSims(const int& sims);

		// Option price
		virtual double OptionPrice() const;
	};

	// Derived class 5:
	class GeomAsianCall : public MonteCarlo
	{
	public:
		// Parameterised constructor
		GeomAsianCall(const double& S, const double& E, const double& r, const double& sigma,
			const int& T, const int& jumps, const int& sims);

		// Virtual destructor
		virtual ~GeomAsianCall();

		// Setter methods
		virtual void setS(const double& S);
		virtual void setE(const double& E);
		virtual void setR(const double& r);
		virtual void setSigma(const double& sigma);
		virtual void setT(const int& T);
		virtual void setJumps(const int& jumps);
		virtual void setSims(const int& sims);

		// Option price
		virtual double OptionPrice() const;
	};

	// Derived class 6:
	class GeomAsianPut : public MonteCarlo
	{
	public:
		// Parameterised constructor
		GeomAsianPut(const double& S, const double& E, const double& r, const double& sigma,
			const int& T, const int& jumps, const int& sims);

		// Virtual destructor
		virtual ~GeomAsianPut();

		// Setter methods
		virtual void setS(const double& S);
		virtual void setE(const double& E);
		virtual void setR(const double& r);
		virtual void setSigma(const double& sigma);
		virtual void setT(const int& T);
		virtual void setJumps(const int& jumps);
		virtual void setSims(const int& sims);

		// Option price
		virtual double OptionPrice() const;
	};
}

#endif