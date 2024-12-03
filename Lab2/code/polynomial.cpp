/*********************************************************
 * Class Polynomial member functions implementation       *
 * TNG033: Lab 2                                          *
 **********************************************************/

#include "polynomial.h"
#include <iomanip>
#include <iostream>

// ADD implementation of the member functions for class Polynomial

//constructor vector v{2.2, 4.4, 2.0}; Polynomial q{ v };
// create poly.  q = 2.2 + 4.4x + 2x
Polynomial::Polynomial(const std::vector<double>& coeffs) : coefficients{ coeffs } {}

// Converstion contructor representing a constant polynomial
Polynomial::Polynomial(double c) : coefficients{ c } {}

// Copy contructor
//Polynomial::Polynomial(const Polynomial& p) : coefficients{ p.coefficients } {}

// Assignment operator behövs inte har default
Polynomial& Polynomial::operator=(const Polynomial& p) {
	if (this != &p) {
		coefficients = p.coefficients;
	}
	return *this;
}

// Evaluate the polynomial at x
double Polynomial::operator()(double x) const {
	double result = 0.0;
	double power = 1.0;
	for (double c : coefficients) {
		result += c * power;
		power *= x;
	}
	return result;
}

// add and assign operator (operator+=)
// p1 += p2
Polynomial& Polynomial::operator+=(const Polynomial& p) {

	if (coefficients.size() < p.coefficients.size()) {
		coefficients.resize(p.coefficients.size(), 0.0);
	}
	for (size_t i = 0; i < p.coefficients.size(); i++) {
		coefficients[i] += p.coefficients[i];
	}
	return *this;
}

// add and assign operator (operator+=) for constant
Polynomial& Polynomial::operator+=(double c) {
	coefficients[0] += c;
	return *this;
}

// Addition operator (+) for two polynomial
Polynomial Polynomial::operator+(const Polynomial& p) const {
	Polynomial temp = *this;
	temp += p;
	return temp;
}

// Type conversion to std::string
Polynomial::operator std::string() const {
	std::ostringstream oss;
	oss << std::fixed << std::setprecision(2); // vill ha 6.60 inte 6.6

	bool firstTerm = true;

	for (size_t i = 0; i < coefficients.size(); ++i) {
		double coeff = coefficients[i];
		
			if (!firstTerm) {
				oss << (coeff >= 0 ? " + " : " - ");
			}
			else if (coeff < 0) {
				oss << "-";
			}

			oss << std::abs(coeff);

			if (i > 0) {
				oss << " * X";
				if (i >= 1) {
					oss << "^" << i;
				}
			}

			firstTerm = false;
		
	}

	if (firstTerm) {
		oss << "0.00";
	}
	return oss.str();
}

Polynomial* Polynomial::clone() const {
	return new Polynomial(*this); // Use copy constructor
}

// Subscript operator: Access or modify coefficients
// k = p[i]; and p[i] = k; should compile.
double& Polynomial::operator[](size_t index) {

	return coefficients[index];
}


const double& Polynomial::operator[](size_t index) const {
return coefficients.at(index); // Use at() for bounds checking
}

Polynomial Polynomial::operator+(double c) const {
	Polynomial temp{*this}; // Copy current Polynomial
	temp += c;              // Use the existing operator+= for addition
	return temp;
}

Polynomial operator+(double c, const Polynomial& p) {
	Polynomial temp = p; // Copy the Polynomial
	temp += c;           // Use the existing operator+= for addition
	return temp;
}