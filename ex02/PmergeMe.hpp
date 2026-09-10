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
		
		std::deque<unsigned int> initD(char **args, int nb_args);
		std::vector<unsigned int> initV(char **args, int nb_args);
		std::deque<unsigned int> sort(const std::deque<unsigned int>& pairs);
		std::vector<unsigned int> sort(const std::vector<unsigned int>& pairs);

	private:
};

std::ostream&	operator<<(std::ostream& os, const std::deque<unsigned int>& nbs);
std::ostream&	operator<<(std::ostream& os, const std::vector<unsigned int>& nbs);
std::ostream&	operator<<(std::ostream& os, const std::deque<std::size_t>& nbs);
std::ostream&	operator<<(std::ostream& os, const std::vector<std::size_t>& nbs);
std::ostream&	operator<<(std::ostream& os, const std::deque<Pair>& pairs);
std::ostream&	operator<<(std::ostream& os, const std::vector<Pair>& pairs);

#endif
