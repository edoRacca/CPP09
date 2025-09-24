
#ifndef PMERGEME_HPP
# define PMERGEME_HPP

# include <iostream>
# include <string>
# include <cstdlib>
# include <vector>
# include <deque>
# include <ctime>
# include <cmath>

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

	void printV(std::vector<int>& v, std::string prefix);
	bool init_values(PmergeMe& p, char **s, int size);
	int mergeInsert(char **values, int size);

	PmergeMe& operator=(const PmergeMe& p);
};


#endif