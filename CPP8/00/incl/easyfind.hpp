#ifndef EASYFIND_HPP
#define EASYFIND_HPP

#include <stdexcept>
#include <iostream>
#include <vector>

template <typename T>
typename T::const_iterator easyFind(const T &container, int value)
{
    typename T::const_iterator it = container.begin();
    for (;it != container.end(); it++)
    {
        if (*it == value)
            return (it);
    }
    throw std::runtime_error("Value not found in the container");
}

#endif