#include "../incl/Bureaucrat.hpp"
#include "../incl/PresidentialPardonForm.hpp"
#include "../incl/RobotomyRequestForm.hpp"
#include "../incl/ShrubberyCreationForm.hpp"
#include <iostream>

int main()
{
    try
    {
        // Create some Bureaucrats with different grades
        Bureaucrat lowRank("Low Rank", 137);
        Bureaucrat midRank("Mid Rank", 45);
        Bureaucrat highRank("High Rank", 5);

        // Create different forms
        PresidentialPardonForm presidentialForm("Alice");
        RobotomyRequestForm robotomyForm("Bob");
        ShrubberyCreationForm shrubberyForm("Garden");

        // Test signing and executing the forms with different Bureaucrats
        std::cout << "\n--- Testing Shrubbery Creation Form ---\n";
        shrubberyForm.beSigned(lowRank); // Should succeed
        shrubberyForm.execute(lowRank);  // Should succeed

        std::cout << "\n--- Testing Robotomy Request Form ---\n";
        robotomyForm.beSigned(midRank);  // Should succeed
        robotomyForm.execute(midRank);   // Should succeed, but randomly might throw RobotomizeException

        std::cout << "\n--- Testing Presidential Pardon Form ---\n";
        presidentialForm.beSigned(highRank); // Should succeed
        presidentialForm.execute(highRank);  // Should succeed

        // Test errors by trying to sign with too low a grade
        std::cout << "\n--- Testing Error Handling ---\n";
        PresidentialPardonForm anotherForm("Charlie");
        anotherForm.beSigned(midRank); // Should throw GradeTooLowException
        anotherForm.execute(lowRank);  // Should not reach here due to previous exception
    }
    catch (const std::exception &e)
    {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    try
    {
        // Test decrementing Bureaucrat grade too far
        std::cout << "\n--- Testing Bureaucrat Grade Exceptions ---\n";
        Bureaucrat tooHigh("Too High", 1);
        tooHigh.incrementGrade(); // Should throw GradeTooHighException
    }
    catch (const std::exception &e)
    {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    try
    {
        // Test executing a form without signing
        std::cout << "\n--- Testing Form Not Signed Exception ---\n";
        Bureaucrat midRank("Mid Rank", 75); // Recreate midRank here
        ShrubberyCreationForm unsignedForm("Forest");
        unsignedForm.execute(midRank); // Should throw NotSignedException
    }
    catch (const std::exception &e)
    {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    return 0;
}
