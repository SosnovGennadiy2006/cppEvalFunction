#include "Calculator.h"

Calculator::Calculator()
{
	this->expression = "";
}

Calculator::Calculator(const std::string &exp)
{
	this->expression = exp;
}

double Calculator::Solve()
{
	return SolveFromExpression(this->expression);
}

double Calculator::SolveOperation(const std::string &s)
{
	std::string number1 = "", number2 = "";
	char _operator = 'n';
	bool flag = true;
	for (size_t i = 0; i < s.length(); i++)
	{
		if (isdigit(s[i]) || s[i] == '.')
		{
			if (flag)
			{
				number1 += s[i];
			}
			else
			{
				number2 += s[i];
			}
		}
		else if(s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i] == '/')
		{
			_operator = s[i];
			flag = false;
		}
	}

	switch (_operator)
	{
	case '+':
		return atof(number1.c_str()) + atof(number2.c_str());
	case '-':
		return atof(number1.c_str()) - atof(number2.c_str());
	case '*':
		return atof(number1.c_str()) * atof(number2.c_str());
	case '/':
		return atof(number1.c_str()) / atof(number2.c_str());
	default:
		return 0;
	}
}

double Calculator::SolveFromExpression(std::string exp)
{
	size_t pos = exp.find('^');
	while (pos != std::string::npos)
	{
		exp.replace(pos, 1, "**");
		pos = exp.find('^');
	}

	std::smatch _match;

	while (std::regex_search(exp, _match, std::regex("[(][^)(]+[)]"), \
		std::regex_constants::match_default))
	{
		std::string elem = _match.str();
		elem = elem.substr(1, elem.length() - 2);
		exp = _match.prefix().str() + \
			std::to_string(SolveFromExpression(elem)) \
			+ _match.suffix().str();
	}

	while (std::regex_search(exp, _match, \
		std::regex("([0-9]|[.])+[!]"), \
		std::regex_constants::match_default))
	{
		std::string elem = _match.str();
		double number = atof(elem.c_str());
		exp = _match.prefix().str() + \
			std::to_string(factorial(number)) \
			+ _match.suffix().str();
	}

	while (std::regex_search(exp, _match, \
		std::regex("([0-9]|[.])+[*][*]([0-9]|[.])+"), \
		std::regex_constants::match_default))
	{
		std::string elem = _match.str();
		
		std::string number1 = "", number2 = "";
		bool flag = true;
		for (auto item : elem)
		{
			if (isdigit(item) || item == '.')
			{
				if (flag)
				{
					number1 += item;
				}
				else
				{
					number2 += item;
				}
			}
			else if(item != ' ')
			{
				flag = false;
			}
		}

		exp = _match.prefix().str() + \
			std::to_string(pow(atof(number1.c_str()), atof(number2.c_str()))) \
			+ _match.suffix().str();
	}

	SolveOperators(std::string("/*"), exp);
	SolveOperators(std::string("+-"), exp);

	return atof(exp.c_str());
}

void Calculator::SolveOperators(const std::string& operators, std::string &exp)
{
	std::smatch _match;

	while (std::regex_search(exp, _match, \
		std::regex("([0-9]|[.])+[" + operators + "]([0-9]|[.])+") , \
		std::regex_constants::match_default))
	{
		std::string elem = _match.str();
		exp = _match.prefix().str() + \
			std::to_string(SolveOperation(elem)) + _match.suffix().str();
	}
}

void Calculator::setExpression(const std::string& exp)
{
	this->expression = exp;
}

std::string Calculator::getExpression() const
{
	return this->expression;
}

unsigned long long Calculator::factorial(unsigned short int number)
{
	unsigned long long Ans = 1;

	for (unsigned short int i = 1; i <= number; i++)
	{
		Ans *= i;
	}

	return Ans;
}