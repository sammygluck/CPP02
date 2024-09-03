#include "../incl/Form.hpp"

Form::Form() : _name("default"), _signed(false), _signGrade(150), _execGrade(150)
{
}

Form::Form(std::string name, int signGrade, int execGrade): _name(name), _signed(false), _signGrade(signGrade), _execGrade(execGrade)
{
    if (signGrade < 1 || execGrade < 1)
        throw Form::GradeTooHighException();
    if (signGrade > 150 || execGrade > 150)
        throw Form::GradeTooLowException();
}

Form::Form(const Form &other): _name(other._name), _signed(other._signed), _signGrade(other._signGrade), _execGrade(other._execGrade)
{
}

Form &Form::operator=(const Form &other)
{
    (void) other;
    return *this;
}

Form::~Form()
{
    std::cout << "Form " << this->_name << " is destroyed" << std::endl;
}

std::string Form::getName() const
{
    return this->_name;
}

bool Form::getSigned() const
{
    return this->_signed;
}

int Form::getSignGrade() const
{
    return this->_signGrade;
}

int Form::getExecGrade() const
{
    return this->_execGrade;
}

void Form::beSigned(Bureaucrat &bureaucrat)
{
    if (bureaucrat.getGrade() > this->_signGrade)
        throw Form::GradeTooLowException();
    this->_signed = true;
}

const char* Form::GradeTooHighException::what() const throw()
{
    return "Grade is too high";
}

const char* Form::GradeTooLowException::what() const throw()
{
    return "Grade is too low";
}

std::ostream &operator<<(std::ostream &out, Form const &form)
{
    out << "Form " << form.getName() << ":" << std::endl;
    out << "Signed: " << form.getSigned() << std::endl;
    out << "Sign grade: " << form.getSignGrade() << std::endl;
    out << "Execution grade: " << form.getExecGrade() << std::endl;
    return out;
}