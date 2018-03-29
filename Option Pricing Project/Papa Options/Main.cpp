#include "PayOff.h"
#include "Random.h"
#include "MonteCarlo.h"
#include "BlackScholes.h"
#include "Binomial.h"

int main()
{
	srand(static_cast<unsigned>(time(NULL)));

	double S, E, r, sigma;
	int T, jumps, sims;

	cout << "S:       ";
	cin >> S;
	cout << "E:       ";
	cin >> E;
	cout << "r:       ";
	cin >> r;
	cout << "sigma:   ";
	cin >> sigma;
	cout << "T:       ";
	cin >> T;
	cout << "jumps:   ";
	cin >> jumps;
	cout << "sims:    ";
	cin >> sims;

	cout << endl;

	MonteCarlo::MonteCarlo* montecarlo1 = new MonteCarlo::EuropeanCall(S, E, r, sigma, T, jumps, sims);
	MonteCarlo::MonteCarlo* montecarlo2 = new MonteCarlo::EuropeanPut(S, E, r, sigma, T, jumps, sims);
	MonteCarlo::MonteCarlo* montecarlo3 = new MonteCarlo::ArthAsianCall(S, E, r, sigma, T, jumps, sims);
	MonteCarlo::MonteCarlo* montecarlo4 = new MonteCarlo::ArthAsianPut(S, E, r, sigma, T, jumps, sims);
	MonteCarlo::MonteCarlo* montecarlo5 = new MonteCarlo::GeomAsianCall(S, E, r, sigma, T, jumps, sims);
	MonteCarlo::MonteCarlo* montecarlo6 = new MonteCarlo::GeomAsianPut(S, E, r, sigma, T, jumps, sims);

	BlackScholes::BlackScholes* blackscholes1 = new BlackScholes::EuropeanCall(S, E, r, sigma, T);
	BlackScholes::BlackScholes* blackscholes2 = new BlackScholes::EuropeanPut(S, E, r, sigma, T);

	Binomial::Binomial* binomial1 = new Binomial::EuropeanCall(S, E, r, sigma, T, jumps);
	Binomial::Binomial* binomial2 = new Binomial::EuropeanPut(S, E, r, sigma, T, jumps);
	Binomial::Binomial* binomial3 = new Binomial::AmericanCall(S, E, r, sigma, T, jumps);
	Binomial::Binomial* binomial4 = new Binomial::AmericanPut(S, E, r, sigma, T, jumps);

	cout << "American call price (Binomial):                         " << binomial3->OptionPrice() << endl;
	cout << "American put price (Binomial):                          " << binomial4->OptionPrice() << endl << endl;

	cout << "Asian arithmetic call price (Monte Carlo):              " << montecarlo3->OptionPrice() << endl;
	cout << "Asian arithmetic put price (Monte Carlo):               " << montecarlo4->OptionPrice() << endl;
	cout << "Asian geometric call price (Monte Carlo):               " << montecarlo5->OptionPrice() << endl;
	cout << "Asian geometric put price (Monte Carlo):                " << montecarlo6->OptionPrice() << endl << endl;

	cout << "European call price (Monte Carlo):                      " << montecarlo1->OptionPrice() << endl;
	cout << "European put price (Monte Carlo):                       " << montecarlo2->OptionPrice() << endl;
	cout << "European call price (Black-Scholes):                    " << blackscholes1->OptionPrice() << endl;
	cout << "European put price (Black-Scholes):                     " << blackscholes2->OptionPrice() << endl;
	cout << "European call price (Binomial):                         " << binomial1->OptionPrice() << endl;
	cout << "European put price (Binomial):                          " << binomial2->OptionPrice() << endl << endl;

	MonteCarlo::EuropeanCall call1(S, E, r, sigma, T, jumps, sims);
	MonteCarlo::EuropeanPut call2(S, E, r, sigma, T, jumps, sims);

	cout << "Greeks (European call): " << endl;
	cout << "Delta:                                                  " << call1.Delta() << endl;
	cout << "Gamma:                                                  " << call1.Gamma() << endl;
	cout << "Vega:                                                   " << call1.Vega() << endl;
	cout << "Theta:                                                  " << call1.Theta() << endl;
	cout << "Rho:                                                    " << call1.Rho() << endl << endl;

	cout << "Greeks (European put): " << endl;
	cout << "Delta:                                                  " << call2.Delta() << endl;
	cout << "Gamma:                                                  " << call2.Gamma() << endl;
	cout << "Vega:                                                   " << call2.Vega() << endl;
	cout << "Theta:                                                  " << call2.Theta() << endl;
	cout << "Rho:                                                    " << call2.Rho() << endl << endl;

	delete montecarlo1, montecarlo2, montecarlo3, montecarlo4, montecarlo5, montecarlo6;
	delete blackscholes1, blackscholes2;
	delete binomial1, binomial2, binomial3, binomial4;

	char fin;
	cin >> fin;

	return 0;
}