/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgluck <sgluck@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 10:54:51 by sgluck            #+#    #+#             */
/*   Updated: 2024/08/15 10:54:55 by sgluck           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/Bureaucrat.hpp"

int main(void)
{
	std::cout << "REGULAR USE:" << std::endl;
	Bureaucrat A("A", 100);
	std::cout << A << std::endl;

	std::cout << "COPY CONSTRUCTOR" << std::endl;
	Bureaucrat B(A);
	std::cout << B << std::endl;

	std::cout << "= OPERATOR OVERLOAD" << std::endl;
	Bureaucrat C;
	C = A;
	std::cout << C << std::endl;

	std::cout << "-----------------------------------------------" << std::endl;
	std::cout << "ON THE LOW END" << std::endl << std::endl;

	try
	{
		std::cout << "INSTANTIATION WITH WRONG ELEMENT I.E. 151" << std::endl;
		Bureaucrat wrong("wrong", 151);
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}

	try
	{
		std::cout << "LOWEST GRADE BUREAUCRAT (i.e. 150):" << std::endl;
		Bureaucrat low("low", 150);
		std::cout  << low << std::endl;
		std::cout << "DECREMENTING THE LOW TO 151, RESULTS IN DISASTER" << std::endl;
		low.decrementGrade();
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}
	
	std::cout << "-----------------------------------------------" << std::endl;
	std::cout << "ON THE HIGH END" << std::endl << std::endl;

	try
	{
		std::cout << "INSTANTIATION WITH WRONG ELEMENT I.E 0" << std::endl;
		Bureaucrat wrong("wrong2", 0);
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}

	try
	{
		std::cout << "HIGHEST GRADE BUREAUCRAT (i.e. 1):" << std::endl;
		Bureaucrat low("high", 1);
		std::cout  << low << std::endl;
		std::cout << "INCREMENTING HIGH TO 0 RESULTS IN DISASTER" << std::endl;
		low.incrementGrade();
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}
	
}
