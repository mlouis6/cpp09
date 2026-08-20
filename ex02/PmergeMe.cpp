#include "PmergeMe.hpp"

PmergeMe::PmergeMe() : m_remainder(0), m_hasRemainder(false)
{

}

PmergeMe::PmergeMe(PmergeMe& other) :
	m_remainder(other.m_remainder),
	m_hasRemainder(other.m_hasRemainder)
{

}

PmergeMe& PmergeMe::operator=(PmergeMe& other)
{
	m_remainder = other.m_remainder;
	m_hasRemainder = other.m_hasRemainder;
	return *this;
}

PmergeMe::~PmergeMe()
{

}

// https://medium.com/@mohammad.ali.ibrahim.525/ford-johnson-algorithm-merge-insertion-4b024f0c3d42


// TODO:
// sort(vector/deque<unsigned int>& numbers)
//		 |
//		 +-- pair adjacent numbers
//		 |
//		 +-- compare each pair
//		 |	  A = larger
//		 |	  B = smaller
//		 |
//		 +-- recursively sort A's
//		 |
//		 +-- build main chain from sorted A's
//		 |
//		 +-- insert B's using Jacobsthal order
//		 |	  |
//		|	  +-- binary search
//		 |
//		 +-- insert odd remainder

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

	// template <typename std::deque<std::size_t>>
	std::deque<std::size_t> getOrder(std::size_t size)
	{
		std::deque<std::size_t> j_order;
		std::size_t prev_Jaco = 1;

		if (size > 1)
			j_order.push_back(1);

		for (std::size_t i = 3 ;  ; ++i)
		{	
			std::size_t nbJaco = getNumber(i);

			if (prev_Jaco >= size - 1)
				break ;

			std::size_t end = std::min(nbJaco, size - 1);

			for (std::size_t j = end ; j > prev_Jaco ; --j)
			{
					j_order.push_back(j);
			}
			prev_Jaco = end;
		}
		return j_order;
	}

	template <typename Container>
	Container displayOrder(const Container& c)
	{
		std::size_t i = 0;
		for ( ; i < c.size() - 1 ; ++i)
		{
			std::cout << c[i] << ", ";
		}
		std::cout << c[i] << std::endl;
	}
}

std::deque<unsigned int> PmergeMe::init(char **args, int nb_args)
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
	if (nbs.empty())
		throw std::runtime_error("Error: no arguments were passed");
	return nbs;
}

std::deque<Pair> PmergeMe::initPairs(std::deque<unsigned int>& nbs)
{
	std::size_t size = nbs.size();
	std::deque<Pair> pairs;

	if (size % 2 != 0)
	{
		m_hasRemainder = true;
		--size;
		m_remainder = nbs[size];
	}
	for (std::size_t i = 0 ; i < size ; ++i)
	{
		Pair p;
		if (nbs[i] > nbs[i + 1])
		{
			p.first = nbs[i];
			++i;
			p.second = nbs[i];
		}
		else
		{
			p.second = nbs[i];
			++i;
			p.first = nbs[i];
		}

		pairs.push_back(p);
	}

	return pairs;
}

void PmergeMe::sort(std::deque<unsigned int>& nbs)
{
	static int level = 0;
	++level;
	std::cout << "lvlb= " << level << std::endl;

	if (nbs.size() <= 1)
		return ;

	std::deque<Pair> pairs = initPairs(nbs);

	std::deque<unsigned int> main;
	std::deque<unsigned int> pending;

	std::deque<Pair>::const_iterator ite = pairs.end();
	for (std::deque<Pair>::const_iterator it = pairs.begin() ; it != ite ; ++it)
	{
		main.push_back(it->first);
		pending.push_back(it->second);
	}
	// if (main.size() == 1)
	// {
	// 	main.push_front(pending[0]);
	// 	pending.pop_front();
	// 	return ;
	// }
	if (m_hasRemainder)
		pending.push_back(m_remainder);
	sort(main);

	std::deque<std::size_t> order = jacobsthal::getOrder(main.size());
	
	// std::deque<unsigned int> main2;
	// std::deque<unsigned int> pending2;

	// main2 = main;
	// pending2 = pending;

	// main2.push_front(pending2[0]);
	// pending2.pop_front();

	std::cout << "\nlvla= " << level << std::endl;
	--level;


	std::cout << "nbs: " << std::endl;
	std::cout << nbs << std::endl;
	std::cout << "main: " << std::endl;
	std::cout << main << std::endl;
	// std::cout << "main2: " << std::endl;
	// std::cout << main2 << std::endl;
	std::cout << "pend: " << std::endl;
	std::cout << pending << std::endl;
	// std::cout << "pend2: " << std::endl;
	// std::cout << pending2 << std::endl;

	
	

	// std::deque<Pair> np = nextLevelPairs(pairs);
	// sort(np);
}

std::ostream&	operator<<(std::ostream& os, const std::deque<unsigned int>& nbs)
{
	for (std::size_t i = 0 ; i < nbs.size() - 1; ++i)
	{
		os << nbs[i] << ", ";
	}
	os << nbs[nbs.size() - 1];

	return os;
}

std::ostream&	operator<<(std::ostream& os, const std::deque<Pair>& pairs)
{
	for (std::size_t i = 0 ; i < pairs.size(); ++i)
	{
		os << "[" << pairs[i].first << ", " << pairs[i].second << "]" << std::endl;
	}
	return os;
}
