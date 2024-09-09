#ifndef SPAN_HPP
#define SPAN_HPP

#include <stdexcept>
#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>


class Span
{
    private:
        unsigned int _N;
        std::vector<int> _elements;
    public:
        Span();
        Span(unsigned int n);
        Span(const Span &other);
        ~Span();
        Span &operator=(const Span &other);

        void addNumber(int number);
        unsigned int shortestSpan();
        unsigned int longestSpan();
        template <typename Iterator>
        void fillSpan(Iterator begin, Iterator end);

        class spanFullException : public std::exception
        {
            const char * what() const throw();
        };
        class invalidOperation : public std::exception
        {
            const char * what() const throw();
        };

};

template <typename Iterator>
void Span::fillSpan(Iterator begin, Iterator end)
{
    while (begin != end)
    {
        addNumber(*begin);
        begin++;
    }
}

#endif