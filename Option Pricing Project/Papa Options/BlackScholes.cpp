#include "BlackScholes.h"

namespace BlackScholes {
	// Base class (BlackScholes):

	// Default constructor
	BlackScholes::BlackScholes()
	{
	}

	// Virtual destructor
	BlackScholes::~BlackScholes()
	{
	}

	// Derived class 1 (EuropeanCall):

	// Parameterised constructor
	EuropeanCall::EuropeanCall(const double& S, const double& E, const double& r, const double& sigma,
		const int& T)
	{
		this->S = S;
		this->E = E;
		this->r = r;
		this->sigma = sigma;
		this->T = T;
	}

	// Virtual destructor
	EuropeanCall::~EuropeanCall()
	{
	}

	// Setter methods
	void EuropeanCall::setS(const double& S)
	{
		this->S = S;
	}

	void EuropeanCall::setE(const double& E)
	{
		this->E = E;
	}

	void EuropeanCall::setR(const double& r)
	{
		this->r = r;
	}

	void EuropeanCall::setSigma(const double& sigma)
	{
		this->sigma = sigma;
	}

	void EuropeanCall::setT(const int& T)
	{
		this->T = T;
	}

	// Option price
	double EuropeanCall::OptionPrice() const
	{
		double d1 = (log(S / E) + (r + 0.5*sigma*sigma)*T) / sigma * sqrt(T);
		double d2 = d1 - sigma * sqrt(T);

		NormalCDF cdf1(d1), cdf2(d2);

		return S * cdf1.Calculate() - E * exp(-r * T)*cdf2.Calculate();
	}

	// Derived class 2 (EuropeanPut):

	// Parameterised constructor
	EuropeanPut::EuropeanPut(const double& S, const double& E, const double& r, const double& sigma,
		const int& T)
	{
		this->S = S;
		this->E = E;
		this->r = r;
		this->sigma = sigma;
		this->T = T;

		blackscholes = new EuropeanCall(EuropeanPut::S, EuropeanPut::E, EuropeanPut::r, EuropeanPut::sigma,
			EuropeanPut::T);
	}

	// Virtual destructor
	EuropeanPut::~EuropeanPut()
	{
		delete blackscholes;
	}

	// Setter methods
	void EuropeanPut::setS(const double& S)
	{
		this->S = S;
	}

	void EuropeanPut::setE(const double& E)
	{
		this->E = E;
	}

	void EuropeanPut::setR(const double& r)
	{
		this->r = r;
	}

	void EuropeanPut::setSigma(const double& sigma)
	{
		this->sigma = sigma;
	}

	void EuropeanPut::setT(const int& T)
	{
		this->T = T;
	}

	// Option price
	double EuropeanPut::OptionPrice() const
	{
		return blackscholes->OptionPrice() - S + exp(-r * T) * E;
	}
}