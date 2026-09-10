#include <iostream>
#include "BitcoinExchange.hpp"
#include <exception>

int main(int argc, char** argv)
{
	if (argc != 2)
	{
		std::cout << "Error: Use `./btc filename`" << std::endl;
		return 1;
	}
	try
	{
		BitcoinExchange::bitcoinCheck(argv[1]);
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}

	return 0;
}
