
#include "BitcoinExchange.hpp"

std::map<std::string, float> parseDb(std::string path)
{
	std::ifstream	file(path.c_str());
	std::string		line;
	std::map<std::string, float> ret;

	if (!file)
	{
		std::cout << "GAY 2" << std::endl;
		return (ret);
	}
	while (std::getline(file, line))
	{
		if (line == "date,exchange_rate")
			continue ;
	} 
	return (ret);
}

BitcoinExchange::BitcoinExchange(std::string path)
{
	this->_db = parseDb(path);
	if (this->_db.size() == 0)
		throw(std::runtime_error("Database doesn't exist or invalid database name"));
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& b)
{
	this->_db = b._db;
}

BitcoinExchange::~BitcoinExchange()
{

}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& b)
{
	if (this != &b)
		this->_db = b._db;
	return (*this);
}
