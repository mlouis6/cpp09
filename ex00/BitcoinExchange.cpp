#include "BitcoinExchange.hpp"
#include <exception>
#include <cstring>

BitcoinExchange::BitcoinExchange()
{

}

BitcoinExchange::~BitcoinExchange()
{

}

bool	BitcoinExchange::checkDate(const std::string& date)
{
	struct tm	t;
	std::memset(&t, 0, sizeof(t));
	int	y, m, d;
	std::istringstream iss(date);
	char del1, del2;
	if (!(iss >> y >> del1 >> m >> del2 >> d))
	{
		return false;
	}
	if (del1 != '-' || del2 != '-')
	{
		return false;
	}
	char extra;
	if (iss >> extra)
	{
		return false;
	}
	t.tm_year = y - 1900;
	t.tm_mon = m - 1;
	t.tm_mday = d;
	
	mktime(&t);
	return (t.tm_year == y - 1900 &&
			t.tm_mon == m - 1 &&
			t.tm_mday == d);
}

std::string	BitcoinExchange::trim(const std::string& str)
{
	size_t begin = str.find_first_not_of(" \t\n\v\f\r");
	if (begin == std::string::npos)
		return "";
	size_t end = str.find_last_not_of(" \t\n\v\f\r");
	
	return str.substr(begin, end - begin + 1);
}

bool	BitcoinExchange::checkFirstLine(const std::string& line, const std::string& col1, const std::string& col2, const char del)
{
	size_t	pos = line.find(del);

	if (pos == std::string::npos)
	{
		throw std::runtime_error("Error: Missing delimiter");
	}
	std::string sub = line.substr(0, pos );
	sub = trim(sub);
	if (sub != col1)
	{
		std::string msg = "Error: First column should be '" + col1 + "' instead of '" + sub + "'";
		throw std::runtime_error(msg);
	}
	sub = line.substr(pos + 1);
	sub = trim(sub);
	if (sub != col2)
	{
		std::string msg = "Error: Second column should be '" + col2 + "' instead of '" + sub + "'";
		throw std::runtime_error(msg);
	}

	return true;
}

bool	BitcoinExchange::checkLine(const std::string& line, const char del, const double max, pair& data)
{
	size_t	pos = line.find(del);

	std::string sub = line.substr(0, pos);
	sub = trim(sub);
	if (!checkDate(sub))
	{
		std::cout << "Error: invalid date => " << sub << std::endl;
		return false;
	}
	data.first = sub;
	sub = line.substr(pos + 1);
	sub = trim(sub);
	std::istringstream iss(sub);
	double	rate;
	iss >> rate;
	if (!iss.eof() || iss.fail() || rate < 0 || rate > max)
	{
		std::cout << "Error: invalid rate => " << sub << std::endl;
		return false;
	}
	data.second = static_cast<float> (rate);
	return true;
}

int BitcoinExchange::bitcoinCheck(const char* filename)
{
	std::ifstream in_data("data.csv");
	if (in_data.fail())
	{
		throw std::runtime_error("Error: Couldn't read the data set");
	}

	std::string	line;
	std::getline(in_data, line);
	if (!checkFirstLine(line, "date", "exchange_rate", ','))
	{
		throw std::runtime_error("Error: `data.csv` first line shouldn't be: " + line);
	}
	
	std::map<std::string, float>	data;
	while (std::getline(in_data, line))
	{
		pair	ret;
		if (!checkLine(line, ',', std::numeric_limits<float>::max(), ret))
		{
			return 1;
		}
		std::map<std::string, float>::const_iterator it = data.find(ret.first);
		if (it != data.end())
		{
			std::cout << "Warning: '" << ret.first;
			std::cout << "' appears multiple times in dataset, first occurence (";
			std::cout << data[ret.first] << ") is the one saved." << std::endl;
		}
		data.insert(ret);
	}

	std::ifstream in(filename);
	
	if (in.fail())
	{
		throw std::runtime_error("Error: Couldn't open file");
	}
	std::getline(in, line);
	if (!checkFirstLine(line, "date", "value", '|'))
	{
		std::string msg = "Error: `" + std::string(filename) + "` first line shouldn't be: " + std::string(line);
		throw std::runtime_error(msg);
	}
	
	while (std::getline(in, line))
	{
		pair	ret;
		if (checkLine(line, '|', 1000, ret))
		{
			std::map<std::string, float>::const_iterator it = data.find(ret.first);
			if (it != data.end())
			{
				std::cout << ret.first << " => " << ret.second;
				std::cout << " = " << ret.second * data[ret.first] << std::endl;
			}
			else
			{
				it = data.upper_bound(ret.first);
				if (it != data.begin())
				{
					--it;
					std::cout << ret.first << " => " << ret.second;
					std::cout << " = " << ret.second * it->second << std::endl;
				}
				else
				{
					std::cout << "No data old enough for " << ret.first << std::endl;
				}
			}
		}
	}
	
	std::cout << std::endl;

	return 0;
}
