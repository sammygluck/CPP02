#ifndef SCALAR_HPP
#define SCALAR_HPP

#include <iostream>
#include <string>
#include <cctype>
#include <stdexcept>
#include <climits>
#include <cmath>
#include <limits>
#include <cfloat>
#include <cstdlib>
#include <sstream>
#include <iomanip>

#define INVALID 0
#define CHAR 1
#define INT 2
#define FLOAT 3
#define DOUBLE 4
#define FLOAT_INF_NAN 5
#define DOUBLE_INF_NAN 6

class ScalarConverter
{
    private:
        ScalarConverter();
        ~ScalarConverter();
        ScalarConverter(const ScalarConverter &copy);
        ScalarConverter &operator=(const ScalarConverter &copy);

        static int _getType(std::string str);
        static void _charToOthers(std::string str);
        static void _intToOthers(std::string str);
        static void _floatToOthers(std::string str);
        static void _doubleToOthers(std::string str);
        static void _floatInfNanToOthers(std::string str);
        static void _doubleInfNanToOthers(std::string str);

    public:
        static void convert(std::string str);



};

#endif

