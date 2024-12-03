/*************************
 * Class Logarithm        *
 * TNG033: Lab 2          *
 **************************/

#pragma once

#include <iostream>
#include <vector>
#include "expression.h"

class Logarithm : public Expression {
protected:
	double c1, c2;
	int base;

	Expression* E;


public:
	//------------Phase 10-----------


	//Default contructor
	Logarithm();

	~Logarithm();

	//		Virtual things (expression.h)
	double operator()(double x) const override;

	operator std::string() const override;

	Logarithm* clone() const override;
	
	Logarithm(Expression& Express, double fC, double sC, int logBase);

	//------------------------------



};
