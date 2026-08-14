#ifndef PMERGE_ME_HPP
# define PMERGE_ME_HPP

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

struct Pair
{
	unsigned int a;
	unsigned int b;
};

class PmergeMe
{
	public:
		PmergeMe();
		// PmergeMe(...);
		// PmergeMe(PmergeMe& other);
		// PmergeMe& operator=(PmergeMe& other);
		~PmergeMe();
		
		std::deque<Pair> initPairs(std::deque<unsigned int>& nbs);
		std::deque<unsigned int> init(char **args, int nb_args);

	private:
		std::deque<Pair> m_pairs;
		unsigned int	m_remainder;
		bool			m_hasRemainder;

};

std::ostream&	operator<<(std::ostream& os, const std::deque<unsigned int>& nbs);
std::ostream&	operator<<(std::ostream& os, const std::deque<Pair>& pairs);

#endif
