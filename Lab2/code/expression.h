/*************************
 * Class Expression       *
 * TNG033: Lab 2          *
 **************************/

#pragma once

#include <iostream>

constexpr double Epsilon = 1.0e-5;

class Expression {
public:
    // Destructor
    virtual ~Expression() {
        --count_expressions;
    }


    // ADD OTHER MEMBER FUNCTIONS ->

    // Function call operator (pure virtual)
    //Enables the object to act like a function f(x)
    virtual double operator()(double x) const = 0;

	// Type conversion to std::string (pure virtual)
    // Converts the object to a human-readable string
    // Example a polynomial becomes "3.40 + 5.00 * X^2"
    virtual explicit operator std::string() const = 0;

    // Check if a value is a root
    // example if (e == 5.0)
	bool isRoot(double x) const {
		return std::abs((*this)(x)) < Epsilon;
	}

    // operator<< to string
    // uses operator std::string internally
	// static_cast to convert pointer from base class to derived class
	// Example: std::cout << p1 << std::endl;
	friend std::ostream& operator<<(std::ostream& os, const Expression& e) {
        os << static_cast<std::string>(e);
		return os;
	}

	//Clone expression (pure virtual) any instance of expression
	//Allows copying an object without knowing its type
	virtual Expression* clone() const = 0;

    // Return number of existing instances of class Expression
    // Used only for debug purposes
    static std::size_t get_count_expressions();

protected:

    Expression& operator=(const Expression&) = delete;

    // Default constructor
    Expression() {
        ++count_expressions;
    }

    // Copy constructor
    Expression(const Expression&) {
        ++count_expressions;
    }

    // total number of existing expressions -- only to help to detect bugs in the code
    static std::size_t count_expressions;
    // Your code cannot manipulate this variable
};
