#include "../incl/PresidentialPardonForm.hpp"

PresidentialPardonForm::PresidentialPardonForm() : AForm("PresidentialDefault", 25, 5)
{
    this->setTarget("default");
}

PresidentialPardonForm::PresidentialPardonForm(std::string target) : AForm("PresidentialPardonForm", 25, 5)
{
    this->setTarget(target);
}

PresidentialPardonForm::PresidentialPardonForm(const PresidentialPardonForm &other): AForm(other) // copy constructor
{
    this->setTarget(other.getTarget());
}

PresidentialPardonForm &PresidentialPardonForm::operator=(const PresidentialPardonForm &other)
{
   
    this->setTarget(other.getTarget());
    return *this;
}

PresidentialPardonForm::~PresidentialPardonForm()
{
    std::cout << "PresidentialPardonForm " << this->getName() << " is destroyed" << std::endl;
}

void PresidentialPardonForm::execute(Bureaucrat const &executor) const
{
    if (executor.getGrade() > this->getExecGrade())
        throw AForm::GradeTooLowException();
    if (!this->getSigned())
        throw AForm::NotSignedException();

    std::cout << this->getTarget() << " has been pardoned by Zaphod Beeblebrox" << std::endl;
}