#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <string>
#include <regex>
#include <iostream>

class Calculator
{
private:
	std::string expression;
	void SolveOperators(const std::string& operators, std::string &exp);
	double SolveOperation(const std::string &s);
public:
	Calculator();
	Calculator(const std::string &exp);

	double Solve();
	double SolveFromExpression(std::string exp);
	void setExpression(const std::string &exp);
	std::string getExpression() const;
	unsigned long long factorial(unsigned short int number);
};

#endif // !CALCULATOR_H

