#include "Scalar.hpp"


//question: do we need all of these constructors and destructors?
ScalarConverter::ScalarConverter()
{
}

ScalarConverter::~ScalarConverter()
{
}

ScalarConverter::ScalarConverter(const ScalarConverter &copy)
{
    *this = copy;
}

ScalarConverter &ScalarConverter::operator=(const ScalarConverter &copy)
{
    (void)copy;
    return *this;
}

int ScalarConverter::_getType(std::string str)
{
 // Handle special floating-point values and their variants
        if (str == "inff" || str == "+inff" || str == "-inff" || str == "nanf")
            return FLOAT_INF_NAN;
        if (str == "inf" || str == "+inf" || str == "-inf" || str == "nan")
            return DOUBLE_INF_NAN;

        // Check for character type
        if (str.length() == 1 && std::isprint(str[0]) && !std::isdigit(str[0]))
            return CHAR;

        // Analyze numeric types
        bool hasDot = false;
        bool hasF = false;
        int dotCount = 0;
        int fCount = 0;
        int digitCount = 0;
        size_t i = 0;

        if (str[0] == '+' || str[0] == '-')
            i++;
        for (; i < str.size(); i++) {
            if (str[i] == '.') 
            {
                hasDot = true;
                dotCount++;
            } 
            else if (str[i] == 'f') 
            {
                hasF = true;
                fCount++;
            } 
            else if (std::isdigit(str[i]))
                digitCount++;
            else
                return INVALID;  // Contains non-numeric characters (besides +, -, dot, f)
        }

        // Based on the count of dots, f's, and digits, determine the type
        if (dotCount == 1 && fCount == 1 && hasF && str.back() == 'f' && digitCount > 0 && str.size() > 2)
            return FLOAT;  // Number with a single '.' and a single 'f' at the end
        else if (dotCount == 1 && fCount == 0 && digitCount > 0 && str.size() > 1)
            return DOUBLE; // Number with a single '.' and no 'f' at the end
        else if (dotCount == 0 && fCount == 0 && digitCount > 0)
            return INT;    // Number without a '.' or an 'f'
        return INVALID; // If none of the conditions are met
}

void ScalarConverter::_charToOthers(std::string str)
{
    char value = str[0];

    std::cout << "char: '" << value << "'" << std::endl;
    std::cout << "int: " << static_cast<int>(value) << std::endl;
    std::cout << "float: " << static_cast<float>(value) << ".0f" << std::endl;
    std::cout << "double: " << static_cast<double>(value) << ".0" << std::endl;
}

void ScalarConverter::_intToOthers(std::string str)
{
    int value;

    try
    {
        value = std::stoi(str);
    }
    catch(const std::invalid_argument& e)
    {
        std::cout << "char: impossible" << std::endl;
        std::cout << "int: overflow" << std::endl;
        std::cout << "float: impossible" << std::endl;
        std::cout << "double: impossible" << std::endl;
        return;
    }
    catch(const std::out_of_range& e)
    {
        std::cout << "char: impossible" << std::endl;
        std::cout << "int: overflow" << std::endl;
        std::cout << "float: impossible" << std::endl;
        std::cout << "double: impossible" << std::endl;
        return;
    }

    if (std::isprint(value))
        std::cout << "char: '" << static_cast<char>(value) << "'" << std::endl;
    else
        std::cout << "char: non displayable" << std::endl;
    std::cout << "int: " << value << std::endl;
    std::cout << "float: " << static_cast<float>(value) << ".0f" << std::endl;
    std::cout << "double: " << static_cast<double>(value) << ".0" << std::endl;    
}

void ScalarConverter::_floatToOthers(std::string str)
{
    std::string value_string = str.substr(0, str.size() - 1);
    float value;

    try
    {
        value = std::stof(value_string);
    }
    catch(const std::invalid_argument& e)
    {
        std::cout << "char: impossible" << std::endl;
        std::cout << "int: impossible" << std::endl;
        std::cout << "float: overflow" << std::endl;
        std::cout << "double: impossible" << std::endl;
        return;
    }
    catch(const std::out_of_range& e)
    {
        std::cout << "char: impossible" << std::endl;
        std::cout << "int: impossible" << std::endl;
        std::cout << "float: overflow" << std::endl;
        std::cout << "double: impossible" << std::endl;
        return;
    }

    int intValue = static_cast<int>(value);
    if (std::isprint(intValue))
        std::cout << "char: '" << static_cast<char>(intValue) << "'" << std::endl;
    else
        std::cout << "char: non displayable" << std::endl;
    if(value > static_cast<float>(INT_MAX) || value < static_cast<float>(INT_MIN))
        std::cout << "int: overflow" << std::endl;
    else
        std::cout << "int: " << intValue << std::endl;
    std::cout << "float: " << value << "f" << std::endl; //double check this part if need to add .0
    std::cout << "double: " << static_cast<double>(value) << std::cout << ".0" << std::endl;    
}

void ScalarConverter::_doubleToOthers(std::string str)
{
    double value;

    try
    {
        value = std::stod(str);
    }
    catch(const std::invalid_argument& e)
    {
        std::cout << "char: impossible" << std::endl;
        std::cout << "int: impossible" << std::endl;
        std::cout << "float: impossible" << std::endl;
        std::cout << "double: overflow" << std::endl;
        return;
    }
    catch(const std::out_of_range& e)
    {
        std::cout << "char: impossible" << std::endl;
        std::cout << "int: impossible" << std::endl;
        std::cout << "float: impossible" << std::endl;
        std::cout << "double: overflow" << std::endl;
        return;
    }
    int intVal = static_cast<int>(value);
    if (std::isprint(intVal))
        std::cout << "char: '" << static_cast<char>(intVal) << "'" << std::endl;
    else
        std::cout << "char: non displayable" << std::endl;
    if(value > static_cast<double>(INT_MAX) || value < static_cast<double>(INT_MIN))
        std::cout << "int: overflow" << std::endl;
    else
        std::cout << "int: " << intVal << std::endl;
    if(value > static_cast<double>(FLT_MAX) || value < static_cast<double>(FLT_MIN)) //double check this part
        std::cout << "float: overflow" << std::endl;
    else
    {
        std::cout << "float: " << static_cast<float>(value);
        if (value - intVal == 0)
            std::cout << ".0f";
        else
            std::cout << "f";
        std::cout << std::endl;
    }
    std::cout << "double: " << value;
    if (value - intVal == 0)
        std::cout << ".0";
    std::cout << std::endl;
}

void ScalarConverter::_floatInfNanToOthers(std::string str)
{
    std::cout << "char: impossible" << std::endl;
    std::cout << "int: impossible" << std::endl;
    std::cout << "float: " << str << std::endl;
    std::cout << "double: " << str.substr(0, str.length() - 1) << std::endl;
    return;
}

void ScalarConverter::_doubleInfNanToOthers(std::string str)
{
    std::cout << "char: impossible" << std::endl;
    std::cout << "int: impossible" << std::endl;
    std::cout << "float: " << str << "f" << std::endl;
    std::cout << "double: " << str << std::endl;
    return;

}

/*
game plan:
1. takes string as input that could be a char, int, float, or double
2. create for each type a function that will convert the string to the type
3. in each function we first check what the string is and if it's valid, if it's valid we convert it to the type and print it
 A: toChar
 B: toInt
 C: toFloat
 D: toDouble
4. if it's valid we convert it to the type
5. if it's not valid we print an error message

*/

/*
*/