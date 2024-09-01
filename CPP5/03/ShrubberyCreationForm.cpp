#include <ShrubberyCreationForm.hpp>

ShrubberyCreationForm::ShrubberyCreationForm(): AForm("ShrubberyDefault", 145, 137)
{
    this->setTarget("default");
}

ShrubberyCreationForm::ShrubberyCreationForm(std::string target): AForm("ShrubberyCreationForm", 145, 137)
{
    this->setTarget(target);
}

ShrubberyCreationForm::ShrubberyCreationForm(const ShrubberyCreationForm &other)
{
    *this = other; //once again, make sure this works well because most vars are a const
}

ShrubberyCreationForm &ShrubberyCreationForm::operator=(const ShrubberyCreationForm &other)
{
    if (this != &other)
    {
        this->setTarget(other.getTarget());
    }
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
    std::ofstream file(this->getTarget() + "_shrubbery");
    if (!file.is_open())
        throw ShrubberyCreationForm::OpenFileException();
     ile << "      /\\      " << std::endl;
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
