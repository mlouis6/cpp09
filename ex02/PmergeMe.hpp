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

struct Pair
{
	unsigned int winner;
	unsigned int loser;
};

class PmergeMe
{
	public:
		PmergeMe();
		PmergeMe(PmergeMe& other);
		PmergeMe& operator=(PmergeMe& other);
		~PmergeMe();
		
		std::deque<Pair> initPairs(std::deque<unsigned int>& nbs);
		std::deque<unsigned int> initD(char **args, int nb_args);
		void sort(std::deque<unsigned int>& nbs);
		std::vector<Pair> initPairs(std::vector<unsigned int>& nbs);
		std::vector<unsigned int> initV(char **args, int nb_args);
		void sort(std::vector<unsigned int>& nbs);

	private:
		void	sortPairs(std::deque<Pair>& pairs);
		std::deque<unsigned int> sortFJ(const std::deque<unsigned int>& pairs);
		void	sortPairs(std::vector<Pair>& pairs);
		std::vector<unsigned int> sortFJ(const std::vector<unsigned int>& pairs);
};

template<typename T>
std::ostream&	operator<<(std::ostream& os, const std::deque<T>& nbs);
template<typename T>
std::ostream&	operator<<(std::ostream& os, const std::vector<T>& nbs);
std::ostream&	operator<<(std::ostream& os, const std::deque<Pair>& pairs);
std::ostream&	operator<<(std::ostream& os, const std::vector<Pair>& pairs);

#endif
