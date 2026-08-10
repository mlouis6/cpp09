#include "RPN.hpp"
#include <cctype>
#include <cstdlib>
#include <iostream>
#include <limits>
#include <cmath>
#include <exception>

// RPN::RPN(char* args)
// {
// 	calculate(args);
// }
std::stack<int, std::list<int> >	RPN::m_nbs;

// RPN::RPN()
// {

// }

// RPN::RPN(RPN& other)
// {
// 	static_cast<void> (other);
// }

// RPN& RPN::operator=(RPN& other)
// {
// 	static_cast<void> (other);
// 	return *this;
// }

RPN::~RPN()
{
	
}

int	RPN::calculate(char* args)
{
	long	res;
	long	y;
	long	x;

	int	i = 0;
	while (args[i])
	{
		if (args[i] == '+' || args[i] == '-' || args[i] == '*' || args[i] == '/')
		{
			if (m_nbs.size() < 2)
				throw std::runtime_error("Not enough numbers");
			y = m_nbs.top();
			m_nbs.pop();
			x = m_nbs.top();
			m_nbs.pop();
		}
		switch (args[i])
		{
			case '+':
				res = x + y;
				break ;
			case '-':
				res = x - y;
				break ;
			case '*':
				res = x * y;
				break ;
			case '/':
				if (y == 0)
					throw std::runtime_error("Can't divide by 0");
				res = round(static_cast<double>(x) / static_cast<double>(y));
				break ;
			case ' ':
				i++;
				continue ;
				break ;
			default:
				if (!isdigit(args[i]))
					throw std::runtime_error("Not a digit");
				int nb = atoi(&args[i]);
				if (nb < 0 || nb > 9)
					throw std::runtime_error("Number needs to be between 0 and 9");
				m_nbs.push(nb);
				i++;
				continue ;
		}
		if (std::numeric_limits<int>::max() < res || std::numeric_limits<int>::min() > res)
			throw std::runtime_error("Result overflow");
		m_nbs.push(res);
		i++;
	}
	if (m_nbs.size() > 1)
		throw std::runtime_error("Not enough operators");
	return static_cast<int> (m_nbs.top());
}
