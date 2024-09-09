#include "../incl/Span.hpp"

//cannonical

Span::Span() : _N(0)
{
    std::cout << "default constructor" << std::endl;
}

Span::Span(unsigned int n) : _N(n)
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
        this->_elements.push_back(number);
}

unsigned int Span::shortestSpan()
{
    //error check
    //first sort, then compare vec[i] - vec[i - 1], for each element
    //update the variable 
    if (this->_elements.size() < 2)
        throw invalidOperation();

    unsigned int minSpan = std::numeric_limits<unsigned int>::max(); //must be unsigned because the range of span can be negative
    std::sort(this->_elements.begin(), this->_elements.end());
    for (std::size_t i = 1; i < this->_elements.size(); i++)
    {
        int span = this->_elements[i] - this->_elements[i - 1];
        if (static_cast<unsigned int>(span) < minSpan)
            minSpan = static_cast<unsigned int>(span);
    }
    return (minSpan);
}

unsigned int Span::longestSpan()
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

//error catching stuff
const char * Span::spanFullException::what() const throw()
{
    return ("The vector is full, no numbers allowed anymore");
}

const char * Span::invalidOperation::what() const throw()
{
    return ("The current operation isn't allowed");
}