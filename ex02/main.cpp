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
	// std::size_t getPrevious(std::size_t ji)
	// {
	// 	// return (std::pow(2, ji) - std::pow(-1, ji)) / 3;
	// }

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
	// typedef std::deque<unsigned int> 					u_int;
	// typedef std::deque<unsigned int>::const_iterator 	c_iter;
	// typedef std::deque<unsigned int>::iterator 			ui_iter;

	struct group
	{
		std::deque<unsigned int>::iterator		begin;
		std::size_t	size;

		group() : size(0) {};
	};

	// typedef std::deque<group> 					pair;
	// typedef std::deque<group>::const_iterator 	cp_iter;
	// typedef std::deque<group>::iterator 		pair_iter;

	std::deque<unsigned int> init(char **args, int nb_args)
	{
		std::deque<unsigned int> nbs;

		for (int i = 1 ; i < nb_args ; ++i)
		{
			std::istringstream iss(args[i]);
			if (args[i][0] == 0)
				continue ;
			while (!iss.eof())
			{
				unsigned long val;
				iss >> val;
				if (iss.fail() || val > std::numeric_limits<unsigned int>::max())
				{
					throw std::runtime_error("Error: argument must be a positive integer (not `" + iss.str() + "`)");
				}
				if (nbs.empty())
					nbs.push_back(static_cast<unsigned int>(val));
				else if (std::find(nbs.begin(), nbs.end(), static_cast<unsigned int>(val)) == nbs.end())
				{
					nbs.push_back(static_cast<unsigned int>(val));
				}
				else
				{
					std::cout << "Warning: duplicate (" << static_cast<unsigned int>(val) << "), only one occurence added to the list to be sorted" << std::endl;
				}
			}
		}
		return nbs;
	}

	std::deque<group> initPairs(std::deque<unsigned int>& nbs)
	{
		std::deque<group> pairs;
		std::deque<unsigned int>::iterator ite = nbs.end();

		for (std::deque<unsigned int>::iterator it = nbs.begin() ; it != ite ; )
		{
			group g;
			g.begin = it;
			int tmp = 2;
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
	
	void	swap(std::deque<group>::iterator it)
	{
		for (std::size_t i = 0 ; i < it->size / 2 ; ++i)
		{
			std::swap(*(it->begin + i), *((it->begin + i) + (it->size / 2)));
		}

	}

	void findBiggest(std::deque<group>& pairs)
	{
		std::deque<group>::iterator ite = pairs.end();
		std::deque<group>::iterator it = pairs.begin();
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

	std::size_t	getPairsSize(const std::deque<group>& pairs)
	{
		std::deque<group>::const_iterator ite = pairs.end();
		std::deque<group>::const_iterator it = pairs.begin();
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


	std::ostream&	operator<<(std::ostream& os, const std::deque<group>& pairs)
	{
		std::deque<group>::const_iterator ite = pairs.end();
		std::deque<group>::const_iterator it = pairs.begin();
		for (; it != ite; ++it)
		{
			std::deque<unsigned int>::const_iterator	iter = it->begin;
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

	std::ostream&	operator<<(std::ostream& os, const std::deque<unsigned int>& nbs)
	{
		std::deque<unsigned int>::const_iterator ite = nbs.end();
		for (std::deque<unsigned int>::const_iterator it = nbs.begin() ; it != ite ; ++it)
			os << *it << " ";
		return os;
	}

	std::deque<group> createPairs(const std::deque<group>& pairs)
	{
		std::deque<group> newPairs;
		std::size_t i = 0;
		for ( ; i + 1 < pairs.size() ; i += 2)
		{
			group g;

			g.begin = pairs[i].begin;
			g.size = pairs[i].size + pairs[i + 1].size;

			newPairs.push_back(g);
		}
		
		if (i < pairs.size())
			newPairs.push_back(pairs[i]);

		return newPairs;
	}

	void	insertPending(std::deque<std::size_t>& order, std::deque<unsigned int>& main, std::deque<unsigned int>& pending)
	{
		for (std::deque<std::size_t>::const_iterator it = order.begin() ; it != order.end() ; ++it)
		{
			std::size_t i = *it;
			std::deque<unsigned int>::iterator start = main.begin() + i;
			std::deque<unsigned int>::iterator end = std::lower_bound(main.begin(), start, pending[i]);
			main.insert(end, pending[i]);
		}	
	}

	void	sort(std::deque<group>& pairs)
	{
		std::cout << "CREATE\n"<< pairs << std::endl;
		findBiggest(pairs);
		std::cout << "BIGGEST\n" << pairs << std::endl;
		if (deque::getPairsSize(pairs) <= 1)
			return ;
		if (deque::getPairsSize(pairs) == 2)
		{
			if (*(pairs[0].begin) > *(pairs[1].begin))
				std::swap(pairs[0], pairs[1]);

			return;
		}
		
		if (deque::getPairsSize(pairs) <= 1)
			return ;


		std::deque<group> newPairs = createPairs(pairs);
		sort(newPairs);

		// TODO: jaco
		// TODO: insert

		/** order order winner winner */

		std::cout << "END RECURSION" << std::endl;

		std::cout << pairs << std::endl;
	}

	void	sort(std::deque<unsigned int>& nbs)
	{
		std::deque<group> pairs = deque::initPairs(nbs);
		sort(pairs);

		std::deque<unsigned int> main;
		std::deque<unsigned int> pending;

		for(std::size_t i = 0; i < pairs.size(); ++i)
		{
			main.push_back(*pairs[i].begin);
			if (pairs[i].size >= 2)
				pending.push_back(*(pairs[i].begin + 1));
		}

		if (!pairs.empty())
		{
			std::deque<group>::iterator it = pairs.end() - 1;
			pending.push_back(*it->begin);
		}


	}


	// /**
	//  * 
	//  * 
	//  */

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
	std::deque<unsigned int>	nbs;
	if (argc < 2 || (argc == 2 && argv[1][0] == 0))
	{
		std::cerr << "Error: usage `./PmergeMe <positive integers>`" << std::endl;
		return 1;
	}
	try
	{
		nbs = deque::init(argv, argc);
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what() << std::endl;
		return 1;
	}

	unsigned long base = timer::start();
	
	// std::deque<group> pairs = deque::initPairs(nbs);
	deque::sort(nbs);
	std::cout << timer::stop(base) << "us" << std::endl;
	return 0;
}