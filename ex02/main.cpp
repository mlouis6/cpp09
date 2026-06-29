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

struct pairInt
{
	std::deque<int>	first;
	std::deque<int>	second;

	// pairInt() : first(-1), second(-1), isReminder(false) {};
	// pairInt(int a_first, int a_second, bool a_rem) : first(a_first), second(a_second), isReminder(a_rem) {};
};

/** */
void createPairs(const std::deque<int> &nbs, std::deque<int> &first, std::deque<int> &second)
{
	// if (nbs.size() == 1)
	// 	return std::deque<pairInt>();

	std::deque<int>::const_iterator ite = nbs.end();
	for (std::deque<int>::const_iterator it = nbs.begin() ; it != ite ; )
	{
		first.push_back(*it);
		++it;
		if (it != ite)
		{
			second.push_back(*it);
			++it;
		}
		else
		{
			second.push_back(*(--first.end()));
			first.pop_back();
		}
	}
}

void findBiggest(std::deque<int> &first, std::deque<int> &second)
{
	std::deque<int>::iterator site = second.end();
	std::deque<int>::iterator sit = second.begin();
	std::deque<int>::iterator fite = first.end();
	std::deque<int>::iterator fit = first.begin();
	for (; fit != fite && sit != site; ++sit, ++fit)
	{
		if (*sit > *fit)
			std::swap(*fit, *sit);
	}
}

void sortBiggest(std::deque<int> &first)//, std::deque<int> &second)
{
	// static std::deque<int> sorted = first;
	std::deque<int> sf;
	std::deque<int> ss;

	createPairs(first, sf, ss);
	static int i =0;
	while (!ss.empty() && i < 10)
	{
		// std::cout << "hello" << std::endl;
		findBiggest(sf, ss);
		sortBiggest(sf); //, ss);
		// createPairs(sf, sf, ss);
		std::cout << "hello: " << *(ss.begin()) << std::endl;
		++i;
	}
	std::deque<int >::const_iterator ite = sf.end();
	std::deque<int >::const_iterator it = sf.begin(); 
	for (; it != ite; ++it)
	{
		std::cout << "sortBIg: " << *it << std::endl;
	}
	// first = sorted;
}


// TODO: change to unsigned
std::deque<int> initDeque(char *args)
{
	std::deque<int> nbs;
	std::istringstream iss(args);
	while (!iss.eof())
	{
		long val;
		iss >> val;
		if (iss.fail() || val < 0 || val > std::numeric_limits<int>::max())
		{
			throw std::runtime_error("Error: argument contains a none positive integer");
		}
		nbs.push_back(static_cast<int>(val));
	}
	return nbs;
}

// https://stackoverflow.com/questions/5833094/get-a-timestamp-in-c-in-microseconds
unsigned long	startTimer()
{
	struct timeval tv;
	gettimeofday(&tv, 0);
	return 1000000 * tv.tv_sec + tv.tv_usec;
}

unsigned long	endTimer(unsigned long start)
{
	struct timeval tv;
	gettimeofday(&tv, 0);
	return (1000000 * tv.tv_sec + tv.tv_usec) - start;
}

int main(int argc, char **argv)
{
	std::deque<int>	nbs;
	if (argc != 2 || argv[1][0] == 0)
	{
		std::cerr << "Error: usage './PmergeMe \"<positive integers>\"'" << std::endl;
		return 1;
	}
	try
	{
		nbs = initDeque(argv[1]);
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what() << std::endl;
	}

	//! ./PmergeMe "14 2 9 34 3 11 88 7 41 6 8 4 85"

	std::deque<int> first;
	std::deque<int> second;
	createPairs(nbs, first, second);
	findBiggest(first, second);
	sortBiggest(first);

	std::deque<int >::const_iterator fite = first.end();
	std::deque<int >::const_iterator fit = first.begin();
	std::deque<int >::const_iterator site = second.end();
	std::deque<int >::const_iterator sit = second.begin(); ; 
	for (; sit != site; ++sit)
	{
		std::cout << "[";
		if (fit != fite)
		{
			std::cout << *fit;
			++fit;
		}
		std::cout << ", ";
			std::cout << *sit;
		std::cout << "]" << std::endl;
	}

	return 0;
}

/**
Group the elements of X into ⌊ n / 2 ⌋ pairs of elements, arbitrarily, leaving one element unpaired if there is an odd number of elements.
Perform ⌊ n / 2 ⌋ comparisons, one per pair, to determine the larger of the two elements in each pair.
Recursively sort the ⌊ n / 2 ⌋ larger elements from each pair, creating a sorted sequence S of ⌊ n / 2 ⌋ of the input elements, in ascending order, using the merge-insertion sort.
Insert at the start of S the element that was paired with the first and smallest element of S.
Insert the remaining ⌈ n / 2 ⌉ − 1  elements of X ∖ S into S, one at a time, with a specially chosen insertion ordering described below. Use binary search in subsequences of S(as described below) to determine the position at which each element should be inserted.
 */

/**
Your program must be able to use a positive integer sequence as an argument.

Your program must use the merge-insert sort algorithm to sort the positive integer
sequence.

To clarify, yes, you need to use the Ford-Johnson algorithm.

You must use at least two different containers in your code to
validate this exercise. Your program must be able to handle at
least 3000 different integers.

It is strongly advised to implement your algorithm for each container
and thus to avoid using a generic function.

Here are some additional guidelines on the information you should display line by line
on the standard output:
• On the first line you must display an explicit text followed by the unsorted positive
integer sequence.
• On the second line you must display an explicit text followed by the sorted positive
integer sequence.
• On the third line, you must display an explicit message indicating the time taken
by your algorithm, specifying the first container used to sort the positive integer
sequence.
• On the last line you must display an explicit text indicating the time used by
your algorithm by specifying the second container used to sort the positive integer
sequence.
The format for the display of the time used to carry out your sorting
is free but the precision chosen must allow to clearly see the
difference between the two containers used.
*/

/**
 * Ford-Johnson algorithm
 * (or merge-insertion sort)
 * algorithm with the fewer comparisons than most
 *
 * on an input X of n elements:
 * 1. divide into pairs (if odd elements, one left alone)
 * 2. compair the number in the pair to determine the biggest of the two
 * 3. recursively sort largest elements of each pair
 */


