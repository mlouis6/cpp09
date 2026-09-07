#include "PmergeMe.hpp"

PmergeMe::PmergeMe()
{

}

PmergeMe::PmergeMe(PmergeMe& other)
{
	static_cast<void>(other);
}

PmergeMe& PmergeMe::operator=(PmergeMe& other)
{
	static_cast<void>(other);
	return *this;
}

PmergeMe::~PmergeMe()
{

}

namespace jacobsthal
{
	// std::size_t getNext(std::size_t ji)
	// {
	// 	return (std::pow(2, ji) - std::pow(-1, ji)) / 3;
	// }

	std::size_t getNumber(std::size_t size)
	{
		if (size == 0)
			return 0;
		if (size == 1)
			return 1;
		std::size_t ji = 0;
		std::size_t save = 1;
		for (std::size_t i = 2 ; i <= size ; ++i)
		{
			std::size_t jn = save + 2 * ji;
			ji = save;
			save = jn;
		}
		return save;
	}

	// template <typename std::deque<std::size_t>>
	std::deque<std::size_t> getOrder(std::size_t size)
	{
		std::deque<std::size_t> j_order;
		std::size_t j_prev = 1;

		if (size > 1)
			j_order.push_back(1);

		for (std::size_t i = 3 ;  ; ++i)
		{	
			std::size_t j_curr = getNumber(i);

			if (j_prev >= size - 1)
				break ;

			std::size_t end = std::min(j_curr, size - 1);

			for (std::size_t j = end ; j > j_prev ; --j)
			{
					j_order.push_back(j);
			}
			j_prev = end;
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

std::deque<unsigned int> PmergeMe::sortFJ(const std::deque<Pair>& pairs)
{
	if (pairs.size() <= 1)
	{
		std::deque<unsigned int> ret;
		for (std::size_t i = 0 ; i < pairs.size() ; ++i)
			ret.push_back(pairs[i].winner);
		return ret;
	}

	std::deque<Pair> newPairs;
	std::size_t size = pairs.size();
	bool hasRemainder = false;
	unsigned int remainder;
	if (size % 2 != 0)
	{
		--size;
		hasRemainder = true;
		remainder = pairs[size].winner;
	}

	for (std::size_t i = 0 ; i < size ; i += 2)
	{
		Pair p;
		if (pairs[i].winner > pairs[i + 1].winner)
		{
			p.winner = pairs[i].winner;
			p.loser = pairs[i + 1].winner;
		}
		else
		{
			p.winner = pairs[i + 1].winner;
			p.loser = pairs[i].winner;
		}
		newPairs.push_back(p);
	}

	std::deque<unsigned int> pairs2 = sortFJ(newPairs);

	std::cout << "pairs" << std::endl;
	std::cout << pairs << std::endl;
	std::cout << "newPairs" << std::endl;
	std::cout << newPairs << std::endl;
	std::cout << "size" << std::endl;
	std::cout << newPairs.size() << std::endl;


	std::deque<unsigned int> res;
	std::deque<unsigned int> main;
	std::deque<unsigned int> pending;
	for (std::size_t i = 0 ; i < newPairs.size() ; ++i)
	{
		main.push_back(newPairs[i].winner);
		res.push_back(newPairs[i].winner);
		pending.push_back(newPairs[i].loser);
	}
	if (hasRemainder)
	{
		pending.push_back(remainder); 
	}
	
	res.push_front(newPairs[0].loser);

	std::deque<size_t> order = jacobsthal::getOrder(newPairs.size());
	
	std::cout << "order" << std::endl;
	std::cout << order << std::endl;

	if (order[0] == 1)
		order.pop_front();

	while (!order.empty())
	{
		std::deque<unsigned int>::iterator pos = lower_bound(res.begin(), res.begin() + order[0], pending[order[0]]);
		res.insert(pos, pending[order[0]]);

		order.pop_front();
	}

	if (hasRemainder)
	{
		std::deque<unsigned int>::iterator pos = lower_bound(res.begin(), res.end(), remainder);
		res.insert(pos, remainder);
	}

	std::cout << "main" << std::endl;
	std::cout << main << std::endl;
	std::cout << "pending" << std::endl;
	std::cout << pending << std::endl;
	std::cout << "res" << std::endl;
	std::cout << res << std::endl;

	return res;
}

// TODO: change to non-void
void PmergeMe::sort(std::deque<unsigned int>& nbs)
{
	if (nbs.size() <= 1)
		return ;

	std::deque<Pair> pairs;
	std::size_t size = nbs.size();
	// bool hasRemainder = false;
	// unsigned int remainder;
	if (nbs.size() % 2 != 0)
	{
		--size;
		// hasRemainder = true;
		// remainder = nbs[size];
	}

	for (std::size_t i = 0 ; i < size ; i += 2)
	{
		Pair p;
		if (nbs[i] > nbs[i + 1])
		{
			p.winner = nbs[i];
			p.loser = nbs[i + 1];
		}
		else
		{
			p.winner = nbs[i + 1];
			p.loser = nbs[i];
		}
		pairs.push_back(p);
	}

	std::deque<unsigned int> sorted = sortFJ(pairs);

	std::cout << "\nSORT\nnbs" << std::endl;
	std::cout << nbs << std::endl;

	std::cout << "sorted" << std::endl;
	std::cout << sorted << std::endl;
}

template <typename T>
std::ostream&	operator<<(std::ostream& os, const std::deque<T>& nbs)
{
	if (nbs.empty())
		return os;
	for (std::size_t i = 0 ; i + 1 < nbs.size(); ++i)
	{
		os << nbs[i] << ", ";
	}
	os << nbs[nbs.size() - 1];

	return os;
}

// std::ostream&	operator<<(std::ostream& os, const std::deque<Pending>& pending)
// {
// 	for (std::size_t i = 0 ; i < pending.size(); ++i)
// 	{
// 		os << pending[i].value << "(" << pending[i].index << ") ";
// 	}
// 	return os;
// }

std::ostream&	operator<<(std::ostream& os, const std::deque<Pair>& pairs)
{
	for (std::size_t i = 0 ; i < pairs.size(); ++i)
	{
		os << "[" << pairs[i].winner << ", " << pairs[i].loser << "]" << std::endl;
	}
	return os;
}
