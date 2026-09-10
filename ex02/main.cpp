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

	std::vector<unsigned int> sure;
	sure = nbs_v;
	std::sort(sure.begin(),sure.end());

	/** std::deque */
	std::cout << "DEQUE" << std::endl;
	std::cout << "Before: " << nbs_d << std::endl;

	unsigned long base_d = timer::start();
	std::deque<unsigned int> sorted_d = pmerge.sort(nbs_d);
	unsigned long stop_d = timer::stop(base_d);

	std::cout << "After: " << sorted_d << std::endl;
	std::cout << "Time: " << stop_d << "us" << std::endl;

	bool isSorted = true;
	for (std::size_t i = 0 ; i < sure.size() ; ++i)
	{
		if (sure[i] != sorted_d[i])
		{
			isSorted = false;
			break ;
		}
	}
	std::cout << std::boolalpha << "Check sorted: " << isSorted << std::endl;
	
	/** std::vector */
	std::cout << "\nVECTOR" << std::endl;
	std::cout << "Before: " << nbs_v << std::endl;

	unsigned long base_v = timer::start();
	std::vector<unsigned int> sorted_v = pmerge.sort(nbs_v);
	unsigned long stop_v = timer::stop(base_v);

	std::cout << "After: " << sorted_v << std::endl;
	std::cout << "Time: " << stop_v << "us" << std::endl;
	isSorted = true;

	for (std::size_t i = 0 ; i < sure.size() ; ++i)
	{
		if (sure[i] != sorted_v[i])
		{
			isSorted = false;
			break ;
		}
	}
	std::cout << std::boolalpha << "Check sorted: " << isSorted << std::endl;

	return 0;
}