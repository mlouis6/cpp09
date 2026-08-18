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
// #include <utility>

struct Pair
{
	unsigned int a;
	unsigned int b;

	Pair() {}
	Pair(unsigned int a, unsigned int b) : a(a), b(b) {};
};

struct Group
{
	std::deque<Pair> pairs;
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
		std::deque<Group> initGroups(std::deque<Pair>& pairs);
		std::deque<unsigned int> init(char **args, int nb_args);
		void sort(std::deque<Group>& groups);

	private:
		std::deque<Pair> m_pairs;
		std::deque<Group> m_groups;
		unsigned int	m_remainder;
		bool			m_hasRemainder;

};

// std::ostream&	operator<<(std::ostream& os, const std::deque<unsigned int>& nbs);
std::ostream&	operator<<(std::ostream& os, const std::deque<Pair>& pairs);

#endif
