#ifndef ARRAY_HPP
#define ARRAY_HPP

#include <iostream>
#include <string>

template <typename T>
class Array
{
    private:
        T *_array;
        unsigned int _size; // unsigned
    public:
        Array();
        Array(unsigned int n);
        Array(Array const &other);
        ~Array();
        Array &operator=(Array const &other);
        //subscript operator [] overload; is const also necessary
        T &operator[](unsigned int n);
        T const &operator[](unsigned int n) const;

        //error class
        class noAccess : public std::exception
        {
            public:
                const char * what() const throw();
        };

        unsigned int size();
};


template <typename T>
Array<T>::Array() : _array(NULL), _size(0)
{
    std::cout << "Array() constructor called" << std::endl;
}

template <typename T>
Array<T>::Array(unsigned int n) :  _size(n)
{
    this->_array =  new T[n];
}

template <typename T>
Array<T>::Array(Array<T> const &other)
{
    this->_size = other._size;
    this->_array = new T[this->_size];
    if (this->_size > 0)
    {
        for (unsigned int i = 0; i < this->_size; i++)
            this->_array[i] = other._array[i];
    }  
}

template <typename T>
Array<T>::~Array()
{
    delete[] this->_array;
}

template<typename T>
Array<T> &Array<T>::operator=(Array<T> const &other)
{
    if (this != &other)
    {
        unsigned int n = other._size;
        this->_size = n;
        delete[] this->_array;
        this->_array = new T[n];
        for (unsigned int i = 0; i < n; i++)
            this->_array[i] = other._array[i];
    }
    return (*this);
}

template<typename T>
T &Array<T>::operator[](unsigned int n)
{
    //if the value doesn't exists; i.e. out of bounds, return an error
    //else return the value at the index of the array
    if (n > this->_size - 1)
        throw noAccess();
    else
        return (this->_array[n]);
}

template<typename T>
T const &Array<T>::operator[](unsigned int n) const
{
    if (n > this->_size - 1)
        throw noAccess();
    else
        return (this->_array[n]);
}

template<typename T>
const char * Array<T>::noAccess::what() const throw()
{
    return("noAccess exception: the function is reaching out of bounds");
}

template<typename T>
unsigned int Array<T>::size()
{
    return(this->_size);
}


#endif