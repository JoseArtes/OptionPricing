#include "MonteCarlo.h"

namespace MonteCarlo {
	// Base class (MonteCarlo);

	// Default constructor
	MonteCarlo::MonteCarlo()
	{
	}

	// Virtual destructor
	MonteCarlo::~MonteCarlo()
	{
	}

	// Derived class 1 (EuropeanCall):

	// Parameterised constructor
	EuropeanCall::EuropeanCall(const double& S, const double& E, const double& r, const double& sigma,
		const int& T, const int& jumps, const int& sims)
	{
		this->S = S;
		this->E = E;
		this->r = r;
		this->sigma = sigma;
		this->T = T;
		this->jumps = jumps;
		this->sims = sims;

		d1 = (log(S / E) + (r + 0.5*sigma*sigma)*T) / sigma * sqrt(T);
		d2 = d1 - sigma * sqrt(T);

		payoff = new CallPayOff(E);
	}

	// Virtual destructor
	EuropeanCall::~EuropeanCall()
	{
		delete payoff;
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

	void EuropeanCall::setJumps(const int& jumps)
	{
		this->jumps = jumps;
	}

	void EuropeanCall::setSims(const int& sims)
	{
		this->sims = sims;
	}

	// Greeks
	double EuropeanCall::Delta() const
	{
		NormalCDF cdf(d1);

		return cdf.Calculate();
	}

	double EuropeanCall::Gamma() const
	{
		return exp(-0.5*d1*d1) / (S*sigma*sqrt(2 * pi*T));
	}

	double EuropeanCall::Vega() const
	{
		return S * (exp(-0.5*d1*d1) / sqrt(2 * pi))*sqrt(T);
	}

	double EuropeanCall::Theta() const
	{
		NormalCDF cdf(d2);

		return ((-S * exp(-0.5*d1*d1)*sigma) / (2 * sqrt(2 * pi*T))) - r*E*exp(-r * T)*cdf.Calculate();
	}

	double EuropeanCall::Rho() const
	{
		NormalCDF cdf(d2);

		return E * T*exp(-r * T)*cdf.Calculate();
	}

	// Option price
	double EuropeanCall::OptionPrice() const
	{
		double dt = T / static_cast<double>(jumps);
		double payoff_sum = 0;

		Random random;
		random.setNormal(0.0, 1.0);

		for (int i = 0; i < sims; i++)
		{
			double S_T = S;
			for (int j = 0; j < jumps; j++)
			{
				double phi = random.Normal();
				S_T *= 1 + r * dt + sigma * phi*sqrt(dt);
			}
			payoff_sum += (*payoff)(S_T);
		}

		return exp(-r * T)*(payoff_sum / sims);
	}


	// Derived class 2 (EuropeanPut):

	// Parameterised constructor
	EuropeanPut::EuropeanPut(const double& S, const double& E, const double& r, const double& sigma,
		const int& T, const int& jumps, const int& sims)
	{
		this->S = S;
		this->E = E;
		this->r = r;
		this->sigma = sigma;
		this->T = T;
		this->jumps = jumps;
		this->sims = sims;

		d1 = (log(S / E) + (r + 0.5*sigma*sigma)*T) / sigma * sqrt(T);
		d2 = d1 - sigma * sqrt(T);

		payoff = new PutPayOff(EuropeanPut::E);
	}

	// Virtual destructor
	EuropeanPut::~EuropeanPut()
	{
		delete payoff;
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

	void EuropeanPut::setJumps(const int& jumps)
	{
		this->jumps = jumps;
	}

	void EuropeanPut::setSims(const int& sims)
	{
		this->sims = sims;
	}

	// Greeks
	double EuropeanPut::Delta() const
	{
		NormalCDF cdf(d1);

		return cdf.Calculate() - 1;
	}

	double EuropeanPut::Gamma() const
	{
		return exp(-0.5*d1*d1) / (S*sigma*sqrt(2 * pi*T));
	}

	double EuropeanPut::Vega() const
	{
		return (S*exp(-0.5*d1*d1)*sqrt(T)) / sqrt(2 * pi);
	}

	double EuropeanPut::Theta() const
	{
		NormalCDF cdf(-d2);

		return ((-S * exp(-0.5*d1*d1)*sigma) / (2 * sqrt(2 * pi * T ))) + (r * E*exp(-r * T)*cdf.Calculate());

	}

	double EuropeanPut::Rho() const
	{
		NormalCDF cdf(-d2);

		return -E * T*exp(-r * T)*cdf.Calculate();
	}

	// Option price
	double EuropeanPut::OptionPrice() const
	{
		double dt = T / static_cast<double>(jumps);
		double payoff_sum = 0;

		Random random;
		random.setNormal(0.0, 1.0);

		for (int i = 0; i < sims; i++)
		{
			double S_T = S;
			for (int j = 0; j < jumps; j++)
			{
				double phi = random.Normal();
				S_T *= 1 + r * dt + sigma * phi*sqrt(dt);
			}
			payoff_sum += (*payoff)(S_T);
		}

		return exp(-r * T)*(payoff_sum / sims);
	}

	// Derived class 3 (ArthAsianCall):

	// Parameterised constructor
	ArthAsianCall::ArthAsianCall(const double& S, const double& E, const double& r, const double& sigma,
		const int& T, const int& jumps, const int& sims)
	{
		this->S = S;
		this->E = E;
		this->r = r;
		this->sigma = sigma;
		this->T = T;
		this->jumps = jumps;
		this->sims = sims;

		payoff = new CallPayOff(E);
	}

	// Virtual destructor
	ArthAsianCall::~ArthAsianCall()
	{
		delete payoff;
	}

	// Setter methods
	void ArthAsianCall::setS(const double& S)
	{
		this->S = S;
	}

	void ArthAsianCall::setE(const double& E)
	{
		this->E = E;
	}

	void ArthAsianCall::setR(const double& r)
	{
		this->r = r;
	}

	void ArthAsianCall::setSigma(const double& sigma)
	{
		this->sigma = sigma;
	}

	void ArthAsianCall::setT(const int& T)
	{
		this->T = T;
	}

	void ArthAsianCall::setJumps(const int& jumps)
	{
		this->jumps = jumps;
	}

	void ArthAsianCall::setSims(const int& sims)
	{
		this->sims = sims;
	}

	// Option price
	double ArthAsianCall::OptionPrice() const
	{
		double dt = T / static_cast<double>(jumps);
		double payoff_sum = 0;

		Random random;
		random.setNormal(0.0, 1.0);

		for (int i = 0; i < sims; i++)
		{
			double S_T = S;
			double S_arth = 0;
			for (int j = 0; j < jumps; j++)
			{
				double phi = random.Normal();
				S_T *= 1 + r * dt + sigma * phi*sqrt(dt);
				S_arth += S_T;
			}
			payoff_sum += (*payoff)(S_arth / jumps);
		}

		return exp(-r * T)*(payoff_sum / sims);
	}

	// Derived class 4 (ArthAsianPut):

	// Parameterised constructor
	ArthAsianPut::ArthAsianPut(const double& S, const double& E, const double& r, const double& sigma,
		const int& T, const int& jumps, const int& sims)
	{
		this->S = S;
		this->E = E;
		this->r = r;
		this->sigma = sigma;
		this->T = T;
		this->jumps = jumps;
		this->sims = sims;

		payoff = new PutPayOff(E);
	}

	// Virtual destructor
	ArthAsianPut::~ArthAsianPut()
	{
		delete payoff;
	}

	// Setter methods
	void ArthAsianPut::setS(const double& S)
	{
		this->S = S;
	}

	void ArthAsianPut::setE(const double& E)
	{
		this->E = E;
	}

	void ArthAsianPut::setR(const double& r)
	{
		this->r = r;
	}

	void ArthAsianPut::setSigma(const double& sigma)
	{
		this->sigma = sigma;
	}

	void ArthAsianPut::setT(const int& T)
	{
		this->T = T;
	}

	void ArthAsianPut::setJumps(const int& jumps)
	{
		this->jumps = jumps;
	}

	void ArthAsianPut::setSims(const int& sims)
	{
		this->sims = sims;
	}

	// Option price
	double ArthAsianPut::OptionPrice() const
	{
		double dt = T / static_cast<double>(jumps);
		double payoff_sum = 0;

		Random random;
		random.setNormal(0.0, 1.0);

		for (int i = 0; i < sims; i++)
		{
			double S_T = S;
			double S_arth = 0;
			for (int j = 0; j < jumps; j++)
			{
				double phi = random.Normal();
				S_T *= 1 + r * dt + sigma * phi*sqrt(dt);
				S_arth += S_T;
			}
			payoff_sum += (*payoff)(S_arth / jumps);
		}

		return exp(-r * T)*(payoff_sum / sims);
	}

	// Derived class 5 (GeomAsianCall):

	// Parameterised constructor
	GeomAsianCall::GeomAsianCall(const double& S, const double& E, const double& r, const double& sigma,
		const int& T, const int& jumps, const int& sims)
	{
		this->S = S;
		this->E = E;
		this->r = r;
		this->sigma = sigma;
		this->T = T;
		this->jumps = jumps;
		this->sims = sims;

		payoff = new CallPayOff(E);
	}

	// Virtual destructor
	GeomAsianCall::~GeomAsianCall()
	{
		delete payoff;
	}

	// Setter methods
	void GeomAsianCall::setS(const double& S)
	{
		this->S = S;
	}

	void GeomAsianCall::setE(const double& E)
	{
		this->E = E;
	}

	void GeomAsianCall::setR(const double& r)
	{
		this->r = r;
	}

	void GeomAsianCall::setSigma(const double& sigma)
	{
		this->sigma = sigma;
	}

	void GeomAsianCall::setT(const int& T)
	{
		this->T = T;
	}

	void GeomAsianCall::setJumps(const int& jumps)
	{
		this->jumps = jumps;
	}

	void GeomAsianCall::setSims(const int& sims)
	{
		this->sims = sims;
	}

	// Option price
	double GeomAsianCall::OptionPrice() const
	{
		double dt = T / static_cast<double>(jumps);
		double payoff_sum = 0;

		Random random;
		random.setNormal(0.0, 1.0);

		for (int i = 0; i < sims; i++)
		{
			double S_T = S;
			double S_arth = 0;
			for (int j = 0; j < jumps; j++)
			{
				double phi = random.Normal();
				S_T *= 1 + r * dt + sigma * phi*sqrt(dt);
				S_arth += log(S_T);
			}
			payoff_sum += (*payoff)(exp(S_arth / jumps));
		}

		return exp(-r * T)*(payoff_sum / sims);
	}

	// Derived class 6 (GeomAsianPut):

	// Parameterised constructor
	GeomAsianPut::GeomAsianPut(const double& S, const double& E, const double& r, const double& sigma,
		const int& T, const int& jumps, const int& sims)
	{
		this->S = S;
		this->E = E;
		this->r = r;
		this->sigma = sigma;
		this->T = T;
		this->jumps = jumps;
		this->sims = sims;

		payoff = new PutPayOff(E);
	}

	// Virtual destructor
	GeomAsianPut::~GeomAsianPut()
	{
		delete payoff;
	}

	// Setter methods
	void GeomAsianPut::setS(const double& S)
	{
		this->S = S;
	}

	void GeomAsianPut::setE(const double& E)
	{
		this->E = E;
	}

	void GeomAsianPut::setR(const double& r)
	{
		this->r = r;
	}

	void GeomAsianPut::setSigma(const double& sigma)
	{
		this->sigma = sigma;
	}

	void GeomAsianPut::setT(const int& T)
	{
		this->T = T;
	}

	void GeomAsianPut::setJumps(const int& jumps)
	{
		this->jumps = jumps;
	}

	void GeomAsianPut::setSims(const int& sims)
	{
		this->sims = sims;
	}

	// Option price
	double GeomAsianPut::OptionPrice() const
	{
		double dt = T / static_cast<double>(jumps);
		double payoff_sum = 0;

		Random random;
		random.setNormal(0.0, 1.0);

		for (int i = 0; i < sims; i++)
		{
			double S_T = S;
			double S_arth = 0;
			for (int j = 0; j < jumps; j++)
			{
				double phi = random.Normal();
				S_T *= 1 + r * dt + sigma * phi*sqrt(dt);
				S_arth += log(S_T);
			}
			payoff_sum += (*payoff)(exp(S_arth / jumps));
		}

		return exp(-r * T)*(payoff_sum / sims);
	}
}