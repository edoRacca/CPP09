
#include "PmergeMe.hpp"


int main(int ac, char **av)
{
	if (ac < 2)
		return (std::cerr << "Invalid arguments number" << std::endl, 1);
	PmergeMe p;

	p.mergeInsert(&av[1], ac - 1);
}