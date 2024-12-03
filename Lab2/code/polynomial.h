/*************************
 * Class Polynomial       *
 * TNG033: Lab 2          *
 **************************/

#pragma once

#include <iostream>
#include <vector>
#include <sstream>

#include "expression.h"

class Polynomial : public Expression {
private:
	// Represent a polynomial of degree, first element konstant, second first degree etc.
	std::vector<double> coefficients;
public:
	Polynomial();


	//deconstructor
	//dont need to implement it because vector
	~Polynomial() = default;

	//constructor vector v{2.2, 4.4, 2.0}; Polynomial q{ v };
	// create poly.  q = 2.2 + 4.4x + 2x
	Polynomial(const std::vector<double>& coeffs);

	// Converstion contructor representing a constant polynomial
	Polynomial(double c);

	// Copy contructor
	Polynomial(const Polynomial& p) = default;

	// Assignment operator
	Polynomial& operator=(const Polynomial& p);

	// Evaluate the polynomial at x
	double operator()(double x) const override;


	// add and assign operator (operator+=)
	// p1 += p2
	Polynomial& operator+=(const Polynomial& p);

	// add and assign operator (operator+=) for constant
	Polynomial& operator+=(double c);

	// Addition operator (+) for two polynomial
	Polynomial operator+(const Polynomial& p) const;

	Polynomial operator+(double c) const;

	// Friend function for double + Polynomial
	friend Polynomial operator+(double c, const Polynomial& p);

	// Type conversion to std::string
	explicit operator std::string() const override;

	Polynomial* clone() const override;

	// Subscript operator: Access or modify coefficients
	double& operator[](size_t index);
	const double& operator[](size_t index) const;


};

/*
 * std::vector should be used to store polinomial's coefficients
 */