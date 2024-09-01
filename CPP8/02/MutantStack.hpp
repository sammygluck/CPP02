#ifndef MUTANTSTACK_HPP
#define MUTANTSTACK_HPP

#include <stack>
#include <deque>

template <typename T>
class MutantStack : public std::stack<T, std::deque<T>>
{
    public:
        MutantStack<T>(): std::stack<T, std::deque<T>>() {};
        MutantStack<T>(const MutantStack<T> &other): std::stack<T, std::deque<T>>(other){};
        ~MutantStack<T>(){};
        MutantStack<T> &operator=(const MutantStack &other)
        {   
            if (this != &copy)
                std::stack<T, std::deque<T>>::operator=(copy);
            return (*this);
        }

        //expose the underlying iterator stuff
        typename std::deque<T>::iterator begin() {return this->c.begin();}
        typename std::deque<T>::iterator end() {return this->c.end();}
        typename std::deque<T>::const_iterator begin() const {return this->c.begin();}
        typename std::deque<T>::const_iterator end() const {return this->c.end();}
        typename std::deque<T>::reverse_iterator rbegin() {return this->c.rbegin();}
        typename std::deque<T>::reverse_iterator rend() {return this->c.rend();}
        typename std::deque<T>::const_reverse_iterator rbegin() const {return this->c.rbegin();}
        typename std::deque<T>::const_reverse_iterator rend() const {return this->c.rend();}

        
};

#endif