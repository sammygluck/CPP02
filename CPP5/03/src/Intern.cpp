#include "Intern.hpp"

Intern::Intern()
{
}

Intern::Intern(const Intern &other)
{
    *this = other; //see if this is correct
}

Intern &Intern::operator=(const Intern &other)
{
    // (void)other; //to avoid warning
    return *this;
}

Intern::~Intern()
{
}

AForm *Intern::makeForm(std::string formName, std::string target)
{
    std::string forms[3] = {"shrubbery creation", "robotomy request", "presidential pardon"};
    AForm *form = NULL;
    int choice = -1;

    for (int i = 0; i < 3; i++)
    {
        if (formName == forms[i])
        {
            choice = i;
            break;
        }
    }
    switch (choice)
    {
        case 0:
            form = new ShrubberyCreationForm(target);
            break;
        case 1:
            form = new RobotomyRequestForm(target);
            break;
        case 2:
            form = new PresidentialPardonForm(target);
            break;
        default:
            throw Intern::FormNotFoundException();
    }
    return form;
}

const char *Intern::FormNotFoundException::what() const throw()
{
    return "Form not found";
}