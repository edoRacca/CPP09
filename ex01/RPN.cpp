
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

void	RPN::notation(std::string expr)
{
	std::istringstream strm(expr);
	std::string val;
	while (std::getline(strm, val, ' '))
	{
		if (isInvalidChar(val))
		{
			std::cout << "Error" << std::endl;
			return ;
		}
	}
}