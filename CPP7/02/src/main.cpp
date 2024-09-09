#include "../incl/Bureaucrat.hpp"
#include "../incl/Array.hpp"

int main()
{
    //simple example: int and string
    Array<int> intArray(5);
    //filling the array with values
    for (unsigned int i = 0; i < intArray.size(); i++)
        intArray[i] = i;
    
    Array<std::string> stringArray(3);
    stringArray[0] = "Hello";
    stringArray[1] = "World";
    stringArray[2] = "!";

    std::cout << "Printing intArray:" << std::endl; 
    for (unsigned int i = 0; i < intArray.size(); i++)
        std::cout << intArray[i] << std::endl;
    std::cout << "Printing stringArray:" << std::endl;
    for (unsigned int i = 0; i < stringArray.size(); i++)
        std::cout << stringArray[i] << std::endl;

    
    //more complex example
    Array<Bureaucrat> bureaucratArray(3);
    for (unsigned int i = 0; i < bureaucratArray.size(); i++)
        std::cout << bureaucratArray[i] << std::endl;
    
    //show that a it's a deep copy copy constructor
    Array<int> intArray2(intArray);
    intArray2[0] = 42;
    std::cout << "Printing intArray:" << std::endl;
    for (unsigned int i = 0; i < intArray.size(); i++)
        std::cout << intArray[i] << std::endl;
    std::cout << "Printing intArray2:" << std::endl;
    for (unsigned int i = 0; i < intArray2.size(); i++)
        std::cout << intArray2[i] << std::endl;
    
    //demonstrate the exception
    try
    {
        std::cout << intArray[5] << std::endl;
    }
    catch (std::exception &e)
    {
        std::cout << e.what() << std::endl;
    }


    

}