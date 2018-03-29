#include "NormalCDF.h"

// Parameterised constructor
NormalCDF::NormalCDF(const double& x)
{
	this->x = x;
}

// Destructor
NormalCDF::~NormalCDF()
{
}

// Setter method
void NormalCDF::setX(const double& x)
{
	this->x = x;
}

// N(0,1) CDF calculation
double NormalCDF::Calculate() const
{
	double b1, b2, b3, b4, b5;
	double p, c;

	b1 = 0.319381530;
	b2 = -0.356563782;
	b3 = 1.781477937;
	b4 = -1.821255978;
	b5 = 1.330274429;
	p = 0.2316419;
	c = log(sqrt(2*pi));

	double a, t, s, y;

	a = fabs(x);
	t = 1 / (1 + a * p);
	s = t * (b1 + t * (b2 + t * (b3 + t * (b4 + t * b5))));
	y = s * exp(-0.5*x*x - c);
	
	if (x > 0)
	{
		y = 1 - y;
	}

	return y;
}