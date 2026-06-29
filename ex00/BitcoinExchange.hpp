#ifndef BITCOIN_EXCHANGE_HPP
# define BITCOIN_EXCHANGE_HPP

#include <iostream>
#include <fstream>
#include <string>

#include <ctime>
#include <sstream>
#include <map>
#include <limits>
#include <utility>

typedef std::pair<std::string, float> pair;

class BitcoinExchange
{
	public:
		BitcoinExchange();
		// BitcoinExchange(const char *filename);
		~BitcoinExchange();

		static int bitcoinCheck(const char* filename);

	private:
		static bool	checkDate(const std::string& date);
		static std::string	trim(const std::string& str);
		static bool	checkFirstLine(const std::string& line, const std::string& col1, const std::string& col2, const char del);
		static bool	checkLine(const std::string& line, const char del, const double max, pair& data);
		
		// const char*	m_filename;
		BitcoinExchange(BitcoinExchange& other);
		BitcoinExchange& operator=(BitcoinExchange& other);
};

#endif
