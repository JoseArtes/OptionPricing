#include "Random.h"


// Base class

// Default constructor
Random::Random()
{
}

// Destructor
Random::~Random()
{
}

// Setter methods
void Random::setUniform(const double& uniform_a, const double& uniform_b)
{
	this->uniform_a = uniform_a;
	this->uniform_b = uniform_b;
}

void Random::setNormal(const double& normal_mu, const double& normal_sigma)
{
	this->normal_mu = normal_mu;
	this->normal_sigma = normal_sigma;
}

// Number generators
double Random::Uniform() const
{
	return (uniform_b - uniform_a)*(static_cast<double>(rand()) / RAND_MAX) + uniform_a;
}

double Random::Normal() const
{
	double u1, u2, x, y, z;

	do
	{
		u1 = static_cast<double>(rand()) / RAND_MAX;
		u2 = static_cast<double>(rand()) / RAND_MAX;
		u1 = 2 * u1 - 1;
		u2 = 2 * u2 - 1;
		x = u1 * u1 + u2 * u2;
	} while (x > 1);

	y = sqrt((-2 * log(x)) / x);
	z = u1 * y;

	return normal_mu + normal_sigma * z;
}