
#ifndef PMERGEME_HPP
# define PMERGEME_HPP

# include <iostream>
# include <string>
# include <cstdlib>
# include <vector>
# include <deque>
# include <ctime>
# include <cmath>
# include <iomanip>
# include <sys/time.h>

class PmergeMe
{
private:
	std::vector<int>	_v;
	double				_vtime;
	std::deque<int>		_d;
	double				_dtime;

public:
	PmergeMe();
	PmergeMe(const PmergeMe& p);
	~PmergeMe();

	std::vector<int> getV(void) const;
	std::deque<int> getD(void) const;
	double	getVTime() const;
	double	getDTime() const;


	bool init_values(PmergeMe& p, char **s, int size);
	int mergeInsert(char **values, int size);

	PmergeMe& operator=(const PmergeMe& p);
};


#endif