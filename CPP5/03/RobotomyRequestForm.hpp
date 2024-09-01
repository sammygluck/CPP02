#ifndef ROBOTOMYREQUESTFORM_HPP
#define ROBOTOMYREQUESTFORM_HPP

#include <iostream>
#include <string>
#include <exception>
#include <random>
#include <AForm.hpp>
#include <Bureaucrat.hpp>

class RobotomyRequestForm : public AForm
{
    public:
        RobotomyRequestForm();
        RobotomyRequestForm(std::string target);
        RobotomyRequestForm(const RobotomyRequestForm &other);
        RobotomyRequestForm &operator=(const RobotomyRequestForm &other);
        ~RobotomyRequestForm();

        void execute(Bureaucrat const & executor) const;

        class RobotomizeException : public std::exception
        {
            public:
                const char *what() const throw();
        };
};

#endif