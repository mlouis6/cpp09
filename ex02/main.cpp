#include <iostream>
#include <sstream>
#include <limits>
#include <vector>
#include <exception>
#include <utility>
#include <deque>
#include <iterator>
#include <algorithm>
#include <sys/time.h>
#include <cmath>

#include "PmergeMe.hpp"


namespace timer
{
	unsigned long	start()
	{
		struct timeval tv;
		gettimeofday(&tv, 0);
		return 1000000 * tv.tv_sec + tv.tv_usec;
	}

	unsigned long	stop(unsigned long start)
	{
		struct timeval tv;
		gettimeofday(&tv, 0);
		return (1000000 * tv.tv_sec + tv.tv_usec) - start;
	}
}

int main(int argc, char **argv)
{
	PmergeMe pmerge;

	std::deque<unsigned int>	nbs_d;
	std::vector<unsigned int>	nbs_v;
	if (argc < 2)
	{
		std::cerr << "Error: usage `./PmergeMe <positive integers>`" << std::endl;
		return 1;
	}
	try
	{
		nbs_d = pmerge.initD(argv, argc);
		nbs_v = pmerge.initV(argv, argc);
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what() << std::endl;
		return 1;
	}

	std::cout << "DEQUE" << std::endl;
	unsigned long base_d = timer::start();
	pmerge.sort(nbs_d);
	std::cout << timer::stop(base_d) << "us" << std::endl;
	
	std::cout << "\nVECTOR" << std::endl;
	unsigned long base_v = timer::start();
	pmerge.sort(nbs_v);
	std::cout << timer::stop(base_v) << "us" << std::endl;
	return 0;
}