#include "RPN.hpp"

RPN::RPN()
{
	err = false;
}

// RPN(...)
// {

// }

RPN::RPN(RPN& other)
{
	static_cast<void> (other);
}

RPN& RPN::operator=(RPN& other)
{
	static_cast<void> (other);
	return *this;
}

RPN::~RPN()
{

}

#include <cctype>
#include <cstdlib>
#include <iostream>
#include <limits>
int	RPN::calculate(char* args)
{
	long	res;
	long	y;
	long	x;

	int	i = 0;
	while (args[i])
	{
		switch (args[i])
		{
			case '+':
				if (m_nbs.size() < 2)
				{
					err = true;
					return 1;
				}
				y = m_nbs.top();
				m_nbs.pop();
				x = m_nbs.top();
				m_nbs.pop();
				res = x + y;
				if (std::numeric_limits<int>::max() < res || std::numeric_limits<int>::min() > res)
				{
					err = true;
					return 1;
				}
				m_nbs.push(res);
				break ;
			case '-':
				if (m_nbs.size() < 2)
				{
					err = true;
					return 1;
				}
				y = m_nbs.top();
				m_nbs.pop();
				x = m_nbs.top();
				m_nbs.pop();
				res = x - y;
				if (std::numeric_limits<int>::max() < res || std::numeric_limits<int>::min() > res)
				{
					err = true;
					return 1;
				}
				m_nbs.push(res);

				break ;
			case '*':
				if (m_nbs.size() < 2)
				{
					err = true;
					return 1;
					return 1;
				}
				y = m_nbs.top();
				m_nbs.pop();
				x = m_nbs.top();
				m_nbs.pop();
				res = x * y;
				if (std::numeric_limits<int>::max() < res || std::numeric_limits<int>::min() > res)
				{
					err = true;
					return 1;
				}
				m_nbs.push(res);

				break ;
			case '/':
				if (m_nbs.size() < 2)
				{
					err = true;
					return 1;
				}
				y = m_nbs.top();
				m_nbs.pop();
				x = m_nbs.top();
				m_nbs.pop();
				if (y == 0)
				{
					err = true;
					return 1;
				}
				res = x / y;
				if (std::numeric_limits<int>::max() < res || std::numeric_limits<int>::min() > res)
				{
					err = true;
					return 1;
				}
				m_nbs.push(res);

				break ;
			case ' ':
				break ;
			default:
				if (!isdigit(args[i]))
				{
					err = true;
					return 1;
				}
				int nb = atoi(&args[i]);
				if (nb < 0 || nb > 9)
				{
					err = true;
					return 1;
				}
				m_nbs.push(nb);
		}
		i++;
	}
	if (m_nbs.size() > 1)
		err = true;
	return static_cast<int> (m_nbs.top());
}
