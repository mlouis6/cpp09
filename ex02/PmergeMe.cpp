#include "PmergeMe.hpp"

PmergeMe::PmergeMe() : m_pairs(), m_remainder(0), m_hasRemainder(false)
{

}

// PmergeMe::PmergeMe(PmergeMe& other)
// {

// }

// PmergeMe& PmergeMe::operator=(PmergeMe& other)
// {

// }

PmergeMe::~PmergeMe()
{

}





// TODO:
// sort(vector/deque<unsigned int>& numbers)
//         |
//         +-- pair adjacent numbers
//         |
//         +-- compare each pair
//         |      A = larger
//         |      B = smaller
//         |
//         +-- recursively sort A's
//         |
//         +-- build main chain from sorted A's
//         |
//         +-- insert B's using Jacobsthal order
//         |      |
//         |      +-- binary search
//         |
//         +-- insert odd remainder

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

	template <typename Container>
	Container getOrder(std::size_t size)
	{
		Container j_order;
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
		return nbs;
	}

	std::deque<Pair> PmergeMe::initPairs(std::deque<unsigned int>& nbs)
	{
		std::size_t size = nbs.size();
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
				p.a = nbs[i];
				++i;
				p.b = nbs[i];
			}
			else
			{
				p.b = nbs[i];
				++i;
				p.a = nbs[i];
			}

			m_pairs.push_back(p);
		}

		return m_pairs;
	}
	
	std::deque<Group> nextLevelPairs(const std::deque<Pair>& pairs)
	{
		if (pairs.size() < 2)
		{
			return pairs;
		}

	}

	void PmergeMe::sort(std::deque<Pair>& pairs)
	{
		if (pairs.size() <= 1)
			return ;

		sort(nextLevelPairs(pairs));
		// std::deque<Pair> np = nextLevelPairs(pairs);
		// sort(np);
	}
	
	// void	swap(pair_iter it)
	// {
	// 	for (std::size_t i = 0 ; i < it->size / 2 ; ++i)
	// 	{
	// 		std::swap(*(it->begin + i), *((it->begin + i) + (it->size / 2)));
	// 	}

	// }

	// void findBiggest(deque::pair& pairs)
	// {
	// 	pair_iter ite = pairs.end();
	// 	pair_iter it = pairs.begin();
	// 	if (it->size != (ite - 1)->size)
	// 	{
	// 		--ite;
	// 	}
	// 	for ( ; it != ite ; ++it)
	// 	{
	// 		if (*(it->begin) < *(it->begin + (it->size / 2)))
	// 		{
	// 			swap(it);
	// 		}
	// 	}
	// }

	// std::size_t	getPairsSize(const deque::pair& pairs)
	// {
	// 	cp_iter ite = pairs.end();
	// 	cp_iter it = pairs.begin();
	// 	if (it == ite - 1)
	// 	{
	// 		return 1;
	// 	}
	// 	if (it->size != (ite - 1)->size)
	// 	{
	// 		return (pairs.size() - 1);
	// 	}
	// 	return pairs.size();
	// }


	std::ostream&	operator<<(std::ostream& os, const std::deque<Pair>& pairs)
	{
		for (std::size_t i = 0 ; i < pairs.size(); ++i)
		{
			os << "[" << pairs[i].a << ", " << pairs[i].b << "]" << std::endl;
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

	// deque::pair createPairs(const deque::pair& pairs)
	// {
	// 	deque::pair newPairs;
	// 	std::size_t i = 0;
	// 	for ( ; i < pairs.size() - 1 ; i += 2)
	// 	{
	// 		group g;

	// 		g.begin = pairs[i].begin;
	// 		g.size = pairs[i].size + pairs[i + 1].size;

	// 		newPairs.push_back(g);
	// 	}
		
	// 	if (i < pairs.size())
	// 		newPairs.push_back(pairs[i]);

	// 	return newPairs;
	// }

	// void orderPairs(deque::pair& pairs, const deque::pair& newPairs)
	// {
	// 	deque::pair ordered;

	// 	for (cp_iter it = newPairs.begin() ; it != newPairs.end() ; ++it)
	// 	{
	// 		for (cp_iter it2 = pairs.begin() ; it2 != pairs.end() ; ++it2)
	// 		{
	// 			if (it2->begin == it->begin)
	// 			{
	// 				ordered.push_back(*it2);
	// 				if (it->size == it2->size * 2)
	// 				{
	// 					++it2;
	// 					if (it2 != pairs.end())
	// 						ordered.push_back(*it2);
	// 				}
	// 				break ;
	// 			}
	// 		}
	// 	}

	// 	pairs = ordered;
	// }

	// void	sort(deque::pair& pairs)
	// {
	// 	std::deque<Pair> pairs;
	// 	std::deque<unsigned int> main;

	// 	/************ OLDIE AND NOT GOODIE............ ***********/

	// 	std::cout << "CREATE\n"<< pairs << std::endl;
	// 	findBiggest(pairs);
	// 	std::cout << "BIGGEST\n" << pairs << std::endl;
	// 	if (deque::getPairsSize(pairs) == 2)
	// 	{
	// 		pair_iter it1 = pairs.begin();
	// 		pair_iter it2 = it1 + 1;

	// 		if (*(it1->begin) > *(it2->begin))
	// 			std::swap(*it1, *it2);

	// 		return;
	// 	}
		
	// 	if (deque::getPairsSize(pairs) <= 1)
	// 		return ;


	// 	deque::pair newPairs = createPairs(pairs);
	// 	sort(newPairs);
	// 	orderPairs(pairs, newPairs);

	// 	// pairs = createPairs(nbs, nbGroups);

	// 	/** order order winner winner */

	// 	std::cout << "END RECURSION" << std::endl;

	// 	// std::cout << nbs << std::endl;
	// 	std::cout << pairs << std::endl;

	// 	std::size_t size = deque::getPairsSize(pairs);
	// 	if (pairs[0].size != pairs[size - 1].size)
	// 		--size;
	// 	if (size % 2 != 0)
	// 		--size;

	// 	std::cout << "Jacobsthal" << std::endl;
	// 	std::cout << "curr= " << jacobsthal::getNumber(size) << std::endl;
	// 	std::cout << "next= " << jacobsthal::getNumber(size) << std::endl;
	// 	std::cout << "end Jacobsthal" << std::endl;

	// 	std::cout << "start: " << *(pairs[0].begin) << std::endl;
	// 	std::cout << "end: " << *(pairs[size - 1].begin + pairs[size - 1].size - 1 ) << std::endl;

	// 	std::deque<unsigned int> main;
	// 	deque::pair a_deq;
	// 	deque::pair b_deq;
	// 	std::size_t nb_pairs =  getPairsSize(pairs);
	// 	cp_iter it = pairs.begin();
	// 	for (std::size_t i = 0 ; i < nb_pairs; ++i, ++it)
	// 	{
	// 		c_iter	iter = it->begin;
	// 		std::size_t j = 0;
			
	// 		group a_grp;
	// 		a_grp.begin = it->begin;
	// 		a_grp.size = it->size / 2;


	// 		group b_grp;
	// 		b_grp.begin = it->begin + (it->size / 2);
	// 		b_grp.size = it->size / 2;

	// 		a_deq.push_back(a_grp);
	// 		b_deq.push_back(b_grp);
	// 		for (; j < it->size / 2 ; ++j, ++iter)
	// 		{
	// 			main.push_back(*iter);
	// 			// a_deq.push_back(*iter);
	// 		}
	// 		// for ( ; j < it->size ; ++j, ++iter)
	// 		// {
	// 		// 	b_deq.push_back(*iter);
	// 		// }

	// 	}
	// 	//! for B0
	// 	for (std::size_t i = pairs.begin()->size - 1 ; i > pairs.begin()->size / 2 - 1; --i)
	// 		main.push_front(*(pairs.begin()->begin + i));
	// 	//! end B0

	// 	// 1 - jacobsthal -> which group to insert
	// 	// 2 - binary search -> where the group goes

	// 	// insert B0 before A0 directly

	// 	// TODO: binary search
	// }

