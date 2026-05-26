#include <iostream>
#include <sstream>
#include <limits>
#include <vector>

int main(int argc, char** argv)
{

	if (argc != 2)
	{
		std::cerr << "Error\nUsage './PMergeMe \"<positive integers>\"'" << std::endl;
		return 1;
	}

	std::vector<unsigned int>	cont1;
	std::istringstream iss(argv[1]);
	while (!iss.eof())
	{
		long val;
		iss >> val;
		if (iss.fail() || val < 0 || val > std::numeric_limits<int>::max())
		{
			throw std::runtime_error("Error: not a positive integer");
		}
		cont1.push_back(static_cast<unsigned int> (val));
	}

	return 0;
}

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
