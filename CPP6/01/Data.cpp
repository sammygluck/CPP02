#include "Data.hpp"

int Data::getValue() const
{
    return this->_value;
}

void Data::setValue(int value)
{
    this->_value = value;
}