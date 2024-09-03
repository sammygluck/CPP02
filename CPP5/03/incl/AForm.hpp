#ifndef FORM_HPP
#define FORM_HPP

#include <iostream>
#include <string>
#include <exception>
#include "Bureaucrat.hpp"

class Bureaucrat;

class AForm
{
    private:
        const std::string _name;
        bool _signed;
        const int _signGrade;
        const int _execGrade;
        std::string _target;     
    public:
        AForm();
        AForm(std::string name, int signGrade, int execGrade);
        AForm(const AForm &other);
        AForm &operator=(const AForm &other);
        virtual ~AForm();

        std::string getName() const;
        bool getSigned() const;
        int getSignGrade() const;
        int getExecGrade() const;
        std::string getTarget() const;
        void setTarget(std::string target);

        void beSigned(Bureaucrat &bureaucrat);

        virtual void execute(Bureaucrat const & executor) const = 0;

        class GradeTooHighException : public std::exception
        {
            public:
                const char *what() const throw();
        };

        class GradeTooLowException: public std::exception
        {
            public:
                const char *what() const throw();
        };

        class AlreadySignedException: public std::exception
        {
            public:
                const char *what() const throw();
        };

        class NotSignedException: public std::exception
        {
            public:
                const char *what() const throw();
        };
};

std::ostream &operator<<(std::ostream &out, const AForm &form);

#endif