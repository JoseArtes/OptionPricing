#ifndef NORMALCDF_H
#define NORMALCDF_H

#include<iostream>
#include<cmath>

using namespace std;

class NormalCDF
{
private:
	double x;
public:
	// Parameterised constructor
	NormalCDF(const double& x);

	// Destructor
	~NormalCDF();
	
	// Setter method
	void setX(const double& x);

	// CDF
	double Calculate() const;
	
	// Pi
	const double pi = 4 * atan(1.0);
};

#endif