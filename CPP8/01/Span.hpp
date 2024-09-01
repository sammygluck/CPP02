#ifndef SPAN_HPP
#define SPAN_HPP

#include <stdexcept>
#include <iostream>
#include <vector>
#include <algorithm>


class Span
{
    private:
        int _N;
        std::vector<int> _elements;
    public:
        Span();
        Span(int n);
        Span(const Span &other);
        ~Span();
        Span &operator=(const Span &other);

        void addNumber(int number);
        int shortestSpan();
        int longestSpan();
        template <typename Iterator>
        void fillSpan(Iterator begin, Iterator end);

        class spanFullException : public std::exception
        {
            //the implementation for catching the error
            const char * what() const throw();
        };
        class invalidOperation : public std::exception
        {
            //the implementation for catching the error
            const char * what() const throw();
        };

};

#endif