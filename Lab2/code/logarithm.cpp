/*********************************************************
 * Class Logarithm member functions implementation        *
 * TNG033: Lab 2                                          *
 **********************************************************/

#include "logarithm.h"
#include "polynomial.h"
#include <cmath>
#include <iomanip>
#include <sstream>

// ADD implementation of the member functions for class Logarithm

//---------------Phase 10-------------

//Gör en ny logatitm (default constructor)
Logarithm::Logarithm() :c1(0), c2(1), base(2) {
	std::vector<double> temp{ 0,1 };
	E = new Polynomial{ temp };
}

Logarithm::~Logarithm() {
	delete E;
	c1 = 0;
	c2 = 0;
	base = 0;
}


// double operator()(double x) const override;
//0.00 + 1.00 * Log_2( 0.00 + 1.00 * X^1 )
double Logarithm::operator()(double x) const {
	return (c1 + c2 * (log(E->operator()(x)) / log(base)));
}

//operator std::string() const override
// 0.00 + 1.00 * Log_2( 0.00 + 1.00 * X^1 )
Logarithm::operator std::string() const {
	std::ostringstream oss;
	oss << std::fixed << std::setprecision(2); // sätter 0.2 till 0.20
	oss << c1;
	oss << (c2 < 0 ? " - " : " + ");
	oss << std::abs(c2) << " * " << "Log_" << base << "( " << *E << " )";
	return oss.str();
}

//Expression* clone() const override;

Logarithm* Logarithm::clone() const {
	return new Logarithm( *this );
}

Logarithm& Logarithm::operator=(const Logarithm& L) {
	Logarithm temp{ L };
	std::swap(this->c1, temp.c1);
	std::swap(this->c2, temp.c2);
	std::swap(this->base, temp.base);
	std::swap(this->E, temp.E);
	return *this;
}

Logarithm::Logarithm(Expression& Express, double fC, double sC, int logBase) : c1( fC ), c2( sC ), base( logBase ) {
	E = Express.clone();
}

Logarithm::Logarithm(const Logarithm& L) : c1(L.c1), c2(L.c2), base(L.base) {
	E = L.E->clone();
}

int& Logarithm::set_base(int x) {
	return this->base = x;
}

//-----------------------------------