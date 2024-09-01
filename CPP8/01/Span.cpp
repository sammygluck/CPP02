#include "Span.hpp"

//cannonical

Span::Span() : _N(0)
{
    std::cout << "default constructor" << std::endl;
}

Span::Span(int n) : _N(n)
{   
    std::cout << "constructor" << std::endl;
}

Span::Span(const Span &other)
{
    this->_N = other._N;
    this->_elements = other._elements;
}

Span::~Span()
{
    std::cout << "destructor" << std::endl;
}

Span &Span::operator=(const Span &other)
{
    if (this != &other)
    {
        this->_N = other._N;
        this->_elements = other._elements;
    }
    return (*this);
}

void Span::addNumber(int number)
{
    if (this->_elements.size() >= this->_N)
        throw spanFullException();
    else
        this->_elements.push_back(number)
}

int Span::shortestSpan()
{
    //error check
    //first sort, then compare vec[i] - vec[i - 1], for each element
    //update the variable 
    if (this->_elements.size() < 2)
        throw invalidOperation();
    else
    {
        int minSpan = INT_MAX; //check this
        std::sort(this->_elements.begin(), this->_elements.end());
        for (int i = 1; i < this->_elements.size(); i++)
        {
            int span = this->_elements[i] - this->_elements[i - 1];
            if ( span < minSpan)
                minSpan = span;
        }
        return (minSpan);
    }

}

int Span::longestSpan()
{
    //error check
    //find highest, find lowest; return difference between highest and lowest
    if (this->_elements.size() < 2)
        throw invalidOperation();
    else
    {
        std::vector<int>::iterator min = std::min_element(this->_elements.begin(), this->_elements.end());
        std::vector<int>::iterator max = std::max_element(this->_elements.begin(), this->_elements.end());
        return (*max - *min);
    }
}


template <typename Iterator>
void Span::fillSpan(Iterator begin, Iterator end)
{
    while (begin != end)
    {
        addNumber(*begin);
        begin++;
    }
}

//error catching stuff
const char * Span::spanFullException::what() const throw()
{
    return ("The vector is full, no numbers allowed anymore");
}

const char * Span::invalidOperation::what() const throw()
{
    return ("The current operation isn't allowed");
}