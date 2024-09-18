#include "../incl/Scalar.hpp"


// //question: do we need all of these constructors and destructors?
//answer: since it can't be instantiated it isn't needed.
// ScalarConverter::ScalarConverter()
// {
// }

// ScalarConverter::~ScalarConverter()
// {
// }

// ScalarConverter::ScalarConverter(const ScalarConverter &copy)
// {
//     *this = copy;
// }

// ScalarConverter &ScalarConverter::operator=(const ScalarConverter &copy)
// {
//     (void)copy;
//     return *this;
// }

void ScalarConverter::convert(std::string str)
{
    int type = _getType(str);

    switch (type)
    {
        case CHAR:
            _charToOthers(str);
            break;
        case INT:
            _intToOthers(str);
            break;
        case FLOAT:
            _floatToOthers(str);
            break;
        case DOUBLE:
            _doubleToOthers(str);
            break;
        case FLOAT_INF_NAN:
            _floatInfNanToOthers(str);
            break;
        case DOUBLE_INF_NAN:
            _doubleInfNanToOthers(str);
            break;
        default:
            std::cout << "Invalid input" << std::endl;
            break;
    }
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
        int dotCount = 0;
        int fCount = 0;
        int digitCount = 0;
        size_t i = 0;

        if (str[0] == '+' || str[0] == '-')
            i++;
        for (; i < str.size(); i++) {
            if (str[i] == '.') 
                dotCount++;
            else if (str[i] == 'f') 
                fCount++;
            else if (std::isdigit(str[i]))
                digitCount++;
            else
                return INVALID;  // Contains non-numeric characters (besides +, -, dot, f)
        }

        if (dotCount > 1 || fCount > 1)
            return INVALID;  // More than one '.' or 'f'

        

        // Based on the count of dots, f's, and digits, determine the type
        // Check for valid float
        if (dotCount == 1 && fCount == 1  && str[str.size() - 1] == 'f' && digitCount > 0 && str.size() > 2)
            return FLOAT;  // Number with a single '.' and a single 'f' at the end
        // Check for valid double 
        else if (dotCount == 1 && fCount == 0 && digitCount > 0 && str.size() > 1)
            return DOUBLE; // Number with a single '.' and no 'f' at the end
        // Check for valid integer
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
    std::stringstream ss(str);
    long value;
    ss >> value;

    if (ss.fail() || !ss.eof() || value < std::numeric_limits<int>::min() || value > std::numeric_limits<int>::max())
    {
        std::cout << "char: impossible" << std::endl;
        std::cout << "int: overflow" << std::endl;
        std::cout << "float: impossible" << std::endl;
        std::cout << "double: impossible" << std::endl;
        return;
    }
    
    if (value < std::numeric_limits<char>::min() || value > std::numeric_limits<char>::max())
        std::cout << "char: impossible" << std::endl;
    else if (isprint(static_cast<char>(value)))
        std::cout << "char: '" << static_cast<char>(value) << "'" << std::endl; 
    else
        std::cout << "char: Non displayable" << std::endl;

    std::cout << "int: " << value << std::endl;

    std::cout << "float: " << std::fixed << std::setprecision(1) << static_cast<float>(value) << "f" << std::endl;
    std::cout << "double: " << std::fixed << std::setprecision(1) << static_cast<double>(value) << std::endl;    
}

void ScalarConverter::_floatToOthers(std::string str)
{
    std::string value_string = str.substr(0, str.size() - 1);
    float value;
    std::stringstream ss(value_string);
    ss >> value;

    if (ss.fail() || !ss.eof())
    {
        std::cout << "char: impossible" << std::endl;
        std::cout << "int: impossible" << std::endl;
        std::cout << "float: overflow" << std::endl;
        std::cout << "double: impossible" << std::endl;
        return;
    }

    if (std::isnan(value) || std::isinf(value) || value < std::numeric_limits<char>::min() || value > std::numeric_limits<char>::max())
        std::cout << "char: impossible" << std::endl;
    else if (isprint(static_cast<char>(value)))
        std::cout << "char: '" << static_cast<char>(value) << "'" << std::endl;
    else
        std::cout << "char: Non displayable" << std::endl;

    if (std::isnan(value) || std::isinf(value) || value < std::numeric_limits<int>::min() || value > std::numeric_limits<int>::max())
        std::cout << "int: impossible" << std::endl;
    else
        std::cout << "int: " << static_cast<int>(value) << std::endl;

    std::cout << "float: " << std::fixed << std::setprecision(1) << value << "f" << std::endl;

    double doubleValue = static_cast<double>(value);
    std::cout << "double: " << std::fixed << std::setprecision(1) << doubleValue << std::endl;
 
}

void ScalarConverter::_doubleToOthers(std::string str)
{
    std::stringstream ss(str);
    double doubleValue;
    ss >> doubleValue;

    if (ss.fail() || !ss.eof())
    {
        std::cout << "char: impossible" << std::endl;
        std::cout << "int: impossible" << std::endl;
        std::cout << "float: invalid input" << std::endl;
        std::cout << "double: invalid input" << std::endl;
        return;
    }

    // Convert to char
    if (std::isnan(doubleValue) || std::isinf(doubleValue) || doubleValue < std::numeric_limits<char>::min() || doubleValue > std::numeric_limits<char>::max())
        std::cout << "char: impossible" << std::endl;
    else if (isprint(static_cast<char>(doubleValue)))
        std::cout << "char: '" << static_cast<char>(doubleValue) << "'" << std::endl;
    else
        std::cout << "char: Non displayable" << std::endl;

    // Convert to int
    if (std::isnan(doubleValue) || std::isinf(doubleValue) || doubleValue < std::numeric_limits<int>::min() || doubleValue > std::numeric_limits<int>::max())
        std::cout << "int: impossible" << std::endl;
    else
        std::cout << "int: " << static_cast<int>(doubleValue) << std::endl;

    // Convert to float
    if (doubleValue < -std::numeric_limits<float>::max() || doubleValue > std::numeric_limits<float>::max())
        std::cout << "float: impossible" << std::endl;
    else
    {
        float floatValue = static_cast<float>(doubleValue);
        std::cout << "float: " << std::fixed << std::setprecision(1) << floatValue << "f" << std::endl;
    }

    std::cout << "double: " << std::fixed << std::setprecision(1) << doubleValue << std::endl;
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