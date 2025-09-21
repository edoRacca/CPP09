
#include "RPN.hpp"

RPN::RPN()
{

}

RPN::RPN(const RPN& r)
{
	this->_s = r._s;
}

RPN::~RPN()
{

}

std::stack<int> RPN::getStack() const
{
	return (this->_s);
}

RPN& RPN::operator=(const RPN& r)
{
	if (this != &r)
	{
		this->_s = r._s;
	}
	return (*this);
}

bool isInvalidChar(std::string& s)
{
	if (s.find('(') != std::string::npos || s.find(')') != std::string::npos || \
	s.find('{') != std::string::npos || s.find('}') != std::string::npos || \
	s.find('.') != std::string::npos)
		return (true);
	return (false);
}

void	checkValue(std::stack<int>& s, std::string val)
{
	if (val == "+" || val == "-" || val == "*" || val == "/")
	{
		if (s.size() > 1)
		{
			int val1 = s.top();
			s.pop();
			int val2 = s.top();
			s.pop();
			if (val == "+")
				s.push(val2 + val1);
			else if (val == "-")
				s.push(val2 - val1);
			else if (val == "*")
				s.push(val2 * val1);
			else
				s.push(val2 / val1);
		}
	}
	else
		s.push(std::atoi(val.c_str()));
}

void	RPN::notation(std::string expr)
{
	std::istringstream strm(expr);
	std::string val;
	while (std::getline(strm, val, ' '))
	{
		if (isInvalidChar(val))
		{
			std::cout << "Error: invalid character" << std::endl;
			return ;
		}
		checkValue(this->_s, val);
	}
	std::cout << this->_s.top() << std::endl;
}
