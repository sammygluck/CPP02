#include "../incl/iter.hpp"

int main()
{
    int intArray[] = {1, 2, 3, 4, 5};
    std::string stringArray[] = {"Hello", "World", "!"};

    std::cout << "Printing intArray:" << std::endl;
    iter(intArray, 5, printElement);
    std::cout << "Printing stringArray:" << std::endl;
    iter(stringArray, 3, printElement);

    return 0;
}
