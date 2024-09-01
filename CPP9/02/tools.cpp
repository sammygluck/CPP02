// Function to check if a string is a positive integer
bool isPositiveInteger(const std::string &str)
{
    if (str.empty() || !std::isdigit(str[0]))
        return false;
    for (std::string::const_iterator it = str.begin(); it != str.end(); ++it)
    {
        if (!std::isdigit(*it))
            return false;
    }
    int num = std::atoi(str.c_str());
    return num > 0;
}

// Template function to parse and validate input, adding to the container
template <typename Container>
int parseInput(int argc, char **argv, Container &container)
{
    for (int i = 1; i < argc; ++i)
    {
        std::string arg = argv[i];
        if (isPositiveInteger(arg))
        {
            int number = std::atoi(arg.c_str());
            container.push_back(number);
        }
        else
        {
            std::cout << "Invalid input: " << arg << " is not a positive integer." << std::endl;
            return (1);
        }
    }
    return (0);
}