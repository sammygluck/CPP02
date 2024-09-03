#include "../incl/AForm.hpp"

Bureaucrat::Bureaucrat(): _name("default")
{
    this->_grade = 150;
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

Bureaucrat::Bureaucrat(const Bureaucrat &other): _name(other._name)
{
  this->_grade = other._grade;
}

Bureaucrat &Bureaucrat::operator=(Bureaucrat const &other)
{
    if (this != &other)
    {
        this->_grade = other._grade;
    }
    return *this;
}


Bureaucrat::~Bureaucrat()
{
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
        std::cout << this->getName() << " executed " << form.getName() << std::endl;
    }
    catch(const std::exception& e)
    {
        std::cout << this->getName() << " couldn't execute " << form.getName() << " reason being: " << e.what() << std::endl;
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