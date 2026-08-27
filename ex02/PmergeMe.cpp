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
		std::size_t save = 1;
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

void	PmergeMe::sortPairs(std::deque<Pair>& pairs)
{
	if (pairs.size() <= 1)
		return ;

	static std::deque<std::size_t> order = jacobsthal::getOrder(pairs.size());
	std::deque<unsigned int> a_deq;
	std::deque<Pair>::const_iterator ite = pairs.end();
	for (std::deque<Pair>::const_iterator it = pairs.begin() ; it != ite ; ++it)
	{
		a_deq.push_back(it->first);
	}
	pairs = initPairs(a_deq);

	PmergeMe::sortPairs(pairs);


	std::deque<unsigned int> main;
	std::deque<unsigned int> pending;
	ite = pairs.end();
	for (std::deque<Pair>::const_iterator it = pairs.begin() ; it != ite ; ++it)
	{
		main.push_back(it->first);
		pending.push_back(it->second);
	}
	if (m_hasRemainder)
		pending.push_back(m_remainder);

	if (main.size() == 1)
	{
		main.push_front(pending[0]);
		pending.pop_front();
	}
	else
	{
		std::cout << "ORDER= " << order << std::endl;
		std::size_t offset = order[0];
		std::size_t prev_os = order[0] + 1;
		while (offset > prev_os)
		{
			prev_os = offset;
			if (offset >= main.size())
				offset = main.size();
			std::deque<unsigned int>::const_iterator start = main.begin();
			std::deque<unsigned int>::const_iterator end = main.begin() + offset;
			std::deque<unsigned int>::const_iterator pos = std::lower_bound(start, end, pending[offset]);
			main.insert(pos, pending[offset]);
			order.pop_front();
			pending.erase(pending.begin() + offset);
			if (order.empty())
				break ;
			offset = order[0];
		}
	}

	std::cout << "main: " << std::endl;
	std::cout << main << std::endl;
	std::cout << "pend: " << std::endl;
	std::cout << pending << std::endl;
}

void PmergeMe::sort(std::deque<unsigned int>& nbs)
{
	if (nbs.size() <= 1)
		return ;

	m_remainder = 0;
	m_hasRemainder = false;

	std::deque<Pair> pairs = initPairs(nbs);

	sortPairs(pairs);
}

template <typename T>
std::ostream&	operator<<(std::ostream& os, const std::deque<T>& nbs)
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
