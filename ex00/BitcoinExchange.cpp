
#include "BitcoinExchange.hpp"

void easyPrintDb(std::multimap<std::string, float> m)
{
	for (std::multimap<std::string, float>::iterator it = m.begin(); it != m.end(); ++it)
	{
		std::cout << std::fixed << std::setprecision(2) << it->first << " -> " << it->second << std::endl;
	}
}

std::multimap<std::string, float> parseDb(std::string path)
{
	std::ifstream	file(path.c_str());
	std::string		date, value;
	std::multimap<std::string, float> ret;

	if (!file)
		return (ret);
	while (std::getline(file, date, ','))
	{
		std::getline(file, value);
		if (date == "date" || value == "exchange_rate")
			continue ;
		ret.insert(std::pair<std::string, float>(date, std::atof(value.c_str())));
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

std::multimap<std::string, float>& BitcoinExchange::getDb(void)
{
	return (this->_db);
}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& b)
{
	if (this != &b)
		this->_db = b._db;
	return (*this);
}
