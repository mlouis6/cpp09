#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange()
{

}

// BitcoinExchange::BitcoinExchange(const char* filename) : m_filename(filename)
// {

// }

// BitcoinExchange::BitcoinExchange(BitcoinExchange& other)
// {
// 	static_cast<void> (other);
// }

// BitcoinExchange& BitcoinExchange::operator=(BitcoinExchange& other)
// {
// 	static_cast<void> (other);
// }

BitcoinExchange::~BitcoinExchange()
{

}

bool	BitcoinExchange::checkDate(const std::string& date)
{
	struct tm	t = {};
	int	y, m, d;
	std::istringstream iss(date);
	char del1, del2;
	if (!(iss >> y >> del1 >> m >> del2 >> d))
	{
		return false;
	}
	if (del1 != '-' || del2 != '-') // || y < 2008) //TODO: minimum date
	{
		return false;
	}
	t.tm_year = y - 1900;
	t.tm_mon = m - 1;
	t.tm_mday = d;
	
	time_t norm = mktime(&t);
	struct tm *cmp = localtime(&norm);
	return (cmp->tm_year == y - 1900 &&
			cmp->tm_mon == m - 1 &&
			cmp->tm_mday == d);
}

std::string	BitcoinExchange::trim(const std::string& str)
{
	std::size_t begin = str.find_first_not_of(" \t\n\v\f\r");
	if (begin == std::string::npos)
		return "";
	std::size_t end = str.find_last_not_of(" \t\n\v\f\r");
	
	return str.substr(begin, end - begin + 1);
}

// TODO: check missing delimiter
bool	BitcoinExchange::checkFirstLine(const std::string& line, const std::string& col1, const std::string& col2, const char del)
{
	std::size_t	pos = line.find(del);

	std::string sub = line.substr(0, pos );
	sub = trim(sub);
	if (sub != col1)
	{
		std::cout << "Error\nFirst column should be '"<< col1 <<"' instead of '" << sub << "'" << std::endl;
		return false;
	}
	sub = line.substr(pos + 1);
	sub = trim(sub);
	if (sub != col2)
	{
		std::cout << "Error\nSecond column should be '" << col2 <<"' instead of '" << sub << "'" << std::endl;
		return false;
	}

	return true;
}

// TODO: check missing delimiter
bool	BitcoinExchange::checkLine(const std::string& line, const char del, const double max, pair& data)
{
	std::size_t	pos = line.find(del);

	std::string sub = line.substr(0, pos);
	sub = trim(sub);
	if (!checkDate(sub))
	{
		std::cout << "Error\nInvalid date: " << sub << std::endl;
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
		std::cout << "Error\nInvalid rate: " << sub << std::endl;
		return false;
	}
	data.second = static_cast<float> (rate);
	return true;
}


// TODO: refacto
// TODO: use exception
int BitcoinExchange::bitcoinCheck(const char* filename)
{
	std::ifstream in_data("data.csv");
	if (in_data.fail())
	{
		std::cout << "Error\nCouldn't read the data set" << std::endl;
		return 1;
	}

	std::string	line;
	std::getline(in_data, line);
	if (!checkFirstLine(line, "date", "exchange_rate", ','))
	{
		std::cout << "Error\n`data.csv` first line shouldn't be: " << line << std::endl;
		return 1;
	}
	
	std::map<std::string, float>	data;
	while (std::getline(in_data, line))
	{
		pair	ret;
		if (!checkLine(line, ',', std::numeric_limits<float>::max(), ret))
		{
			return 1;
		}
		// TODO: check double
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
		std::cout << "Error\nCouldn't open file" << std::endl;
		return 1;
	}
	std::getline(in, line);
	if (!checkFirstLine(line, "date", "value", '|'))
	{
		std::cout << "Error\n`" << filename << "` first line shouldn't be: " << line << std::endl;
		return 1;
	}
	
	while (std::getline(in, line))
	{
		pair	ret;
		if (checkLine(line, '|', 1000, ret))
		{
			// TODO: the code (not nemo)
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
					// TODO: check date before 1900
					std::cout << "No data old enough for " << ret.first << std::endl;
				}
			}
		}
	}
	
	std::cout << std::endl;

	return 0;
}

