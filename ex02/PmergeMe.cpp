
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

double	PmergeMe::getVTime() const
{
	return (this->_vtime);
}

double	PmergeMe::getDTime() const
{
	return (this->_dtime);
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

std::vector<int> jacobsthalSequenceV(int index)
{
	std::vector<int> ret;
	ret.push_back(0);
	ret.push_back(1);
	while (ret[(int)ret.size() - 1] < index)
		ret.push_back(ret[(int)ret.size() - 1] + 2 * ret[(int)ret.size() - 2]);
	return (ret);
}

std::vector<int> jacobsthalOrderV(int index)
{
	std::vector<int> jacob = jacobsthalSequenceV(index);
	std::vector<int> jorder;
	for (int i = 2; i < (int)jacob.size(); i++)
	{
		int start = std::min(index, jacob[i - 1] + 1);
		int end = std::min(index, jacob[i]);
		for (int j = end; j >= start; j--)
			jorder.push_back(j);
		if (end == index)
			break ;
	}
	return (jorder);
}


std::vector<int> fordJohnsonAlgorithmV(std::vector<int>& v)
{
	if ((int)v.size() < 2)
		return (v);
	std::vector<int> big, small;
	for(int i = 0; i + 1 < (int)v.size(); i += 2)
	{
		if (v[i] < v[i + 1])
		{
			big.push_back(v[i + 1]);
			small.push_back(v[i]);
		}
		else
		{
			small.push_back(v[i + 1]);
			big.push_back(v[i]);
		}
	}
	if ((int)v.size() %  2 == 1)
		small.push_back(v[v.size() - 1]);
	big = fordJohnsonAlgorithmV(big);
	if (!small.empty())
	{
		std::vector<int>::iterator index = std::lower_bound(big.begin(), big.end(), small[0]);
		big.insert(index, small[0]);
	}
	if ((int)small.size() > 0)
	{
		std::vector<int> jorder = jacobsthalOrderV((int)small.size());
		for (int i = 0; i < (int)jorder.size(); i++)
		{
			int idx = jorder[i];
			int s = small[idx - 1];
			std::vector<int>::iterator index = std::lower_bound(big.begin(), big.end(), s);
			big.insert(index, s);
		}
	}
	return (big);
}

std::deque<int> jacobsthalSequenceD(int index)
{
	std::deque<int> ret;
	ret.push_back(0);
	ret.push_back(1);
	while (ret[(int)ret.size() - 1] < index)
		ret.push_back(ret[(int)ret.size() - 1] + 2 * ret[(int)ret.size() - 2]);
	return (ret);
}

std::deque<int> jacobsthalOrderD(int index)
{
	std::deque<int> jacob = jacobsthalSequenceD(index);
	std::deque<int> jorder;
	for (int i = 2; i < (int)jacob.size(); i++)
	{
		int start = std::min(index, jacob[i - 1] + 1);
		int end = std::min(index, jacob[i]);
		for (int j = end; j >= start; j--)
			jorder.push_back(j);
		if (end == index)
			break ;
	}
	return (jorder);
}


std::deque<int> fordJohnsonAlgorithmD(std::deque<int>& v)
{
	if ((int)v.size() < 2)
		return (v);
	std::deque<int> big, small;
	for(int i = 0; i + 1 < (int)v.size(); i += 2)
	{
		if (v[i] < v[i + 1])
		{
			big.push_back(v[i + 1]);
			small.push_back(v[i]);
		}
		else
		{
			small.push_back(v[i + 1]);
			big.push_back(v[i]);
		}
	}
	if ((int)v.size() %  2 == 1)
		small.push_back(v[v.size() - 1]);
	big = fordJohnsonAlgorithmD(big);
	if (!small.empty())
	{
		std::deque<int>::iterator index = std::lower_bound(big.begin(), big.end(), small[0]);
		big.insert(index, small[0]);
	}
	if ((int)small.size() > 0)
	{
		std::deque<int> jorder = jacobsthalOrderD((int)small.size());
		for (int i = 0; i < (int)jorder.size(); i++)
		{
			int idx = jorder[i];
			int s = small[idx - 1];
			std::deque<int>::iterator index = std::lower_bound(big.begin(), big.end(), s);
			big.insert(index, s);
		}
	}
	return (big);
}

int PmergeMe::mergeInsert(char **values, int size)
{
	if (!init_values(*this, values, size))
		return (std::cerr << "Error\n", 1);
	struct timeval timev1, timev2;
	gettimeofday(&timev1, NULL);
	this->_v = fordJohnsonAlgorithmV(this->_v);
	gettimeofday(&timev2, NULL);
	this->_vtime = (double)(((long long)timev2.tv_sec * 1000000 + timev2.tv_usec) - ((long long)timev1.tv_sec * 1000000 + timev1.tv_usec)) / 1000;
	std::cout << std::fixed << std::setprecision(5) << "Duration: " << this->_vtime << std::endl;
	this->_d = fordJohnsonAlgorithmD(this->_d);
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
