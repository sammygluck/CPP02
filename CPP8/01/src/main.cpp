#include "../incl/Span.hpp"
#include <iostream>
#include <vector>
#include <cstdlib> // for rand()

int main()
{
    try {
        // Test 1: Basic functionality with 5 elements
        std::cout << "Test 1: Basic functionality with 5 elements" << std::endl;
        Span sp = Span(5);

        sp.addNumber(6);
        sp.addNumber(3);
        sp.addNumber(17);
        sp.addNumber(9);
        sp.addNumber(11);

        std::cout << "Shortest Span: " << sp.shortestSpan() << std::endl;
        std::cout << "Longest Span: " << sp.longestSpan() << std::endl;

        // Test 2: Exception when adding to a full Span
        std::cout << std::endl << "Test 2: Adding number to full Span (should throw exception)" << std::endl;
        try {
            sp.addNumber(42); // This should throw an exception
        } catch (const std::exception& e) {
            std::cout << "Caught exception: " << e.what() << std::endl;
        }

        // Test 3: Exception when computing spans with less than 2 elements
        std::cout << std::endl << "Test 3: Span with less than 2 elements (should throw exception)" << std::endl;
        Span sp2 = Span(1);
        sp2.addNumber(100);
        try {
            std::cout << "Shortest Span: " << sp2.shortestSpan() << std::endl;
        } catch (const std::exception& e) {
            std::cout << "Caught exception: " << e.what() << std::endl;
        }

        // Test 4: Fill Span using a range of iterators
        std::cout << std::endl << "Test 4: Filling Span with a range of iterators" << std::endl;
        std::vector<int> numbers;
        for (int i = 0; i < 10000; i++) {
            numbers.push_back(rand() % 100000); // Fill with random numbers
        }

        Span sp3 = Span(10000);
        sp3.fillSpan(numbers.begin(), numbers.end());

        std::cout << "Shortest Span: " << sp3.shortestSpan() << std::endl;
        std::cout << "Longest Span: " << sp3.longestSpan() << std::endl;

    } catch (const std::exception& e) {
        std::cout << "Unexpected exception: " << e.what() << std::endl;
    }

    return 0;
}
