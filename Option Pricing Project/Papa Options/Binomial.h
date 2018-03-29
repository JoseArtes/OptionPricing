#ifndef BINOMIAL_H
#define BINOMIAL_H

#include<iostream>
#include<algorithm>
#include<cmath>
#include<vector>
#include<Eigen/Dense>

#include "PayOff.h"

using namespace std;

namespace Binomial {
	// Base class:
	class Binomial
	{
	protected:
		double S, E, r, sigma;
		double u, d;
		double q;
		int T, jumps;
		double dt;
		Eigen::MatrixXd stock_tree;
		Eigen::MatrixXd option_tree;

		PayOff* payoff;

		// S - initial stock price
		// E - strike price
		// r - risk-free rate
		// sigma - volatility
		// u - increasing stock price factor
		// d - decreasing stock price factor
		// q - risk-neutral probabilities
		// T - contract maturity length
		// jumps - jumps
		// dt - jumping factor
		// stock_tree - underlying stock price tree
		// option_tree - option tree

		// payoff - option payoff pointer

	public:
		// Default constructor
		Binomial();

		// Virtual destructor
		virtual ~Binomial();

		// Pure virtual setter methods
		virtual void setS(const double& S) = 0;
		virtual void setE(const double& E) = 0;
		virtual void setR(const double& r) = 0;
		virtual void setSigma(const double& sigma) = 0;
		virtual void setQ() = 0;
		virtual void setT(const int& T) = 0;
		virtual void setJumps(const int& jumps) = 0;
		virtual void setTrees() = 0;

		// Option price
		virtual double OptionPrice() = 0;
	};

	// Derived class 1:
	class EuropeanCall : public Binomial
	{
	public:
		// Parameterised constructor
		EuropeanCall(const double& S, const double& E, const double& r, const double& sigma,
			const int& T, const int& jumps);

		// Virtual destructor
		virtual ~EuropeanCall();

		// Setter methods
		virtual void setS(const double& S);
		virtual void setE(const double& E);
		virtual void setR(const double& r);
		virtual void setSigma(const double& sigma);
		virtual void setQ();
		virtual void setT(const int& T);
		virtual void setJumps(const int& jumps);
		virtual void setTrees();

		// Option price
		virtual double OptionPrice();
	};

	// Derived class 2:
	class EuropeanPut : public Binomial
	{
	public:
		// Parameterised constructor
		EuropeanPut(const double& S, const double& E, const double& r, const double& sigma,
			const int& T, const int& jumps);

		// Virtual destructor
		virtual ~EuropeanPut();

		// Setter methods
		virtual void setS(const double& S);
		virtual void setE(const double& E);
		virtual void setR(const double& r);
		virtual void setSigma(const double& sigma);
		virtual void setQ();
		virtual void setT(const int& T);
		virtual void setJumps(const int& jumps);
		virtual void setTrees();

		// Option price
		virtual double OptionPrice();
	};

	// Derived class 3:
	class AmericanCall : public Binomial
	{
	public:
		// Parameterised constructor
		AmericanCall(const double& S, const double& E, const double& r, const double& sigma,
			const int& T, const int& jumps);

		// Virtual destructor
		virtual ~AmericanCall();

		// Setter methods
		virtual void setS(const double& S);
		virtual void setE(const double& E);
		virtual void setR(const double& r);
		virtual void setSigma(const double& sigma);
		virtual void setQ();
		virtual void setT(const int& T);
		virtual void setJumps(const int& jumps);
		virtual void setTrees();

		// Option price
		virtual double OptionPrice();
	};

	// Derived class 4:
	class AmericanPut : public Binomial
	{
	public:
		// Parameterised constructor
		AmericanPut(const double& S, const double& E, const double& r, const double& sigma,
			const int& T, const int& jumps);

		// Virtual destructor
		virtual ~AmericanPut();

		// Setter methods
		virtual void setS(const double& S);
		virtual void setE(const double& E);
		virtual void setR(const double& r);
		virtual void setSigma(const double& sigma);
		virtual void setQ();
		virtual void setT(const int& T);
		virtual void setJumps(const int& jumps);
		virtual void setTrees();

		// Option price
		virtual double OptionPrice();
	};
}

#endif