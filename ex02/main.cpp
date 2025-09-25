
#include "PmergeMe.hpp"

template <typename T> 
void printContainer(T v, std::string prefix, int size)
{
	std::cout << prefix;
	for (int i = 0; i < size; i++)
		std::cout << v[i] << (i != size - 1 ? " " : "");
	std::cout << std::endl;
}

int main(int ac, char **av)
{
	if (ac < 2)
		return (std::cerr << "Invalid arguments number" << std::endl, 1);
	PmergeMe p;
	printContainer(&av[1], "Before:\t", ac - 1);
	p.mergeInsert(&av[1], ac - 1);
	printContainer(p.getV(), "After:\t", (int)p.getV().size());
}