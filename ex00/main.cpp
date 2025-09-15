
#include "BitcoinExchange.hpp"


int main(int ac, char **av)
{
	std::ifstream file;

	if (ac != 2)
		return (std::cout << "Error: could not open file." << std::endl, 1);
	file.open(av[1]);
	if (!file)
		return (std::cout << "Error: could not open file." << std::endl, 1);
	try
	{
		BitcoinExchange b("data.csv");
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	
		
}