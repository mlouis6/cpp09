#include <iostream>
#include <sstream>
#include <limits>
#include <vector>
#include <exception>

void	foo(char* args)
{
	std::vector<unsigned int>	cont1;
	std::istringstream iss(args);
	while (!iss.eof())
	{
		long val;
		iss >> val;
		if (iss.fail() || val < 0 || val > std::numeric_limits<int>::max())
		{
			throw std::runtime_error("Error: argument contains a none positive integer");
		}
		cont1.push_back(static_cast<unsigned int> (val));
	}
}

int main(int argc, char** argv)
{

	if (argc != 2 || argv[1][0] == 0)
	{
		std::cerr << "Erro: usage './PmergeMe \"<positive integers>\"'" << std::endl;
		return 1;
	}
	try
	{
		foo(argv[1]);
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}

	return 0;
}

/**
Group the elements of X into ⌊ n / 2 ⌋ pairs of elements, arbitrarily, leaving one element unpaired if there is an odd number of elements.
Perform ⌊ n / 2 ⌋ comparisons, one per pair, to determine the larger of the two elements in each pair.
Recursively sort the ⌊ n / 2 ⌋ larger elements from each pair, creating a sorted sequence S of ⌊ n / 2 ⌋ of the input elements, in ascending order, using the merge-insertion sort.
Insert at the start of S the element that was paired with the first and smallest element of S.
Insert the remaining ⌈ n / 2 ⌉ − 1  elements of X ∖ S into S, one at a time, with a specially chosen insertion ordering described below. Use binary search in subsequences of S(as described below) to determine the position at which each element should be inserted.
 */

/** 
Your program must be able to use a positive integer sequence as an argument.

Your program must use the merge-insert sort algorithm to sort the positive integer
sequence.

To clarify, yes, you need to use the Ford-Johnson algorithm.

You must use at least two different containers in your code to
validate this exercise. Your program must be able to handle at
least 3000 different integers.

It is strongly advised to implement your algorithm for each container
and thus to avoid using a generic function.

Here are some additional guidelines on the information you should display line by line
on the standard output:
• On the first line you must display an explicit text followed by the unsorted positive
integer sequence.
• On the second line you must display an explicit text followed by the sorted positive
integer sequence.
• On the third line, you must display an explicit message indicating the time taken
by your algorithm, specifying the first container used to sort the positive integer
sequence.
• On the last line you must display an explicit text indicating the time used by
your algorithm by specifying the second container used to sort the positive integer
sequence.
The format for the display of the time used to carry out your sorting
is free but the precision chosen must allow to clearly see the
difference between the two containers used.
*/
