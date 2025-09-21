
# include "RPN.hpp"

int main(int ac, char **av)
{
	if (ac != 2)
		return (std::cerr << "Wrong number of arguments" << std::endl, 1);
	std::string arg = av[1];
	if (arg == "")
		return (std::cerr << "Empty input string" << std::endl, 1);
	RPN s;
	s.notation(av[1]);
}