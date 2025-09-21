
#ifndef PMERGEME_HPP
# define PMERGEME_HPP

# include <iostream>
# include <string>
# include <cstdlib>
# include <vector>
# include <deque>
# include <ctime>

class PmergeMe
{
private:
	std::vector<int>	_v;
	size_t				_vtime;
	std::deque<int>		_d;
	size_t				_dtime;

public:
	PmergeMe();
	PmergeMe(const PmergeMe& p);
	~PmergeMe();

	std::vector<int> getV(void) const;
	std::deque<int> getD(void) const;

	int mergeInsert(char **values, int size);

	PmergeMe& operator=(const PmergeMe& p);
};


#endif