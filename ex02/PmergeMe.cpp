
#include "PmergeMe.hpp"

PmergeMe::PmergeMe()
{
	this->_vtime = 0;
	this->_dtime = 0;
}

PmergeMe::PmergeMe(const PmergeMe& p)
{
	this->_v = p._v;
	this->_d = p._d;
	this->_vtime = p._vtime;
	this->_dtime = p._dtime;
}

PmergeMe::~PmergeMe()
{

}

std::vector<int> PmergeMe::getV(void) const
{
	return (this->_v);
}

std::deque<int> PmergeMe::getD(void) const
{
	return (this->_d);
}

bool isDigitStr(std::string s)
{
	for (size_t i = 0; i < s.size(); i++)
		if (std::isdigit(s[i]) == 0)
			return (false);
	return (true);
}

bool PmergeMe::init_values(PmergeMe& p, char **s, int size)
{
	for (int i = 0; i < size; i++)
	{
		if (std::atoi(s[i]) < 0 || !isDigitStr(s[i]))
			return (false);
		p._v.push_back(std::atoi(s[i]));
		p._d.push_back(std::atoi(s[i]));
	}
	return (true);
}


int PmergeMe::mergeInsert(char **values, int size)
{
	if (!init_values(*this, values, size))
		return (std::cerr << "Error\n", 1);
	std::vector<std::pair<int,int>> block;
	std::vector<int> leftovers;
	for (size_t i = 0; i + 1 < this->_v.size(); i += 2)
	{
		if (this->_v[i] > this->_v[i + 1])
			block.push_back(std::make_pair(this->_v[i + 1], this->_v[i]));
		else
			block.push_back(std::make_pair(this->_v[i], this->_v[i + 1]));
	}
	if (this->_v.size() % 2 == 1)
		leftovers.push_back(this->_v[this->_v.size() - 1]);
	
	return (0);
}

PmergeMe& PmergeMe::operator=(const PmergeMe& p)
{
	if (this != &p)
	{
		this->_v = p._v;
		this->_d = p._d;
		this->_vtime = p._vtime;
		this->_dtime = p._dtime;
	}
	return (*this);
}
