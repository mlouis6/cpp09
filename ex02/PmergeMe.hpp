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
#include <utility>

typedef std::pair<unsigned int, unsigned int> Pair; 

class PmergeMe
{
	public:
		PmergeMe();
		// PmergeMe(...);
		PmergeMe(PmergeMe& other);
		PmergeMe& operator=(PmergeMe& other);
		~PmergeMe();
		
		std::deque<Pair> initPairs(std::deque<unsigned int>& nbs);
		std::deque<unsigned int> init(char **args, int nb_args);
		void sort(std::deque<unsigned int>& nbs);

	private:
		void	sortPairs(std::deque<Pair>& pairs, bool hasRemainder, unsigned int remainder);

};

template <typename T>
std::ostream&	operator<<(std::ostream& os, const std::deque<T>& nbs);
std::ostream&	operator<<(std::ostream& os, const std::deque<Pair>& pairs);

#endif
