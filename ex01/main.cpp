#include <iostream>
#include "RPN.hpp"

int main(int argc, char** argv)
{
	if (argc != 2)
	{
		std::cerr << "Error\nMissing arguments" << std::endl;
		return 1;
	}

	RPN rpn;
	int res = rpn.calculate(argv[1]);

	rpn.err ? std::cerr << "Error" << std::endl : std::cout << res << std::endl;

	return 0;
}
