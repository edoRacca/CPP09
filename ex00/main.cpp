
#include "BitcoinExchange.hpp"

void printDb(std::string date, float value, float multiplier)
{
	std::cout  << date << " => " << value << " = " << value * multiplier << std::endl;
}

std::string extractDate(std::string date, char c)
{
	unsigned int first = date.find('-');
	unsigned int second = date.find('-', first + 1);
	if (c == 'd')
		return(date.substr(second + 1));
	if (c == 'm')
		return(date.substr(first + 1, second - first - 1));
	else
		return(date.substr(0, first));
}

int isValidDate(int y, int m, int d)
{
	if (y < 2009 || y > 2022)
		return (false);
	if (m < 1 || m > 12)
		return (false);
	if (m == 2 && (y % 400 == 0 || (y % 4 == 0 && y % 100 != 0)) && d > 29)
		return (false);
	if (m == 2 && !(y % 400 == 0 || (y % 4 == 0 && y % 100 != 0)) && d > 28)
		return (false);
	if ((m == 1 || m == 3 || m == 5 || m == 7 || m == 8 || m == 10 || m == 12) && d > 31)
		return (false);
	if ((m == 4 || m == 6 || m == 9 || m == 11) && d > 31)
		return (false);
	return (true);
}

int dateDiff(std::string date1, std::string date2)
{
	unsigned int y1 = std::atoi(extractDate(date1, 'y').c_str());
	unsigned int m1 = std::atoi(extractDate(date1, 'm').c_str());
	unsigned int d1 = std::atoi(extractDate(date1, 'd').c_str());
	unsigned int y2 = std::atoi(extractDate(date2, 'y').c_str());
	unsigned int m2 = std::atoi(extractDate(date2, 'm').c_str());
	unsigned int d2 = std::atoi(extractDate(date2, 'd').c_str());
	std::tm t1 = std::tm();
	std::tm t2 = std::tm();
	t1.tm_year = y1 - 1900;
	t1.tm_mon = m1 - 1;
	t1.tm_mday = d1;
	t1.tm_hour = 12;
	t2.tm_year = y2 - 1900;
	t2.tm_mon = m2 - 1;
	t2.tm_mday = d2;
	t2.tm_hour = 12;
	return (std::difftime(std::mktime(&t1), std::mktime(&t2)) / (60 * 60 * 24));
}

std::string checkClosestDate(BitcoinExchange& b, std::string date)
{
	std::multimap<std::string, float>::iterator it = b.getDb().lower_bound(date);

	if (it == b.getDb().begin() && isValidDate(std::atoi(extractDate(date, 'y').c_str()), \
		std::atoi(extractDate(date, 'm').c_str()), std::atoi(extractDate(date, 'd').c_str())) == true)
		return (it->first);
	else if (it == b.getDb().end() && isValidDate(std::atoi(extractDate(date, 'y').c_str()), \
		std::atoi(extractDate(date, 'm').c_str()), std::atoi(extractDate(date, 'd').c_str())) == true)
		return ((--it)->first);
	else
	{
		if (isValidDate(std::atoi(extractDate(date, 'y').c_str()), \
		std::atoi(extractDate(date, 'm').c_str()), std::atoi(extractDate(date, 'd').c_str())) == false)
			return ("");
		std::multimap<std::string, float>::iterator prev = it;
		--prev;
		if (dateDiff(date, prev->first) < dateDiff(it->first, date))
			return (prev->first);
		else
			return (it->first);
	}
}

bool checkFormat(std::string line)
{
	size_t pos = line.find('|');
	if (pos == std::string::npos || line[pos - 1] != ' ' || line[pos + 1] != ' ')
	{
		std::cout << "Error: wrong date value => " << line << std::endl;
		return (false);
	}
	return (true);
}

void checkRightValues(BitcoinExchange& b, std::string closest, std::string date, std::string value)
{
	if (closest == "")
		std::cout << "Error: wrong date value => " << date << std::endl;
	else if (std::atof(value.c_str()) < 0 || std::atof(value.c_str()) > 1000)
		std::cout << "Error: wrong value passed => " << value << std::endl;
	else
		printDb(date, std::atof(value.c_str()), (b.getDb().find(closest)->second));
}

void checkBitcoinsDate(BitcoinExchange& b, std::ifstream& file)
{
	std::string		date, value, closest, line;

	while (std::getline(file, line))
	{
		if (!checkFormat(line))
			continue ;
		date = line.substr(0, line.find('|') - 1);
		value = line.substr(line.find('|') + 2);
		date.erase(std::remove(date.begin(), date.end(), ' '), date.end());
		value.erase(std::remove(value.begin(), value.end(), ' '), value.end());
		if (date == "date" || value == "value")
			continue ;
		closest = checkClosestDate(b, date);
		checkRightValues(b, closest, date, value);
	}
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
	file.close();
}