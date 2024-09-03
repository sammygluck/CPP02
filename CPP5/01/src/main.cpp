#include <iostream>
#include "../incl/Bureaucrat.hpp"
#include "../incl/Form.hpp"

int main() {
    std::cout << "===== Bureaucrat Default Constructor Test =====" << std::endl;
    try {
        Bureaucrat b1;
        std::cout << b1;
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
    }

    std::cout << "\n===== Bureaucrat Parameterized Constructor Tests =====" << std::endl;
    try {
        Bureaucrat b2("John", 1);
        std::cout << b2;

        Bureaucrat b3("Jane", 150);
        std::cout << b3;

        std::cout << "Attempting to create a Bureaucrat with grade 0 (should throw an exception)..." << std::endl;
        Bureaucrat b4("InvalidHigh", 0);
        std::cout << b4;  // This should not be executed
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
    }

    try {
        std::cout << "Attempting to create a Bureaucrat with grade 151 (should throw an exception)..." << std::endl;
        Bureaucrat b5("InvalidLow", 151);
        std::cout << b5;  // This should not be executed
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
    }

    std::cout << "\n===== Bureaucrat Copy Constructor and Assignment Operator Tests =====" << std::endl;
    try {
        Bureaucrat b6("Alice", 42);
        Bureaucrat b7(b6);
        std::cout << "Copy of Alice: " << b7;

        Bureaucrat b8("Bob", 75);
        std::cout << "Before assignment, Bob: " << b8;
        b8 = b6;
        std::cout << "After assignment, Bob: " << b8;
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
    }

    std::cout << "\n===== Bureaucrat Increment and Decrement Tests =====" << std::endl;
    try {
        Bureaucrat b9("Chris", 2);
        std::cout << "Initial Chris: " << b9;

        std::cout << "Incrementing Chris's grade..." << std::endl;
        b9.incrementGrade();
        std::cout << "After increment: " << b9;

        std::cout << "Incrementing Chris's grade again (should throw an exception)..." << std::endl;
        b9.incrementGrade();
        std::cout << "After second increment: " << b9;  // This should not be executed
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
    }

    try {
        Bureaucrat b10("Diana", 149);
        std::cout << "Initial Diana: " << b10;

        std::cout << "Decrementing Diana's grade..." << std::endl;
        b10.decrementGrade();
        std::cout << "After decrement: " << b10;

        std::cout << "Decrementing Diana's grade again (should throw an exception)..." << std::endl;
        b10.decrementGrade();
        std::cout << "After second decrement: " << b10;  // This should not be executed
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
    }

    std::cout << "\n===== Form Constructor Tests =====" << std::endl;
    try {
        Form f1;
        std::cout << f1;

        Form f2("ImportantForm", 50, 25);
        std::cout << f2;

        std::cout << "Attempting to create a Form with sign grade 0 (should throw an exception)..." << std::endl;
        Form f3("InvalidFormHigh", 0, 25);
        std::cout << f3;  // This should not be executed
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
    }

    try {
        std::cout << "Attempting to create a Form with execution grade 151 (should throw an exception)..." << std::endl;
        Form f4("InvalidFormLow", 75, 151);
        std::cout << f4;  // This should not be executed
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
    }

    std::cout << "\n===== Form Signing Tests =====" << std::endl;
    try {
        Bureaucrat b11("Eve", 100);
        Form f5("RegularForm", 100, 50);
        std::cout << f5;

        std::cout << "Eve attempting to sign RegularForm..." << std::endl;
        b11.signForm(f5);
        std::cout << f5;

        std::cout << "Eve attempting to sign RegularForm again (should already be signed)..." << std::endl;
        b11.signForm(f5);
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
    }

    try {
        Bureaucrat b12("Frank", 101);
        Form f6("HighGradeForm", 100, 50);
        std::cout << f6;

        std::cout << "Frank attempting to sign HighGradeForm (should throw an exception)..." << std::endl;
        b12.signForm(f6);
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
