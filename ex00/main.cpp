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

int main(int argc, char** argv)
{
	if (argc != 2)
	{
		std::cout << "Error\nUse `./btc filename`" << std::endl;
		return 1;
	}

	std::ifstream in(argv[1]);
	
	if (in.fail())
	{
		std::cout << "Error\nCouldn't open file" << std::endl;
	}

	std::ifstream data("data.csv");
	if (data.fail())
	{
		std::cout << "Error\nCouldn't read the data set" << std::endl;
	}

	// TODO: loop through lines
	if (!checkDate(argv[1]))
	{
		std::cout << "Error\nInvalid date: "
	}
	std::cout << std::endl;

	return 0;
}
