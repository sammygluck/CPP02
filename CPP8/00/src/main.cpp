#include "../incl/easyfind.hpp"
#include <iterator>

int main()
{
    std::vector<int> intVector;
    intVector.push_back(1);
    intVector.push_back(2);
    intVector.push_back(3);
    intVector.push_back(4);
    intVector.push_back(5);

    // Print vector
    std::cout << "Printing intVector:" << std::endl;
    for (std::vector<int>::const_iterator it = intVector.begin(); it != intVector.end(); ++it) // note: using const_iterator for safe read-only access
        std::cout << *it << "; ";
    std::cout << std::endl;

    // Finding existing and non-existing values
    // Existing value
    try
    {
        std::cout << "Looking for 3 in intVector:" << std::endl;
        std::vector<int>::const_iterator it = easyFind(intVector, 3);
        std::cout << "Found 3 at index " << std::distance(static_cast<std::vector<int>::const_iterator>(intVector.begin()), it) << std::endl; // note: explicitly cast begin() to const_iterator
    }
    catch (std::exception &e)
    {
        std::cout << e.what() << std::endl;
    }

    // Non-existing value
    try
    {
        std::cout << "Looking for 6 in intVector:" << std::endl;
        std::vector<int>::const_iterator it = easyFind(intVector, 6);
        std::cout << "Found 6 at index " << std::distance(static_cast<std::vector<int>::const_iterator>(intVector.begin()), it) << std::endl; // note: explicitly cast begin() to const_iterator
    }
    catch (std::exception &e)
    {
        std::cout << e.what() << std::endl;
    }

    return 0;
}


