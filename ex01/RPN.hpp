#ifndef RPN_HPP
# define RPN_HPP

# include <stack>
# include <list>

class RPN
{
	public:
		~RPN();
		static int	calculate(char* args);

	private:
		RPN();
		RPN(RPN& other);
		// RPN(char* args);
		RPN& operator=(RPN& other);

		static std::stack<int, std::list<int> >	m_nbs;

};

#endif
