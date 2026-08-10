#include <iostream>
#include <exception>
#include "RPN.hpp"

int main(int argc, char** argv)
{
	if (argc != 2)
	{
		std::cerr << "Error: Usage `./RPN \"<values>\"`" << std::endl;
		return 1;
	}

	try
	{
		int res = RPN::calculate(argv[1]);
		std::cout << res << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cerr << "Error: " << e.what() << std::endl;
	}

	return 0;
}
