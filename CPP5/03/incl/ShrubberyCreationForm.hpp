#ifndef SHRUBBERYCREATIONFORM_HPP
#define SHRUBBERYCREATIONFORM_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <exception>
#include <AForm.hpp>
#include <Bureaucrat.hpp>

class ShrubberyCreationForm : public AForm
{
    public:
        ShrubberyCreationForm();
        ShrubberyCreationForm(std::string target);
        ShrubberyCreationForm(const ShrubberyCreationForm &other);
        ShrubberyCreationForm &operator=(const ShrubberyCreationForm &other);
        ~ShrubberyCreationForm();

        void execute(Bureaucrat const & executor) const;

        class OpenFileException : public std::exception
        {
            public:
                const char* what() const throw();
        };
};

#endif