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
			int tmp = recu;
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
		std::size_t size = deque::getPairsSize(pairs);
		std::cout << "size= " << size << std::endl;
		std::cout << "jacobsthal= " << jacobsthal::getNumber(deque::getPairsSize(pairs)) << std::endl;
		std::cout << "CREATE" << std::endl;
		std::cout << pairs << std::endl;
		if (size <= 1)
			return ;
		findBiggest(pairs);
		std::cout << "BIGGEST" << std::endl;
		std::cout << pairs << std::endl;
		sort(nbs, nbGroups * 2);
		std::cout << "END RECURSION" << std::endl;
		std::cout << pairs << std::endl;
	}
}

int main(int argc, char **argv)
{
	deque::u_int	nbs;

	try
	{
		nbs = deque::init(argv[1]);
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what() << std::endl;
		return 1;
	}

	deque::sort(nbs, 2);
	return 0;
}
