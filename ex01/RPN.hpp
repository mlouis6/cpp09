#ifndef RPN_HPP
# define RPN_HPP

# include <stack>
# include <vector>

class RPN
{
	public:
		RPN();
		// RPN(...);
		RPN(RPN& other);
		RPN& operator=(RPN& other);
		~RPN();

		int	calculate(char* args);
		bool			err;

	private:
		std::stack<int, std::vector<int> >	m_nbs;

};

#endif
