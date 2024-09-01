#include <iostream>
#include <list>
#include <string>
#include <utility>
#include <cstdlib> 
#include <iterator> 

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


void printList(const std::list<int>& toPrint, const std::string& message)
{
    std::cout << message << std::endl;
    for (std::list<int>::const_iterator it = toPrint.begin(); it != toPrint.end(); ++it)
    {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}


// Adjusting pairer function for generic container usage
template <typename InputContainer, typename OutputContainer>
void pairer(const InputContainer& inputContainer, OutputContainer& outputContainer)
{
    typename InputContainer::const_iterator it = inputContainer.begin();
    while (it != inputContainer.end())
    {
        int first = *it++;
        int second = *it++;
        if (first > second)
            outputContainer.push_back(std::make_pair(first, second));
        else
            outputContainer.push_back(std::make_pair(second, first));
    }
}

// Adjusting extraction functions to be generic
template<typename PairContainer>
std::list<int> extractMain(const PairContainer& pairedNumbers) {
    std::list<int> mainChain;

    typename PairContainer::const_iterator it = pairedNumbers.begin();
    while (it != pairedNumbers.end()) {
        mainChain.push_back(it->first);
        ++it;
    }

    return mainChain;
}

template<typename PairContainer>
std::list<int> extractPend(const PairContainer& pairedNumbers) {
    std::list<int> pend;

    typename PairContainer::const_iterator it = pairedNumbers.begin();
    while (it != pairedNumbers.end()) {
        pend.push_back(it->second);
        ++it;
    }

    return pend;
}

// Adjust merge_sort function for lists
template<typename PairList>
void merge_sort(typename PairList::iterator begin, typename PairList::iterator end, PairList& buffer)
{
    size_t length = std::distance(begin, end);
    if (length <= 1)
        return;

    typename PairList::iterator mid = begin;
    std::advance(mid, length / 2);

    merge_sort(begin, mid, buffer);
    merge_sort(mid, end, buffer);

    typename PairList::iterator left = begin;
    typename PairList::iterator right = mid;
    typename PairList::iterator buff_iter = buffer.begin();

    while (left != mid && right != end)
    {
        if ((*left).first < (*right).first)
            *buff_iter++ = *left++;
        else
            *buff_iter++ = *right++;
    }

    while (left != mid)
        *buff_iter++ = *left++;

    while (right != end)
        *buff_iter++ = *right++;

    // Use std::advance to correctly handle non-random-access iterators
    typename PairList::iterator start = buffer.begin();
    std::advance(start, std::distance(buffer.begin(), buff_iter));
    std::copy(buffer.begin(), start, begin);
}


// template<typename Iterator, typename Value>
// Iterator find_insert_position(Iterator begin, Iterator end, const Value& value) {
//     while (begin != end && *begin < value) {
//         ++begin;
//     }
//     return begin;
// }
// position_of_insert = find_insert_position(main.begin(), main.end(), pend_value);

// Helper function to find the correct insertion position in a list
template<typename Iterator, typename Value>
Iterator find_insert_position(Iterator begin, Iterator end, const Value& value) {
    while (begin != end && *begin < value) {
        ++begin;
    }
    return begin;
}

template<typename Container>
void jacobsthal_insertion(Container &pend, Container &main) {
    if (pend.empty()) return; // Early exit if pend is empty

    int jacobsthal_hardcoded_index_adjusted[] = {0, 2, 4, 10, 20, 42, 84, 170, 340, 682, 1364, 2730, 5460};
    int insert_index = jacobsthal_hardcoded_index_adjusted[0];
    int current_j = jacobsthal_hardcoded_index_adjusted[0];
    int insert_count = 0;
    int i = 0;

    typename Container::iterator position_of_insert = main.begin();

    while (insert_count < static_cast<int>(pend.size())) {
        if (insert_index < static_cast<int>(pend.size())) 
        {
            typename Container::iterator pend_it = pend.begin();
            std::advance(pend_it, insert_index); // Safe as insert_index is checked
            int pend_value = *pend_it;

            // Implementing a manual search to find the correct insertion point
            position_of_insert = find_insert_position(main.begin(), main.end(), pend_value);
            main.insert(position_of_insert, pend_value);
            insert_count++;

            if (insert_count == current_j + 1 && i < sizeof(jacobsthal_hardcoded_index_adjusted)/sizeof(jacobsthal_hardcoded_index_adjusted[0]) - 1) 
            {
                i++;
                current_j = jacobsthal_hardcoded_index_adjusted[i];
                insert_index = current_j < static_cast<int>(pend.size()) ? current_j : static_cast<int>(pend.size()) - 1;
            } 
            else
                insert_index = insert_index > 0 ? insert_index - 1 : 0;  // Prevent negative index
        } 
        else
            break;  // Prevent out-of-bounds access if Jacobsthal numbers exceed pend size
    }
}



// template<typename Container>
// void jacobsthal_insertion(Container &pend, Container &main) {
//     if (pend.empty()) return; // Early exit if pend is empty

//     int jacobsthal_hardcoded_index_adjusted[] = {0, 2, 4, 10, 20, 42, 84, 170, 340, 682, 1364, 2730, 5460};
//     int current_j = 0;
//     int insert_count = 0;
//     typename Container::iterator position_of_insert = main.begin();

//     for (int i = 0; i < sizeof(jacobsthal_hardcoded_index_adjusted)/sizeof(jacobsthal_hardcoded_index_adjusted[0]) && current_j < static_cast<int>(pend.size()); ++i) {
//         current_j = jacobsthal_hardcoded_index_adjusted[i];
//         typename Container::iterator pend_it = pend.begin();
//         std::advance(pend_it, current_j);

//         if (current_j < static_cast<int>(pend.size())) {
//             int pend_value = *pend_it;

//             // Find the position to insert the pend_value in the main list
//             position_of_insert = std::lower_bound(main.begin(), main.end(), pend_value);

//             // Insert the pend_value into the main list at the found position
//             main.insert(position_of_insert, pend_value);
//             insert_count++;

//             // Move the insert position forward for next insert
//             if (position_of_insert != main.end()) ++position_of_insert;
//         } 
//         else 
//         {
//             break;  // If current_j exceeds pend size, break the loop
//         }
//     }
// }


std::list<int> ford_johnson(std::list<int>& listNumbers)
{
    bool strangler = false;
    int strangler_number = 0;

    if (listNumbers.size() == 1)
        return listNumbers;
    if (listNumbers.size() % 2 != 0)
    {
        strangler = true;
        strangler_number = listNumbers.back();
        listNumbers.pop_back();
    }

    std::list<std::pair<int, int> > pairedNumbers;
    pairer(listNumbers, pairedNumbers);

    std::list<std::pair<int, int> > buffer(pairedNumbers.size());
    merge_sort(pairedNumbers.begin(), pairedNumbers.end(), buffer);

    std::list<int> mainChain = extractMain(pairedNumbers);
    std::list<int> pend = extractPend(pairedNumbers);
    if (strangler)
        pend.push_back(strangler_number);
    printList(pend, "This is the pend");

    jacobsthal_insertion(pend, mainChain);

    return mainChain;
}

int main(int argc, char **argv)
{
    std::list<int> listNumbers;

    if (argc < 2 || argc > 3001)
    {
        std::cout << "Please provide 1 - 3000 integers to sort" << std::endl;
        return 1;
    }
    if (parseInput(argc, argv, listNumbers))
        return (1);
    printList(listNumbers, "List contents before");
    std::list<int> sorted = ford_johnson(listNumbers);
    printList(sorted, "List contents after");
    return 0;
}
