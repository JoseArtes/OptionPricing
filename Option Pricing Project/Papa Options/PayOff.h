#ifndef PAYOFF_H
#define PAYOFF_H

#include<iostream>
#include<algorithm>
#include<cmath>

using namespace std;

// Base class:
class PayOff
{
protected:
	double E; // Strike price

public:
	// Default constructor
	PayOff();

	// Virtual destructor
	virtual ~PayOff();

	// Pure virtual functor
	virtual double operator()(const double& S) const = 0;
};

// Derived class 1 (Call):
class CallPayOff : public PayOff
{
public:
	// Parameterised constructor
	CallPayOff(const double& E);

	// Virtual destructor
	virtual ~CallPayOff();

	// Virtual functor
	virtual double operator()(const double& S) const;
};

// Derived class 2 (Put):
class PutPayOff : public PayOff
{
public:
	// Parameterised constructor
	PutPayOff(const double& E);

	// Virtual destructor
	virtual ~PutPayOff();

	// Virtual functor
	virtual double operator()(const double& S) const;
};

#endif