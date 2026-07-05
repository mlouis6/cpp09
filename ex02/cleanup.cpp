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

	deque::pair createPairs(deque::u_int& nbs, int recu)
	{
		deque::pair pairs;
		ui_iter ite = nbs.end();

		for (ui_iter it = nbs.begin() ; it != ite ; )
		{
			group g;
			g.begin = it;
			int tmp = recu;;
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
		deque::pair winners;
		deque::pair losers;
		deque::pair remainders;
		std::size_t size = deque::getPairsSize(pairs);
		if (pairs[0].size != pairs[size - 1].size)
			--size;
		if (size % 2 != 0)
			--size;
		std::size_t i = 0;
		std::cout << "size pairs= " << size << std::endl;
		for ( ; i < size ; ++i)
		{
			winners.push_back(pairs[i]);
			++i;
			losers.push_back(pairs[i]);
		}
		while (i < deque::getPairsSize(pairs))
		{
			remainders.push_back(pairs[i]);
			++i;
		}
		std::cout << "before:" << std::endl;
		std::cout << "W= " << winners << std::endl;
		std::cout << "L= " << losers << std::endl;
		std::cout << "R=" << remainders << std::endl;
		std::cout << "size= " << getPairsSize(winners) << std::endl;
		std::cout << "jacobsthal= " << jacobsthal::getNumber(deque::getPairsSize(losers)) << std::endl;
		pair_iter w_ite = winners.end();
		pair_iter w_it = winners.begin();
		pair_iter l_it = losers.begin();
		for ( ; w_it != w_ite ; ++w_it)
		{
			if (*(w_it->begin) > *(l_it->begin))
			{
				std::swap(w_it->begin, l_it->begin);
			}
			winners.push_back(*l_it);
			losers.pop_front();
			l_it = losers.begin();
		}
		std::cout << "after:" << std::endl;
		std::cout << "W= " << winners << std::endl;
		std::cout << "L= " << losers << std::endl;
		std::cout << "R=" << remainders << std::endl;

		std::cout << pairs << std::endl;		
	}
}

int main(int argc, char **argv)
{
	deque::u_int nbs = deque::init(argv[1]);
	deque::sort(nbs, 2);
	return 0;
}


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
	std::cout << pairs << std::endl;		
}