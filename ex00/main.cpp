#include <iostream>
#include <fstream>
#include <string>

#include <ctime>
#include <sstream>

bool	checkDate(char* date)
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

bool	checkFirstLine(std::string line)
{
	size_t	posD = line.find("date") + 4;
	// TODO: check fail
	if (posD != 4)
	{
		std::cerr << "Need date" << std::endl;
		return false;
	}
	size_t	posE = line.find("exchange_rate");
	// TODO: check fail
	if (posE != posD + 1)
	{
		std::cerr << "delimiter too long" << std::endl;
		return false;
	}
	if (line[posD] != ',')
	{
		std::cerr << "CSV badly formatted" << std::endl;
		return false;
	}
	if (line[posE + std::string("exchange_rate").size()])
	{
		std::cerr << "Too many stuff" << std::endl;
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
	checkFirstLine(std::string(argv[1]));
	std::cout << std::endl;

	return 0;
}
