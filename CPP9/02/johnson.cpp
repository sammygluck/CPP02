#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <utility>
#include <cstdlib>  // for std::atoi

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
void parseInput(int argc, char **argv, Container &container)
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
        }
    }
}

// Function to pair each two numbers such that the larger number comes first
template <typename Container>
void pairer(const Container &container, Container &pairedContainer)
{
    typename Container::const_iterator it = container.begin();
    while (it != container.end())
    {
        if (it == container.end() || it == --container.end()) //double check this line
            break;
        int first = *it;
        ++it;
        // if (it == container.end())
        // {
        //     pairedContainer.push_back(std::make_pair(first, 0)); // pair with 0 if there's an odd element
        //     break;
        // }
        int second = *it;
        ++it;

        if (first > second)
            pairedContainer.push_back(std::make_pair(first, second));
        else
            pairedContainer.push_back(std::make_pair(second, first));
    }
}

// Extract the larger element (main element) from each pair
std::vector<int> extractMain(const std::vector<std::pair<int, int>>& pairedNumbers) {
    std::vector<int> mainChain;
    mainChain.reserve(pairedNumbers.size()); // Reserve space to avoid reallocations

    for (size_t i = 0; i < pairedNumbers.size(); ++i) {
        mainChain.push_back(pairedNumbers[i].first); // Assuming the first element is the main element
    }

    return mainChain;
}

// Extract the smaller element (pend element) from each pair
std::vector<int> extractPend(const std::vector<std::pair<int, int>>& pairedNumbers) {
    std::vector<int> pend;
    pend.reserve(pairedNumbers.size()); // Reserve space to avoid reallocations

    for (size_t i = 0; i < pairedNumbers.size(); ++i) {
        pend.push_back(pairedNumbers[i].second); // Assuming the second element is the pend element
    }

    return pend;
}


void merge_sort(std::vector<std::pair<int, int> >::iterator begin, std::vector<std::pair<int, int> >::iterator end, std::vector<std::pair<int, int> >& buffer)
{
    size_t length = std::distance(begin, end);
    if (length <= 1)
        return;

    std::vector<std::pair<int, int>>::iterator mid = begin + (length / 2);

    merge_sort(begin, mid, buffer);
    merge_sort(mid, end, buffer);

    //merge phase
    std::vector<std::pair<int, int>>::iterator left = begin;
    std::vector<std::pair<int, int>>::iterator right = mid;
    std::vector<std::pair<int, int>>::iterator buff_iter = buffer.begin();

    while (left != mid && right != end)
    {
        if ((*left).first > (*right).first)
            *buff_iter++ = *left++;
        else
            *buff_iter++ = *right++;
    }

    while (left != mid)
        *buff_iter++ = *left++;

    while (right != end)
        *buff_iter++ = *right++;
    
    std::copy(buffer.begin(), buffer.begin() + length, begin);
}

template<typename Container>
void jacobsthal_insertion(Container &pend, Container &main) {
    if (pend.empty()) return; // Early exit if pend is empty

    int jacobsthal_hardcoded_index_adjusted[] = {0, 2, 4, 10, 20, 42, 84, 170, 340, 682, 1364, 2730, 5460};
    int insert_index = jacobsthal_hardcoded_index_adjusted[0];
    int current_j = jacobsthal_hardcoded_index_adjusted[0];
    int insert_count = 0;
    int i = 0;

    typename Container::iterator position_of_insert;

    while (insert_count < static_cast<int>(pend.size())) {
        if (insert_index < static_cast<int>(pend.size())) {
            typename Container::iterator pend_it = pend.begin();
            std::advance(pend_it, insert_index); // Safe as insert_index is checked
            int pend_value = *pend_it;

            position_of_insert = std::lower_bound(main.begin(), main.end(), pend_value);
            main.insert(position_of_insert, pend_value);
            insert_count++;

            if (insert_count == current_j + 1 && i < sizeof(jacobsthal_hardcoded_index_adjusted)/sizeof(jacobsthal_hardcoded_index_adjusted[0]) - 1) {
                i++;
                current_j = jacobsthal_hardcoded_index_adjusted[i];
                insert_index = current_j < static_cast<int>(pend.size()) ? current_j : static_cast<int>(pend.size()) - 1;
            } else {
                insert_index = insert_index > 0 ? insert_index - 1 : 0;  // Prevent negative index
            }
        } else {
            break;  // Prevent out-of-bounds access if Jacobsthal numbers exceed pend size
        }
    }
}

// Function to handle the Ford-Johnson algorithm logic
std::vector<int> ford_johnson(std::vector<int> &vectorNumbers)
{
    bool strangler = false;
    int strangler_number = 0;

    if (vectorNumbers.size() % 2 != 0)
    {
        strangler = true;
        strangler_number = vectorNumbers.back();
        vectorNumbers.pop_back();
    }

    std::vector<std::pair<int, int>> pairedNumbers;
    pairer(vectorNumbers, pairedNumbers);
    std::vector<std::pair<int, int>> buffer(pairedNumbers.size());
    merge_sort(pairedNumbers.begin(), pairedNumbers.end(), buffer);
    std::vector<int> mainChain = extractMain(pairedNumbers);
    std::vector<int> pend = extractPend(pairedNumbers);
    jacobsthal_insertion(pend, mainChain);

    return mainChain;
}

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
