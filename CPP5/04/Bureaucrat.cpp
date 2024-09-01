#include "Bureaucrat.hpp"

Bureaucrat::Bureaucrat()
{
    _name = "default";
    _grade = 150;
}

Bureaucrat::Bureaucrat(std::string name, int grade): _name(name)
{
    if (grade < 1)
        throw Bureaucrat::GradeTooHighException();
    else if (grade > 150)
        throw Bureaucrat::GradeTooLowException();
    else
        this->_grade = grade;
}

Bureaucrat::Bureaucrat(const Bureaucrat &other)
{
  *this = other; //make sure this works well because name is a const
}

Bureaucrat &Bureaucrat::operator=(Bureaucrat const &other)
{
    if (this != &other)
    {
        this->_grade = other._grade; //name doesn't get copies as it's a const
    }
    return *this;
}


Bureaucrat::~Bureaucrat()
{
    std::cout << "Bureaucrat " << this->_name << " is destroyed" << std::endl;
}

std::string Bureaucrat::getName() const
{
    return this->_name;
}

int Bureaucrat::getGrade() const
{
    return this->_grade;
}

void Bureaucrat::incrementGrade()
{
    if (--this->_grade < 1)
        throw Bureaucrat::GradeTooHighException();
}

void Bureaucrat::decrementGrade()
{
    if (++this->_grade > 150)
        throw Bureaucrat::GradeTooLowException();
}

void Bureaucrat::signForm(AForm &form)
{
    try
    {
        form.beSigned(*this);
        std::cout << this->_name << " signed " << form.getName() << std::endl;
    }
    catch(const std::exception& e)
    {
        std::cout << this->_name << " couldn't sign " << form.getName();
        std::cout << " because " << e.what() << std::endl;
    }  
}

void Bureaucrat::executeForm(AForm const &form)
{
    try
    {
        form.execute(*this);
        std::cout << this->_name << "executed" << form.getName() << std::endl;
    }
    catch(const std::exception& e)
    {
        std::cout << this->_name << "failed to execute" << form.getName();
        std::cout << " because " << e.what() << std::endl;
    }
    
}

const char* Bureaucrat::GradeTooHighException::what() const throw()
{
    return "Exception thrown: Grade is too high";
}

const char* Bureaucrat::GradeTooLowException::what() const throw()
{
    return "Exception thrown: Grade is too low";
}

std::ostream &operator<<(std::ostream &out, Bureaucrat const &bureaucrat)
{
    out << bureaucrat.getName() << ", bureaucrat grade " << bureaucrat.getGrade() << std::endl;
    return out;
}