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
	long res;long	y;long	x;
	/**
	 * push to stack until operator
	 * top
	 * pop
	 * top
	 * pop
	 * top2 operator top1
	 * push
	 *
	*/
	int	i = 0;
	while (args[i])
	{
		switch (args[i])
		{
			case '+':
				if (m_nbs.size() < 2)
				{
					std::cerr << "Error" << std::endl;
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
					// std::cerr << "Error" << std::endl;
					err = true;
					return 1;
				}
				m_nbs.push(res);
				break ;
			case '-':
				if (m_nbs.size() < 2)
				{
					// std::cerr << "Error" << std::endl;
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
					// std::cerr << "Error" << std::endl;
					err = true;
					return 1;
				}
				m_nbs.push(res);

				break ;
			case '*':
				if (m_nbs.size() < 2)
				{
					// std::cerr << "Error" << std::endl;
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
					// std::cerr << "Error" << std::endl;
					err = true;
					return 1;
				}
				m_nbs.push(res);

				break ;
			case '/':
				if (m_nbs.size() < 2)
				{
					// std::cerr << "Error" << std::endl;
					err = true;
					return 1;
				}
				y = m_nbs.top();
				m_nbs.pop();
				x = m_nbs.top();
				m_nbs.pop();
				if (y == 0)
				{
					// std::cerr << "Error" << std::endl;
					err = true;
					return 1;
				}
				res = x / y;
				if (std::numeric_limits<int>::max() < res || std::numeric_limits<int>::min() > res)
				{
					// std::cerr << "Error" << std::endl;
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
					// std::cerr << "Error"<< std::endl;
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
	return static_cast<int> (m_nbs.top());
}

// TODO: check overflow / underflow
// TODO: check if divided by 0
// TODO: check between 0-9


