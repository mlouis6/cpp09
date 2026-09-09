#include "PmergeMe.hpp"


// TODO: debug mode
// TODO: duplicate mode, pmm need to be modify to shuf with double

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

		// if (size > 1)
		// 	j_order.push_back(1);

		for (std::size_t i = 3 ;  ; ++i)
		{	
			std::size_t j_curr = getNumber(i);

			if (j_prev >= size) // - 1)
				break ;

			std::size_t end = std::min(j_curr, size); // - 1);

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


// std::deque<unsigned int> PmergeMe::sortFJ(const std::deque<Pair>& pairs)
// {
// 	if (pairs.size() <= 1)
// 	{
// 		std::deque<unsigned int> ret;
// 		for (std::size_t i = 0 ; i < pairs.size() ; ++i)
// 			ret.push_back(pairs[i].winner);
// 		return ret;
// 	}

// 	std::deque<Pair> newPairs;
// 	std::size_t size = pairs.size();
// 	bool hasRemainder = false;
// 	unsigned int remainder;
// 	if (size % 2 != 0)
// 	{
// 		--size;
// 		hasRemainder = true;
// 		remainder = pairs[size].winner;
// 	}

// 	for (std::size_t i = 0 ; i < size ; i += 2)
// 	{
// 		Pair p;
// 		if (pairs[i].winner > pairs[i + 1].winner)
// 		{
// 			p.winner = pairs[i].winner;
// 			p.loser = pairs[i + 1].winner;
// 		}
// 		else
// 		{
// 			p.winner = pairs[i + 1].winner;
// 			p.loser = pairs[i].winner;
// 		}
// 		newPairs.push_back(p);
// 	}

// 	std::deque<unsigned int> pairs2 = sortFJ(newPairs);

// 	/*** */
// 	std::deque<Pair> sortedPairs;

// 	for (std::size_t i = 0; i < pairs2.size(); ++i)
// 	{
// 		for (std::size_t j = 0; j < pairs.size(); ++j)
// 		{
// 			if (pairs[j].winner == pairs2[i])
// 			{
// 				sortedPairs.push_back(pairs[j]);
// 				break;
// 			}
// 		}
// 	}
// 	std::cout << "sortedPairs" << std::endl;

// 	for (std::size_t i = 0; i < sortedPairs.size(); ++i)
// 		std::cout << "[" << sortedPairs[i].winner
// 				<< ", " << sortedPairs[i].loser << "]" << std::endl;
// 	/*** */

// 	std::cout << "pairs" << std::endl;
// 	std::cout << pairs << std::endl;
// 	std::cout << "newPairs" << std::endl;
// 	std::cout << newPairs << std::endl;
// 	std::cout << "size" << std::endl;
// 	std::cout << newPairs.size() << std::endl;

// 	std::deque<unsigned int> main;
// 	std::deque<unsigned int> pending;
// 	for (std::size_t i = 0 ; i < sortedPairs.size() ; ++i)
// 	{
// 		main.push_back(sortedPairs[i].winner);
// 		// res.push_back(sortedPairs[i].winner);
// 		pending.push_back(sortedPairs[i].loser);
// 	}
// 	if (hasRemainder)
// 	{
// 		pending.push_back(remainder); 
// 	}
	
// 	std::deque<unsigned int> res = main;

// 	std::deque<std::size_t> winnerPos;
// 	for (std::size_t i = 0 ; i < main.size() ; ++i)
// 		winnerPos.push_back(i);

// 	res.insert(res.begin(), sortedPairs[0].loser);

// 	for (std::size_t i = 0 ; i < winnerPos.size() ; ++i)
// 		++winnerPos[i];

// 	std::deque<size_t> order = jacobsthal::getOrder(pending.size());
	
// 	std::cout << "order" << std::endl;
// 	std::cout << order << std::endl;

// 	// if (order[0] == 1)
// 	// 	order.pop_front();

// 	for (std::size_t i = 0 ; i < order.size() ; ++i)
// 	{
// 		std::size_t idx = order[i] - 1;
// 		std::deque<unsigned int>::iterator pos = lower_bound(res.begin(), res.begin() + winnerPos[idx], pending[idx]);
// 		res.insert(pos, pending[idx]);

// 		for (std::size_t j = idx ; j < winnerPos.size() ; ++j)
// 			++winnerPos[j];
// 	}

// 	// if (hasRemainder)
// 	// {
// 	// 	std::deque<unsigned int>::iterator pos = lower_bound(res.begin(), res.end(), remainder);
// 	// 	res.insert(pos, remainder);
// 	// }

// 	std::cout << "main" << std::endl;
// 	std::cout << main << std::endl;
// 	std::cout << "pending" << std::endl;
// 	std::cout << pending << std::endl;
// 	std::cout << "res" << std::endl;
// 	std::cout << res << std::endl;

// 	return res;
// }

std::deque<unsigned int> PmergeMe::sortFJ(const std::deque<unsigned int>& values)
{
    if (values.size() <= 1)
        return values;

    std::size_t n = values.size();
    bool hasRemainder = false;
    unsigned int remainder = 0;
    if (n % 2 != 0)
    {
        hasRemainder = true;
        remainder = values[n - 1];
        --n;
    }

    std::deque<Pair> pairs;
    for (std::size_t i = 0; i < n; i += 2)
    {
        Pair p;
        if (values[i] > values[i + 1])
        { p.winner = values[i];     p.loser = values[i + 1]; }
        else
        { p.winner = values[i + 1]; p.loser = values[i]; }
        pairs.push_back(p);
    }

    // recurse on plain winner values only
    std::deque<unsigned int> winners;
    for (std::size_t i = 0; i < pairs.size(); ++i)
	{
        winners.push_back(pairs[i].winner);
	}

	
	std::cout << "pairsBEFORE" << std::endl;
	std::cout << pairs << std::endl;
	std::cout << "winnersBEFORE" << std::endl;
	std::cout << winners << std::endl;

    std::deque<unsigned int> mainChain = sortFJ(winners); // fully sorted, same length as pairs

	std::cout << "pairs" << std::endl;
	std::cout << pairs << std::endl;
	std::cout << "winners" << std::endl;
	std::cout << winners << std::endl;
	// std::cout << "mainChain" << std::endl;
	// std::cout << mainChain << std::endl;

    // reattach each winner's own loser, freshly, from THIS level's pairs
    std::deque<unsigned int> pending;
    for (std::size_t i = 0; i < mainChain.size(); ++i)
    {
        for (std::size_t j = 0; j < pairs.size(); ++j)
        {
            if (pairs[j].winner == mainChain[i])
            {
                pending.push_back(pairs[j].loser);
                break;
            }
        }
    }
    if (hasRemainder)
        pending.push_back(remainder);

    std::deque<unsigned int> res = mainChain;

	res.insert(res.begin(), pending[0]);

	// track where each mainChain[k] currently sits inside res
	std::deque<std::size_t> winnerPos;
	for (std::size_t i = 0; i < mainChain.size(); ++i)
		winnerPos.push_back(i + 1); // +1 because pending[0] was just inserted at index 0

	std::deque<std::size_t> order = jacobsthal::getOrder(pending.size());
	std::cout << "order" << std::endl;
	std::cout << order << std::endl;

	for (std::size_t i = 0; i < order.size(); ++i)
	{
		std::size_t k = order[i] - 1; // 0-indexed
		if (k == 0)
			continue; // already inserted above
		
		bool isRemainderSlot = hasRemainder && (k == pending.size() - 1);
		std::deque<unsigned int>::iterator upper =
			isRemainderSlot ? res.end() : (res.begin() + winnerPos[k]);

		// pending[k] is guaranteed < mainChain[k], so bound the search there
		std::deque<unsigned int>::iterator pos =
				std::lower_bound(res.begin(), upper, pending[k]);

			std::size_t insertIndex = pos - res.begin();
			res.insert(pos, pending[k]);

			for (std::size_t j = 0; j < winnerPos.size(); ++j)
				if (winnerPos[j] >= insertIndex)
					++winnerPos[j];
	}

	std::cout << "mainChain" << std::endl;
	std::cout << mainChain << std::endl;
	std::cout << "pending" << std::endl;
	std::cout << pending << std::endl;
	std::cout << "res" << std::endl;
	std::cout << res << std::endl;

    return res;
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
