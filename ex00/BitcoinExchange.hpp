
#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

# include <iostream>
# include <cstdlib>
# include <fstream>
# include <string>
# include <map>

class BitcoinExchange
{
private:
	std::map<std::string, float> _db;

public:
	BitcoinExchange(std::string path);
	BitcoinExchange(const BitcoinExchange& b);
	~BitcoinExchange();

	BitcoinExchange& operator=(const BitcoinExchange& b);
};



#endif