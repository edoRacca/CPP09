
#include "BitcoinExchange.hpp"

void printDb(std::map<std::string, float> m)
{
	for (std::map<std::string, float>::iterator it = m.begin(); it != m.end(); ++it)
	{
		std::cout << std::fixed << std::setprecision(2) << it->first << " -> " << it->second << std::endl;
	}
}

std::map<std::string, float> parseInputFile(std::ifstream& file)
{
	std::string		date, value;
	std::map<std::string, float> ret;

	if (!file)
		return (ret);
	while (std::getline(file, date, '|'))
	{
		date.erase(std::remove(date.begin(), date.end(), ' '), date.end());
		std::getline(file, value);
		value.erase(std::remove(value.begin(), value.end(), ' '), value.end());
		if (date == "date" || value == "value")
			continue ;
		// ret[date] = std::atof(value.c_str());
		std::cout << "[" << date << "]" << std::endl;
		std::cout << "{" << value << "}" << std::endl;
	}
	// i valori vengono sovrascritti perche le date qui sono uguali, forse meglio non usare map?
	// printDb(ret);
	return (ret);
}

void checkBitcoinsDate(BitcoinExchange& b, std::ifstream& file)
{
	std::map<std::string, float> parse = parseInputFile(file);
// 	for (std::map<std::string, float>::iterator it = parse.begin(); it != parse.end(); ++it)
// 	{
// 		std::string year, month, day;
// 
	// }
	(void)b;
}

int main(int ac, char **av)
{
	std::ifstream file;

	if (ac != 2)
		return (std::cout << "Error: input file doesn't exist." << std::endl, 1);
	file.open(av[1]);
	if (!file)
		return (file.close(), std::cout << "Error: could not open file." << std::endl, 1);
	try
	{
		BitcoinExchange b("data.csv");
		checkBitcoinsDate(b, file);
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
}