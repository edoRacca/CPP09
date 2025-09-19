
#ifndef RPN_HPP
# define RPN_HPP

# include <iostream>
# include <string>
# include <stack>
# include <sstream>

class RPN
{
private:
	std::stack<int> _s;

public:
	RPN();
	RPN(const RPN& r);
	~RPN();

	std::stack<int> getStack() const;

	void notation(std::string expr);

	RPN& operator=(const RPN& r);
};

#endif
