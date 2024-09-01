#ifndef DATA_HPP
#define DATA_HPP

#include <iostream>
#include <string>


struct Data
{
    private:
        int _value;
    public:
        int getValue() const;
        void setValue(int value);
}

#endif