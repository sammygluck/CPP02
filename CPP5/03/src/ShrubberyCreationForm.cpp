#include "../incl/ShrubberyCreationForm.hpp"

ShrubberyCreationForm::ShrubberyCreationForm(): AForm("ShrubberyDefault", 145, 137)
{
    this->setTarget("default");
}

ShrubberyCreationForm::ShrubberyCreationForm(std::string target): AForm("ShrubberyCreationForm", 145, 137)
{
    this->setTarget(target);
}

ShrubberyCreationForm::ShrubberyCreationForm(const ShrubberyCreationForm &other): AForm(other) // copy constructor
{
    this->setTarget(other.getTarget());
}

ShrubberyCreationForm &ShrubberyCreationForm::operator=(const ShrubberyCreationForm &other)
{

    this->setTarget(other.getTarget());
    return *this;
}

ShrubberyCreationForm::~ShrubberyCreationForm()
{
    std::cout << "ShrubberyCreationForm " << this->getName() << " is destroyed" << std::endl;
}

void ShrubberyCreationForm::execute(Bureaucrat const & executor) const
{
    if (executor.getGrade() > this->getExecGrade())
        throw AForm::GradeTooLowException();
    if (!this->getSigned())
        throw AForm::NotSignedException();
    std::string filename = this->getTarget() + "_shrubbery";
    std::ofstream file(filename.c_str());
    if (!file.is_open())
        throw ShrubberyCreationForm::OpenFileException();
    file << "      /\\      " << std::endl;
    file << "     /\\*\\     " << std::endl;
    file << "    /\\O\\*\\    " << std::endl;
    file << "   /\\*\\/\\*\\   " << std::endl;
    file << "  /\\O\\/\\*\\/\\  " << std::endl;
    file << " /\\*\\/\\O\\/\\*\\ " << std::endl;
    file << "/\\O\\/\\*\\/\\O\\/\\ " << std::endl;
    file << "      ||      " << std::endl;
    file << "      ||      " << std::endl;

    file.close();
    std::cout << "ShrubberyCreationForm " << this->getName() << " has been executed" << std::endl;
}

const char *ShrubberyCreationForm::OpenFileException::what() const throw()
{
    return "Error: could not open file";
}
