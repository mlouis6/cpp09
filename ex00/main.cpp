#include <iostream>
#include <fstream>
#include <string>

#include <ctime>
#include <sstream>
#include <map>
#include <limits>
#include <utility>
bool	checkDate(std::string date)
{
	struct tm	t = {};
	int	y, m, d;
	std::istringstream iss(date);
	char del1, del2;
	if (!(iss >> y >> del1 >> m >> del2 >> d))
	{
		return false;
	}
	if (del1 != '-' || del2 != '-' || y < 2008) //TODO: minimum date
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

std::string	trim(const std::string& str)
{
	size_t begin = str.find_first_not_of(" \t\n\v\f\r");
	if (begin == std::string::npos)
		return "";
	size_t end = str.find_last_not_of(" \t\n\v\f\r");
	
	return str.substr(begin, end - begin + 1);
}

bool	checkFirstLine(std::string line, std::string col1, std::string col2, char del)
{
	size_t	pos = line.find(del);

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
// struct	pair
// {
// 	std::string	date;
// 	float		val;
// };

typedef std::pair<std::string, float> pair;

bool	checkLine(std::string line, char del, double max, pair& data)
{
	size_t	pos = line.find(del);

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

int main(int argc, char** argv)
{
	if (argc != 2)
	{
		std::cout << "Error\nUse `./btc filename`" << std::endl;
		return 1;
	}




	std::ifstream in_data("data.csv");
	if (in_data.fail())
	{
		std::cout << "Error\nCouldn't read the data set" << std::endl;
		return 1;
	}
	std::string						line;
	std::getline(in_data, line);
	if (!checkFirstLine(line, "date", "exchange_rate", ','))
	{
		std::cout << "LINE= " << line << std::endl;
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
		data[ret.first] = ret.second;
	}


	std::ifstream in(argv[1]);
	
	if (in.fail())
	{
		std::cout << "Error\nCouldn't open file" << std::endl;
		return 1;
	}
	std::getline(in, line);
	if (!checkFirstLine(line, "date", "value", '|'))
	{
		std::cout << "LINE= " << line << std::endl;
		return 1;
	}
	
	while (std::getline(in, line))
	{
		pair	ret;
		if (checkLine(line, '|', 1000, ret))
		{
			// TODO: the code (not nemo)
		}
	}
	
	// TODO: loop through lines
	// if (!checkDate(argv[1]))
	// {
	// 	std::cout << "Error\nInvalid date: " << argv[1] << std::endl;
	// 	return 1;
	// }
	// checkFirstLine(std::string(argv[1]), ',');
	std::cout << std::endl;

	return 0;
}


/**

you have to create a program which outputs the value of a certain amount of bitcoin
on a certain date.
This program must use a database in csv format which will represent bitcoin price
over time. This database is provided with this subject.
The program will take as input a second database, storing the different prices/dates
to evaluate.
Your program must respect these rules:
• The program name is btc.
• Your program must take a file as an argument.
• Each line in this file must use the following format: "date | value".
• A valid date will always be in the following format: Year-Month-Day.
• A valid value must be either a float or a positive integer, between 0 and 1000.


Your program will use the value in your input file.
Your program should display on the standard output the result of the value multiplied
by the exchange rate according to the date indicated in your database.

If the date used in the input does not exist in your DB then you
must use the closest date contained in your DB. Be careful to use the
lower date and not the upper one.

 */
