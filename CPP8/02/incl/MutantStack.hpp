#ifndef MUTANTSTACK_HPP
#define MUTANTSTACK_HPP

#include <stack>
#include <deque>

template <typename T>
class MutantStack : public std::stack<T, std::deque<T> >
{
    public:
        MutantStack(): std::stack<T, std::deque<T> >() {};
        MutantStack(const MutantStack<T> &other): std::stack<T, std::deque<T> >(other){};
        ~MutantStack(){};
        MutantStack &operator=(const MutantStack &other)
        {   
            if (this != &other)
                std::stack<T, std::deque<T> >::operator=(other);
            return (*this);
        }

        typedef typename std::deque<T>::iterator iterator;
        typedef typename std::deque<T>::const_iterator const_iterator;
        typedef typename std::deque<T>::reverse_iterator reverse_iterator;
        typedef typename std::deque<T>::const_reverse_iterator const_reverse_iterator;

        //expose the underlying iterator stuff
        iterator end() {return this->c.end();}
        iterator begin() {return this->c.begin();}
        const_iterator begin() const {return this->c.begin();}
        const_iterator end() const {return this->c.end();}
        reverse_iterator rbegin() {return this->c.rbegin();}
        reverse_iterator rend() {return this->c.rend();}
        const_reverse_iterator rbegin() const {return this->c.rbegin();}
        const_reverse_iterator rend() const {return this->c.rend();}

        
};

#endif