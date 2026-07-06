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

// struct pairInt
// {
// 	std::deque<int>	first;
// 	std::deque<int>	second;

// 	// pairInt() : first(-1), second(-1), isReminder(false) {};
// 	// pairInt(int a_first, int a_second, bool a_rem) : first(a_first), second(a_second), isReminder(a_rem) {};
// };


/** */
// void createPairs(const std::deque<int> &nbs, std::deque<int> &first, std::deque<int> &second)
// {
// 	// if (nbs.size() == 1)
// 	// 	return std::deque<pairInt>();

// 	std::deque<int>::const_iterator ite = nbs.end();
// 	for (std::deque<int>::const_iterator it = nbs.begin() ; it != ite ; )
// 	{
// 		first.push_back(*it);
// 		++it;
// 		if (it != ite)
// 		{
// 			second.push_back(*it);
// 			++it;
// 		}
// 		else
// 		{
// 			second.push_back(*(--first.end()));
// 			first.pop_back();
// 		}
// 	}
// }

// void findBiggest(std::deque<int> &first, std::deque<int> &second)
// {
// 	std::deque<int>::iterator site = second.end();
// 	std::deque<int>::iterator sit = second.begin();
// 	std::deque<int>::iterator fite = first.end();
// 	std::deque<int>::iterator fit = first.begin();
// 	for (; fit != fite && sit != site; ++sit, ++fit)
// 	{
// 		if (*sit > *fit)
// 			std::swap(*fit, *sit);
// 	}
// }

// void sortBiggest(std::deque<int> &first)//, std::deque<int> &second)
// {
// 	// static std::deque<int> sorted = first;
// 	std::deque<int> sf;
// 	std::deque<int> ss;

// 	createPairs(first, sf, ss);
// 	static int i =0;
// 	while (!ss.empty() && i < 10)
// 	{
// 		// std::cout << "hello" << std::endl;
// 		findBiggest(sf, ss);
// 		sortBiggest(sf); //, ss);
// 		// createPairs(sf, sf, ss);
// 		std::cout << "hello: " << *(ss.begin()) << std::endl;
// 		++i;
// 	}
// 	std::deque<int >::const_iterator ite = sf.end();
// 	std::deque<int >::const_iterator it = sf.begin(); 
// 	for (; it != ite; ++it)
// 	{
// 		std::cout << "sortBIg: " << *it << std::endl;
// 	}
// 	// first = sorted;
// }

#include <cmath>
namespace jacobsthal
{
	std::size_t getNext(std::size_t ji)
	{
		return (std::pow(2, ji) - std::pow(-1, ji)) / 3;
	}

	std::size_t getNumber(std::size_t size)
	{
		if (size == 0)
			return 0;
		if (size == 1)
			return 1;
		std::size_t ji = 1;
		std::size_t jn = getNext(ji);
		std::size_t save;
		while (jn < size)
		{
			save = jn;
			++ji;
			jn = getNext(ji);
		}
		return save;
	}
}

namespace deque
{
	typedef std::deque<unsigned int> 		u_int;
	typedef deque::u_int::const_iterator 	c_iter;
	typedef deque::u_int::iterator 			ui_iter;

	struct group
	{
		ui_iter		begin;
		std::size_t	size;

		group() : size(0) {};
	};

	typedef std::deque<group> 				pair;
	typedef deque::pair::const_iterator 	cp_iter;
	typedef deque::pair::iterator 			pair_iter;

	deque::u_int init(char *args)
	{
		deque::u_int nbs;
		std::istringstream iss(args);
		while (!iss.eof())
		{
			unsigned long val;
			iss >> val;
			if (iss.fail() || val > std::numeric_limits<unsigned int>::max())
			{
				throw std::runtime_error("Error: argument contains a none positive integer");
			}
			nbs.push_back(static_cast<unsigned int>(val));
		}
		return nbs;
	}

	deque::pair createPairs(deque::u_int& nbs, int pairSize)
	{
		deque::pair pairs;
		ui_iter ite = nbs.end();

		for (ui_iter it = nbs.begin() ; it != ite ; )
		{
			group g;
			g.begin = it;
			int tmp = pairSize; //! dont change
			while (tmp > 0)
			{
				if (it != ite)
				{
					++g.size;
					++it;
				}
				--tmp;
			}
			pairs.push_back(g);
		}
		return pairs;
	}
	
	void	swap(pair_iter it)
	{
		for (std::size_t i = 0 ; i < it->size / 2 ; ++i)
		{
			std::swap(*(it->begin + i), *((it->begin + i) + (it->size / 2)));
		}

	}

	void findBiggest(deque::pair& pairs)
	{
		pair_iter ite = pairs.end();
		pair_iter it = pairs.begin();
		// exclude the reminders
		if (it->size != (ite - 1)->size)
		{
			--ite;
		}
		for ( ; it != ite ; ++it)
		{
			if (*(it->begin) < *(it->begin + (it->size / 2)))
			{
				swap(it);
			}
		}
	}

	std::size_t	getPairsSize(const deque::pair& pairs)
	{
		cp_iter ite = pairs.end();
		cp_iter it = pairs.begin();
		// exclude the reminders
		if (it == ite - 1)
		{
			return 1;
		}
		if (it->size != (ite - 1)->size)
		{
			return (pairs.size() - 1);
		}
		return pairs.size();
	}


	std::ostream&	operator<<(std::ostream& os, const deque::pair& pairs)
	{
		cp_iter ite = pairs.end();
		cp_iter it = pairs.begin();
		for (; it != ite; ++it)
		{
			c_iter	iter = it->begin;
			os << "[";
			for (std::size_t i = 0 ; i < it->size - 1 ; ++i, ++iter)
			{
				os << *iter;
				os << ", ";
			}
			os << *iter;
			os << "]" << std::endl;
		}
		return os;
	}

	std::ostream&	operator<<(std::ostream& os, const deque::u_int& nbs)
	{
		c_iter ite = nbs.end();
		for (c_iter it = nbs.begin() ; it != ite ; ++it)
			std::cout << *it << " ";
		std::cout << std::endl;
	}

	// void	sort(deque::u_int& nbs)
	// {
	// 	static std::size_t i = 1;
	// 	while (1)//size > 1 && i < 5)
	// 	{
	// 		std::cout << "i= " << i << std::endl;
	// 		deque::pair pairs;
	// 		pairs = createPairs(nbs, i);
	// 		std::size_t size = deque::getPairsSize(pairs);
	// 		std::cout << "size= " << size << std::endl;
	// 		std::cout << "jacobsthal= " << jacobsthal::getNumber(deque::getPairsSize(pairs)) << std::endl;
	// 		std::cout << "CREATE" << std::endl;
	// 		std::cout << pairs << std::endl;
	// 		findBiggest(pairs);
	// 		std::cout << "BIGGEST" << std::endl;
	// 		std::cout << pairs << std::endl;
	// 		++i;
	// 		if (size != 1)
	// 		{
	// 			sort(nbs);
	// 			std::cout << "END RECURSION" << std::endl;
	// 		}
	// 		std::cout << pairs << std::endl;
	// 		if (size == 1)
	// 			break ;
	// 	}
	// }

	void	sort(deque::u_int& nbs, std::size_t nbGroups)
	{
		deque::pair pairs = createPairs(nbs, nbGroups);
		std::cout << "CREATE\n"<< pairs << std::endl;
		findBiggest(pairs);
		std::cout << "BIGGEST\n" << pairs << std::endl;
		if (deque::getPairsSize(pairs) <= 1)
			return ;
		sort(nbs, nbGroups * 2);

		std::cout << "END RECURSION" << std::endl;
		// even number groups (0, 2, 4, ...) = winner
		// odd = loser
		// different size or odd total number = remainder
		/** start w/l/r */
		// deque::pair winners;
		// deque::pair losers;
		// deque::pair remainders;
		// std::size_t size = deque::getPairsSize(pairs);
		// if (pairs[0].size != pairs[size - 1].size)
		// 	--size;
		// if (size % 2 != 0)
		// 	--size;
		// std::size_t i = 0;
		// std::cout << "size pairs= " << size << std::endl;
		// for ( ; i < size ; ++i)
		// {
		// 	winners.push_back(pairs[i]);
		// 	++i;
		// 	losers.push_back(pairs[i]);
		// }
		// while (i < deque::getPairsSize(pairs))
		// {
		// 	remainders.push_back(pairs[i]);
		// 	++i;
		// }
		// std::cout << "before:" << std::endl;
		// std::cout << "W= " << winners << std::endl;
		// std::cout << "L= " << losers << std::endl;
		// std::cout << "R=" << remainders << std::endl;
		// std::cout << "size= " << getPairsSize(winners) << std::endl;
		// std::cout << "jacobsthal= " << jacobsthal::getNumber(deque::getPairsSize(losers)) << std::endl;
		// //! indices
		// // i = 0;
		// // for ( ; i < size ; ++i)
		// // {
		// // 	if (*(winners[i].begin) > *(losers[i].begin))
		// // 	{
		// // 		std::swap(winners[i].begin, losers[i].begin);
		// // 	}
		// // 	winners.push_back(losers[i]);
		// // 	losers.pop_back(); // TODO: probably need iterator cause that wont work
		// // }
		// //! iterators
		// pair_iter w_ite = winners.end();
		// pair_iter w_it = winners.begin();
		// // pair_iter l_ite = losers.end();
		// pair_iter l_it = losers.begin();
		// for ( ; w_it != w_ite ; ++w_it)
		// {
		// 	// pair_iter l_ite = losers.end();
		// 	if (*(w_it->begin) > *(l_it->begin))
		// 	{
		// 		std::swap(w_it->begin, l_it->begin);
		// 	}
		// 	winners.push_back(*l_it);
		// 	losers.pop_front(); // erase(l_it);
		// 	l_it = losers.begin();
		// }
		// std::cout << "after:" << std::endl;
		// std::cout << "W= " << winners << std::endl;
		// std::cout << "L= " << losers << std::endl;
		// std::cout << "R=" << remainders << std::endl;
		/** end */
		
		/** start with same list pairs */

		// std::size_t size = deque::getPairsSize(pairs);
		// if (pairs[0].size != pairs[size - 1].size)
		// 	--size;
		// if (size % 2 != 0)
		// 	--size;
		// std::size_t i = 0;
		// std::cout << "size pairs= " << size << std::endl;
		// for ( ; i < size ; ++i)
		// {
		// 	std::cout << "main" << pairs.begin() + i << std::endl;
		// 	++i;
		// 	std::cout << "pending" << pairs.begin() + i << std::endl;
		// }
		// while (i < deque::getPairsSize(pairs))
		// {
		// 	std::cout << "remainder" << pairs.begin() + i << std::endl;
		// 	++i;
		// }
		// std::cout << "before:" << std::endl;
		// std::cout << "main= "; << main << std::endl;
		// std::cout << "pending= " << pending << std::endl;
		// std::cout << "size= " << getPairsSize(pending) << std::endl;
		// std::cout << "jacobsthal= " << jacobsthal::getNumber(deque::getPairsSize(pending)) << std::endl;
		// std::cout << "after:" << std::endl;

		/** end */
		std::cout << nbs << std::endl;
		std::cout << pairs << std::endl;

		/**
		 * A0 A1 A2 A3 A4
		 * B0 B1 B2 B3 B4
		 * R0
		 * 
		 * to insert B0:
		 * find A0
		 * insert B0 before A0
		 * push everything back
		 * no insert, no erase
		 */
		/**
		 * END RECURSION
		 * grp A | grp B 
		 * [88, 7, 11, 3]
		 * [34, 9, 14, 2]
		 * [41, 6, 8, 4]
		 * remainders
		 * [85]
		 */
		/**
		 * need tmp_nbs for the main chain
		 * so no modification in nbs, so pairs are still significant
		 * 
		 */

		// deque::u_int tmp;

		// std::size_t size = deque::getPairsSize(pairs);
		// if (pairs[0].size != pairs[size - 1].size)
		// 	--size;
		// if (size % 2 != 0)
		// 	--size;
		// std::size_t i = 0;
		// for ( ; i < size ; ++i)
		// {
		// 	if (i % 2 == 0)
		// 		tmp.push_back();
		// }
		

	}

	/**
	 * 
	 * 
	 */

}

namespace timer
{
	// https://stackoverflow.com/questions/5833094/get-a-timestamp-in-c-in-microseconds
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


// TODO:
/**
 * add recursion
 * find stop condition for it //? maybe when nbGroup == 1
 * add jacobsthal number to the insertion
 */
int main(int argc, char **argv)
{
	deque::u_int	nbs;
	if (argc != 2 || argv[1][0] == 0)
	{
		std::cerr << "Error: usage './PmergeMe \"<positive integers>\"'" << std::endl;
		return 1;
	}
	try
	{
		nbs = deque::init(argv[1]);
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what() << std::endl;
		return 1;
	}

	//! ./PmergeMe "14 2 9 34 3 11 88 7 41 6 8 4 85"
	//! ./PmergeMe "18 75 5 0 100 20 91 3 34 88 2 8 1 11 7 62 4 16 9 4 41 14 6 25"


	// deque::pair pairs = deque::createPairs(nbs, std::pow(2, 1)); //! power, so here "1", is recursion level
	// std::cout << "size= " << deque::getPairsSize(pairs) << std::endl;
	// std::cout << "jacobsthal= " << jacobsthal::getNumber(deque::getPairsSize(pairs)) << std::endl;
	// std::cout << pairs << std::endl;
	// deque::findBiggest(pairs);
	// std::cout << pairs << std::endl;
	unsigned long base = timer::start();
	deque::sort(nbs, 2);
	std::cout << timer::stop(base) << "us" << std::endl;
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


