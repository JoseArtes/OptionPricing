#ifndef RANDOM_H
#define RANDOM_H

#include<iostream>
#include<cmath>
#include<ctime>
#include<random>

class Random
{
private:
	double uniform_a, uniform_b; // U(a,b) parameters
	double normal_mu, normal_sigma; // N(mu,sigma) parameters

public:
	// Default constructor
	Random();

	// Destructor
	~Random();

	// Setter methods
	void setUniform(const double& uniform_a, const double& uniform_b);
	void setNormal(const double& normal_mu, const double& normal_sigma);

	// Number generators
	double Uniform() const;
	double Normal() const;
};


#endif