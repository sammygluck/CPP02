int main(int argc, char **argv)
{
    if (argc < 2)
    {
        std::cout << "At least one int required" << std::endl;
        return 1;
    }

    std::vector<int> vectorNumbers;
    std::list<int> listNumbers;

    // Parse input and fill vector
    parseInput(argc, argv, vectorNumbers);
    
    // Parse input and fill list
    parseInput(argc, argv, listNumbers);

    // Optionally, print the contents of the vector and list to verify
    std::cout << "Vector contents: ";
    for (std::vector<int>::const_iterator it = vectorNumbers.begin(); it != vectorNumbers.end(); ++it)
    {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    std::cout << "List contents: ";
    for (std::list<int>::const_iterator it = listNumbers.begin(); it != listNumbers.end(); ++it)
    {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    return 0;
}
