#include  "PayOff.h"

// Base class:

// Default constructor
PayOff::PayOff()
{
}

// Virtual destructor
PayOff::~PayOff()
{
}

// Derived class 1 (Call):

// Parameterised constructor
CallPayOff::CallPayOff(const double& E)
{
	this->E = E;
}

// Virtual destructor
CallPayOff::~CallPayOff()
{
}

// Virtual functor
double CallPayOff::operator()(const double& S) const
{
	return max(S - E, 0.0);
}

// Derived class 2 (Put):

// Parameterised constructor
PutPayOff::PutPayOff(const double& E)
{
	this->E = E;
}

// Virtual destructor
PutPayOff::~PutPayOff()
{
}

// Virtual functor
double PutPayOff::operator()(const double& S) const
{
	return max(E - S, 0.0);
}