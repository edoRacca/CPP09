
#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

# include <iostream>
# include <cstdlib>
# include <iomanip>
# include <fstream>
# include <string>
# include <algorithm>
# include <map>
# include <cmath>
# include <ctime>

class BitcoinExchange
{
private:
	std::map<std::string, float> _db;

public:
	BitcoinExchange(std::string path);
	BitcoinExchange(const BitcoinExchange& b);
	~BitcoinExchange();

	std::map<std::string, float>& getDb(void);

	BitcoinExchange& operator=(const BitcoinExchange& b);
};



#endif