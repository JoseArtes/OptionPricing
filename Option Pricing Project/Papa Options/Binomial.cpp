#include "Binomial.h"

namespace Binomial
{
	// Base class (Binomial):

	// Default constructor
	Binomial::Binomial()
	{
	}

	// Virtual destructor
	Binomial::~Binomial()
	{
	}

	// Derived class 1 (EuropeanCall):
	
	// Parameterised constructor
	EuropeanCall::EuropeanCall(const double& S, const double& E, const double& r, const double& sigma,
		const int& T, const int& jumps)
	{
		this->S = S;
		this->E = E;
		this->r = r;
		this->sigma = sigma;
		this->T = T;
		this->jumps = jumps;

		stock_tree = Eigen::MatrixXd::Zero(jumps + 1, jumps + 1);
		option_tree = Eigen::MatrixXd::Zero(jumps + 1, jumps + 1);

		dt = T / static_cast<double>(jumps);

		// Cox, Ross and Rubinstein (CRR) method to generate the lattice
		u = exp(sigma*sqrt(dt)); // Up-factor
		d = exp(-sigma * sqrt(dt));	 // Down-factor
		q = (exp(r*dt) - d) / (u - d); // Risk-neutral probability

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

	void EuropeanCall::setQ()
	{
		dt = T / static_cast<double>(jumps);
		u = exp(sigma * sqrt(dt));
		d = exp(-sigma * sqrt(dt));
		q = (exp(r*dt) - d) / (u - d);
	}

	void EuropeanCall::setT(const int& T)
	{
		this->T = T;
	}

	void EuropeanCall::setJumps(const int& jumps)
	{
		this->jumps = jumps;
	}

	void EuropeanCall::setTrees()
	{
		stock_tree = Eigen::MatrixXd::Zero(jumps + 1, jumps + 1);
		option_tree = Eigen::MatrixXd::Zero(jumps + 1, jumps + 1);
	}

	// Option price
	double EuropeanCall::OptionPrice()
	{
		for (int i = 0; i <= jumps; i++)
		{
			for (int j = 0; j <= i; j++)
			{
				stock_tree(j,i) = S * pow(u, i - j)*pow(d, j);
			}
		}

		for (int i = 0; i <= jumps; i++)
		{
			option_tree(i,jumps) = (*payoff)(stock_tree(i,jumps));
		}

		for (int i = jumps - 1; i>=0; i--)
		{
			for (int j = 0; j <= i; j++)
			{
				option_tree(j, i) = exp(-dt * r)*(q*option_tree(j, i + 1) + (1 - q)*option_tree(j + 1, i + 1));
			}
		}

		return option_tree(0, 0);
	}

	// Derived class 2 (EuropeanPut):
	
	// Parameterised constructor
	EuropeanPut::EuropeanPut(const double& S, const double& E, const double& r, const double& sigma,
		const int& T, const int& jumps)
	{
		this->S = S;
		this->E = E;
		this->r = r;
		this->sigma = sigma;
		this->T = T;
		this->jumps = jumps;

		stock_tree = Eigen::MatrixXd::Zero(jumps + 1, jumps + 1);
		option_tree = Eigen::MatrixXd::Zero(jumps + 1, jumps + 1);

		dt = T / static_cast<double>(jumps);

		u = exp(sigma*sqrt(dt));
		d = exp(-sigma * sqrt(dt));
		q = (exp(r*dt) - d) / (u - d);

		payoff = new PutPayOff(E);
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

	void EuropeanPut::setQ()
	{
		dt = T / static_cast<double>(jumps);
		u = exp(sigma * sqrt(dt));
		d = exp(-sigma * sqrt(dt));
		q = (exp(r*dt) - d) / (u - d);
	}

	void EuropeanPut::setT(const int& T)
	{
		this->T = T;
	}

	void EuropeanPut::setJumps(const int& jumps)
	{
		this->jumps = jumps;
	}

	void EuropeanPut::setTrees()
	{
		stock_tree = Eigen::MatrixXd::Zero(jumps + 1, jumps + 1);
		option_tree = Eigen::MatrixXd::Zero(jumps + 1, jumps + 1);

	}

	// Option price
	double EuropeanPut::OptionPrice()
	{
		for (int i = 0; i <= jumps; i++)
		{
			for (int j = 0; j <= i; j++)
			{
				stock_tree(j, i) = S * pow(u, i - j)*pow(d, j);
			}
		}

		for (int i = 0; i <= jumps; i++)
		{
			option_tree(i, jumps) = (*payoff)(stock_tree(i, jumps));
		}

		for (int i = jumps - 1; i >= 0; i--)
		{
			for (int j = 0; j <= i; j++)
			{
				option_tree(j, i) = exp(-dt * r)*(q*option_tree(j, i + 1) + (1 - q)*option_tree(j + 1, i + 1));
			}
		}

		return option_tree(0, 0);
	}

	//  Derived class 3  (AmericanCall):

	// Parameterised constructor
	AmericanCall::AmericanCall(const double& S, const double& E, const double& r, const double& sigma,
		const int& T, const int& jumps)
	{
		this->S = S;
		this->E = E;
		this->r = r;
		this->sigma = sigma;
		this->T = T;
		this->jumps = jumps;

		stock_tree = Eigen::MatrixXd::Zero(jumps + 1, jumps + 1);
		option_tree = Eigen::MatrixXd::Zero(jumps + 1, jumps + 1);

		dt = T / static_cast<double>(jumps);

		u = exp(sigma*sqrt(dt));
		d = exp(-sigma * sqrt(dt));
		q = (exp(r*dt) - d) / (u - d);

		payoff = new CallPayOff(E);
	}

	// Virtual destructor
	AmericanCall::~AmericanCall()
	{
		delete payoff;
	}

	// Setter methods
	void AmericanCall::setS(const double& S)
	{
		this->S = S;
	}

	void AmericanCall::setE(const double& E)
	{
		this->E = E;
	}

	void AmericanCall::setR(const double& r)
	{
		this->r = r;
	}

	void AmericanCall::setSigma(const double& sigma)
	{
		this->sigma = sigma;
	}

	void AmericanCall::setQ()
	{
		dt = T / static_cast<double>(jumps);
		u = exp(sigma*sqrt(dt));
		d = exp(-sigma * sqrt(dt));
		q = (exp(r*dt) - d) / (u - d);
	}

	void AmericanCall::setT(const int& T)
	{
		this->T = T;
	}

	void AmericanCall::setJumps(const int& jumps)
	{
		this->jumps = jumps;
	}

	void AmericanCall::setTrees()
	{
		stock_tree = Eigen::MatrixXd::Zero(jumps + 1, jumps + 1);
		option_tree = Eigen::MatrixXd::Zero(jumps + 1, jumps + 1);
	}

	// Option price
	double AmericanCall::OptionPrice()
	{
		for (int i = 0; i <= jumps; i++)
		{
			for (int j = 0; j <= i; j++)
			{
				stock_tree(j, i) = S * pow(u, i - j)*pow(d, j);
			}
		}

		for (int i = 0; i <= jumps; i++)
		{
			option_tree(i, jumps) = (*payoff)(stock_tree(i, jumps));
		}

		for (int i = jumps - 1; i >= 0; i--)
		{
			for (int j = 0; j <= i; j++)
			{
				double option_value = exp(-dt * r)*(q*option_tree(j, i + 1) + (1 - q)*option_tree(j + 1, i + 1));
				double option_payoff = (*payoff)(stock_tree(j, i));
				if (option_value < option_payoff)
				{
					option_tree(j, i) = option_payoff;
				}
				else
				{
					option_tree(j, i) = option_value;
				}
			}
		}

		return option_tree(0, 0);
	}

	// Derived class 4 (AmericanPut):

	// Parameterised constructor
	AmericanPut::AmericanPut(const double& S, const double& E, const double& r, const double& sigma,
		const int& T, const int& jumps)
	{
		this->S = S;
		this->E = E;
		this->r = r;
		this->sigma = sigma;
		this->T = T;
		this->jumps = jumps;

		stock_tree = Eigen::MatrixXd::Zero(jumps + 1, jumps + 1);
		option_tree = Eigen::MatrixXd::Zero(jumps + 1, jumps + 1);

		dt = T / static_cast<double>(jumps);

		u = exp(sigma*sqrt(dt));
		d = exp(-sigma * sqrt(dt));
		q = (exp(r*dt) - d) / (u - d);

		payoff = new PutPayOff(E);
	}

	// Virtual destructor
	AmericanPut::~AmericanPut()
	{
		delete payoff;
	}

	// Setter methods
	void AmericanPut::setS(const double& S)
	{
		this->S = S;
	}

	void AmericanPut::setE(const double& E)
	{
		this->E = E;
	}

	void AmericanPut::setR(const double& r)
	{
		this->r = r;
	}

	void AmericanPut::setSigma(const double& sigma)
	{
		this->sigma = sigma;
	}

	void AmericanPut::setQ()
	{
		dt = T / static_cast<double>(jumps);
		u = exp(sigma*sqrt(dt));
		d = exp(-sigma * sqrt(dt));
		q = (exp(r*dt) - d) / (u - d);
	}

	void AmericanPut::setT(const int& T)
	{
		this->T = T;
	}

	void AmericanPut::setJumps(const int& jumps)
	{
		this->jumps = jumps;
	}

	void AmericanPut::setTrees()
	{
		stock_tree = Eigen::MatrixXd::Zero(jumps + 1, jumps + 1);
		option_tree = Eigen::MatrixXd::Zero(jumps + 1, jumps + 1);
	}

	// Option price
	double AmericanPut::OptionPrice()
	{
		for (int i = 0; i <= jumps; i++)
		{
			for (int j = 0; j <= i; j++)
			{
				stock_tree(j, i) = S * pow(u, i - j)*pow(d, j);
			}
		}

		for (int i = 0; i <= jumps; i++)
		{
			option_tree(i, jumps) = (*payoff)(stock_tree(i, jumps));
		}

		for (int i = jumps - 1; i >= 0; i--)
		{
			for (int j = 0; j <= i; j++)
			{
				double option_value = exp(-dt * r)*(q*option_tree(j, i + 1) + (1 - q)*option_tree(j + 1, i + 1));
				double option_payoff = (*payoff)(stock_tree(j, i));
				if (option_value < option_payoff)
				{
					option_tree(j, i) = option_payoff;
				}
				else
				{
					option_tree(j, i) = option_value;
				}
			}
		}

		return option_tree(0, 0);
	}
}