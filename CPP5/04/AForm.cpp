#include <AForm.hpp>

AForm::AForm() : _name("default"), _signed(false), _signGrade(150), _execGrade(150)
{
}

AForm::AForm(std::string name, int signGrade, int execGrade): _name(name), _signed(false), _signGrade(signGrade), _execGrade(execGrade)
{
    if (signGrade < 1 || execGrade < 1)
        throw AForm::GradeTooHighException();
    if (signGrade > 150 || execGrade > 150)
        throw AForm::GradeTooLowException();
}

AForm::AForm(const AForm &other)
{
    *this = other; //again make sure this works well because most vars are a const
}

AForm &AForm::operator=(const AForm &other)
{
    if (this != &other)
    {
        this->_signed = other._signed;
    }
    return *this;
}

AForm::~AForm()
{
    std::cout << "Form " << this->_name << " is destroyed" << std::endl;
}

std::string AForm::getName() const
{
    return this->_name;
}

bool AForm::getSigned() const
{
    return this->_signed;
}

const int AForm::getSignGrade() const
{
    return this->_signGrade;
}

const int AForm::getExecGrade() const
{
    return this->_execGrade;
}

std::string AForm::getTarget() const
{
    return this->_target;
}

void AForm::setTarget(std::string target)
{
    this->_target = target;
}

void AForm::beSigned(Bureaucrat &bureaucrat)
{
    if (bureaucrat.getGrade() > this->_signGrade)
        throw AForm::GradeTooLowException();
    this->_signed = true;
}

void AForm::execute(Bureaucrat const & executor) const
{
    if (!this->_signed)
        throw AForm::NotSignedException();
    if (executor.getGrade() > this->_execGrade)
        throw AForm::GradeTooLowException();
}

const char* AForm::GradeTooHighException::what() const throw()
{
    return "Grade is too high";
}

const char* AForm::GradeTooLowException::what() const throw()
{
    return "Grade is too low";
}

const char* AForm::AlreadySignedException::what() const throw()
{
    return "Form is already signed";
}

const char* AForm::NotSignedException::what() const throw()
{
    return "Form is not signed";
}

std::ostream &operator<<(std::ostream &out, AForm const &form)
{
    out << "Form " << form.getName() << ":" << std::endl;
    out << "Signed: " << form.getSigned() << std::endl;
    out << "Sign grade: " << form.getSignGrade() << std::endl;
    out << "Execution grade: " << form.getExecGrade() << std::endl;
    out << "Target: " << form.getTarget() << std::endl;
    return out;
}