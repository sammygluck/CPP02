#include "../incl/Bureaucrat.hpp"
#include "../incl/PresidentialPardonForm.hpp"
#include "../incl/RobotomyRequestForm.hpp"
#include "../incl/ShrubberyCreationForm.hpp"
#include "../incl/Intern.hpp"
#include <iostream>

int main()
{
    Intern intern;
    Bureaucrat bureaucrat("Bureaucrat", 1);
    AForm *form;

    form = intern.makeForm("presidential pardon", "target");
    bureaucrat.signForm(*form);
    bureaucrat.executeForm(*form);
    delete form;

    form = intern.makeForm("robotomy request", "target");
    bureaucrat.signForm(*form);
    bureaucrat.executeForm(*form);
    delete form;

    form = intern.makeForm("shrubbery creation", "target");
    bureaucrat.signForm(*form);
    bureaucrat.executeForm(*form);
    delete form;


    Intern someRandomIntern;
    AForm* rrf;

    rrf = someRandomIntern.makeForm("robotomy request", "Bender");

    std::cout << *rrf << std::endl;

    delete rrf;

    return 0;
}