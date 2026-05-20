#include <iostream>
#include <fstream>
#include <string>

#include <ctime>
#include <sstream>

bool	checkDate(std::string date)
{
	struct tm	t = {};
	int	y, m, d;
	std::istringstream is(date);
	char del;
	is >> y >> del >> m >> del >> d;
	// TODO: maybe check for before btc date and after today
	t.tm_year = y - 1900;
	t.tm_mon = m - 1;
	t.tm_mday = d;
	
	time_t norm = mktime(&t);
	struct tm *cmp = localtime(&norm);
	return (cmp->tm_year == y - 1900 &&
			cmp->tm_mon == m - 1 &&
			cmp->tm_mday == d);
}

std::string	trim(const std::string& str)
{
	size_t begin = str.find_first_not_of(" \t\n\v\f\r");
	if (begin == std::string::npos)
		return "";
	size_t end = str.find_last_not_of(" \t\n\v\f\r");
	
	return str.substr(begin, end - begin + 1);
}

bool	checkFirstLine(std::string line, char del)
{
	size_t	pos = line.find(del);

	std::string sub = line.substr(0, pos );
	sub = trim(sub);
	if (sub != "date")
	{
		std::cout << "Error\nFirst column should be 'date'" << std::endl;
		return false;
	}
	sub = line.substr(pos + 1);
	sub = trim(sub);
	if (sub != "exchange_rate")
	{
		std::cout << "Error\nSecond column should be 'exchange_rate'" << std::endl;
		return false;
	}

	return true;
}

bool	checkLine(std::string line, char del)
{
	size_t	pos = line.find(del);

	std::string sub = line.substr(0, pos);
	sub = trim(sub);
	if (checkDate(sub))
	{
		std::cout << "Error\nInvalid date: " << sub << std::endl;
		return false;
	}
	sub = line.substr(pos + 1);
	sub = trim(sub);
	std::istringstream iss(sub);
	double	rate;
	iss >> rate;
	char	cmp;
	iss >> cmp;
	if (cmp != 0) // TODO: check if something nan
	{
		std::cout << "Error\nInvalid rate: " << sub << std::endl;
		return false;
	}

	return true;
}

int main(int argc, char** argv)
{
	if (argc != 2)
	{
		std::cout << "Error\nUse `./btc filename`" << std::endl;
		return 1;
	}

	// std::ifstream in(argv[1]);
	
	// if (in.fail())
	// {
	// 	std::cout << "Error\nCouldn't open file" << std::endl;
	// 	return 1;
	// }

	// std::ifstream data("data.csv");
	// if (data.fail())
	// {
	// 	std::cout << "Error\nCouldn't read the data set" << std::endl;
	// 	return 1;
	// }

	
	// TODO: loop through lines
	// if (!checkDate(argv[1]))
	// {
	// 	std::cout << "Error\nInvalid date: " << argv[1] << std::endl;
	// 	return 1;
	// }
	checkFirstLine(std::string(argv[1]), ',');
	std::cout << std::endl;

	return 0;
}
