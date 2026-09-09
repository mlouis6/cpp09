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

	std::deque<std::size_t> getOrder(std::size_t size)
	{
		std::deque<std::size_t> j_order;
		std::size_t j_prev = 1;

		for (std::size_t i = 3 ;  ; ++i)
		{	
			std::size_t j_curr = getNumber(i);

			if (j_prev >= size)
				break ;

			std::size_t end = std::min(j_curr, size);

			for (std::size_t j = end ; j > j_prev ; --j)
			{
					j_order.push_back(j);
			}
			j_prev = end;
		}
		return j_order;
	}
	
	std::vector<std::size_t> getOrder(std::size_t size)
	{
		std::vector<std::size_t> j_order;
		std::size_t j_prev = 1;

		for (std::size_t i = 3 ;  ; ++i)
		{	
			std::size_t j_curr = getNumber(i);

			if (j_prev >= size)
				break ;

			std::size_t end = std::min(j_curr, size);

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

std::deque<unsigned int> PmergeMe::sortFJ(const std::deque<unsigned int>& nbs)
{
	if (nbs.size() <= 1)
		return nbs;

	std::size_t size = nbs.size();
	bool hasRemainder = false;
	unsigned int remainder;
	if (size % 2 != 0)
	{
		--size;
		hasRemainder = true;
		remainder = nbs[size];
	}

	std::deque<Pair> pairs;
	std::deque<unsigned int> winners;
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
		winners.push_back(p.winner);
	}

	std::cout << "pairsBEFORE" << std::endl;
	std::cout << pairs << std::endl;
	std::cout << "winnersBEFORE" << std::endl;
	std::cout << winners << std::endl;

	std::deque<unsigned int> main = sortFJ(winners);

	std::cout << "pairs" << std::endl;
	std::cout << pairs << std::endl;
	std::cout << "winners" << std::endl;
	std::cout << winners << std::endl;

	std::deque<unsigned int> pending;
	//? find???
	// TODO: maybe find
	for (std::size_t i = 0 ; i < main.size() ; ++i)
	{
		for (std::size_t j = 0 ; j < pairs.size() ; ++j)
		{
			if (pairs[j].winner == main[i])
			{
				pending.push_back(pairs[j].loser);
				break ;
			}
		}
	}
	if (hasRemainder)
	{
		pending.push_back(remainder); 
	}

	std::deque<std::size_t> winnerPos;
	for (std::size_t i = 0 ; i < main.size() ; ++i)
		winnerPos.push_back(i);

	main.insert(main.begin(), pending[0]);

	for (std::size_t i = 0 ; i < winnerPos.size() ; ++i)
		++winnerPos[i];

	std::deque<size_t> order = jacobsthal::getOrder(pending.size());
	
	std::cout << "order" << std::endl;
	std::cout << order << std::endl;

	for (std::size_t i = 0 ; i < order.size() ; ++i)
	{
		std::size_t idx = order[i] - 1;
		std::deque<unsigned int>::iterator end;
		if (hasRemainder && idx == pending.size() - 1)
			end = main.end();
		else
			end = main.begin() + winnerPos[idx];
		std::deque<unsigned int>::iterator pos = lower_bound(main.begin(), end, pending[idx]);
		
		for (std::size_t j = 0 ; j < winnerPos.size() ; ++j)
		{
			if (winnerPos[j] >= static_cast<std::size_t>(pos - main.begin()))
				++winnerPos[j];
		}
		main.insert(pos, pending[idx]);

	}

	std::cout << "main" << std::endl;
	std::cout << main << std::endl;
	std::cout << "pending" << std::endl;
	std::cout << pending << std::endl;

	return main;
}

// TODO: change to non-void
void PmergeMe::sort(std::deque<unsigned int>& nbs)
{
	std::cout << "BEFORE" << std::endl;
	std::cout << nbs << std::endl;
	std::deque<unsigned int> sorted = sortFJ(nbs);

	std::cout << "\nSORT\nnbs" << std::endl;
	std::cout << nbs << std::endl;

	std::cout << "sorted" << std::endl;
	std::cout << sorted << std::endl;

	std::deque<unsigned int> sure;
	sure = nbs;
	std::sort(sure.begin(),sure.end());
	bool isSorted = true;
	for (std::size_t i = 0 ; i < sure.size() ; ++i)
	{
		if (sure[i] != sorted[i])
		{
			isSorted = false;
			break ;
		}
	}
	std::cout << std::boolalpha << "check sorted: " << isSorted << std::endl;
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

std::ostream&	operator<<(std::ostream& os, const std::deque<Pair>& pairs)
{
	for (std::size_t i = 0 ; i < pairs.size(); ++i)
	{
		os << "[" << pairs[i].winner << ", " << pairs[i].loser << "]" << std::endl;
	}
	return os;
}
