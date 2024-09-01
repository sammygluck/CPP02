#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <utility>
#include <cstdlib>  // for std::atoi


// // Function to pair each two numbers such that the larger number comes first
template <typename InputContainer, typename OutputContainer>
void pairer(const InputContainer& inputContainer, OutputContainer& outputContainer)
{
    typename InputContainer::const_iterator it = inputContainer.begin();
    while (it != inputContainer.end())
    {
        int first = *it++; //it saves the derefence and then increments
        int second = *it++;
        if (first > second)
            outputContainer.push_back(std::make_pair(first, second));
        else
            outputContainer.push_back(std::make_pair(second, first));
    }
}

// Extract the larger element (main element) from each pair
std::vector<int> extractMain(const std::vector<std::pair<int, int> >& pairedNumbers) {
    std::vector<int> mainChain;
    mainChain.reserve(pairedNumbers.size()); // Reserve space to avoid reallocations

    for (size_t i = 0; i < pairedNumbers.size(); ++i)
        mainChain.push_back(pairedNumbers[i].first);

    return mainChain;
}

// Extract the smaller element (pend element) from each pair
std::vector<int> extractPend(const std::vector<std::pair<int, int> >& pairedNumbers) {
    std::vector<int> pend;
    pend.reserve(pairedNumbers.size()); // Reserve space to avoid reallocations

    for (size_t i = 0; i < pairedNumbers.size(); ++i)
        pend.push_back(pairedNumbers[i].second);

    return pend;
}

//buffer.resize(length);
void merge_sort(std::vector<std::pair<int, int> >::iterator begin, std::vector<std::pair<int, int> >::iterator end, std::vector<std::pair<int, int> >& buffer)
{
    size_t length = std::distance(begin, end);
    if (length <= 1)
        return;

    std::vector<std::pair<int, int> >::iterator mid = begin + (length / 2);

    merge_sort(begin, mid, buffer);
    merge_sort(mid, end, buffer);

    //merge phase
    std::vector<std::pair<int, int> >::iterator left = begin;
    std::vector<std::pair<int, int> >::iterator right = mid;
    std::vector<std::pair<int, int> >::iterator buff_iter = buffer.begin();

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
        if (insert_index < static_cast<int>(pend.size())) 
        {
            typename Container::iterator pend_it = pend.begin();
            std::advance(pend_it, insert_index); // Safe as insert_index is checked
            int pend_value = *pend_it;

            position_of_insert = std::lower_bound(main.begin(), main.end(), pend_value);
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

void printVector(std::vector<int> toPrint, std::string message)
{
    int VectorSize = toPrint.size();
    std::vector<int>::iterator it = toPrint.begin();
    std::cout << message << std::endl;
    for(std::vector<int>::iterator it = toPrint.begin();it != toPrint.end(); it++)
    {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}

// Function to handle the Ford-Johnson algorithm logic
std::vector<int> ford_johnson(std::vector<int> &vectorNumbers)
{
    bool strangler = false;
    int strangler_number = 0;

    if (vectorNumbers.size() == 1)
        return (vectorNumbers);
    if (vectorNumbers.size() % 2 != 0)
    {
        strangler = true;
        strangler_number = vectorNumbers.back();
        vectorNumbers.pop_back();
    }

    std::vector<std::pair<int, int> > pairedNumbers;
    pairer(vectorNumbers, pairedNumbers);

    std::vector<std::pair<int, int> > buffer(pairedNumbers.size());
    merge_sort(pairedNumbers.begin(), pairedNumbers.end(), buffer);

    std::vector<int> mainChain = extractMain(pairedNumbers);
    std::vector<int> pend = extractPend(pairedNumbers);
    if (strangler == true)
        pend.push_back(strangler_number);
    printVector(pend, "this is the pend");

    jacobsthal_insertion(pend, mainChain);

    return mainChain;
}

int main(int argc, char **argv)
{
    std::vector<int> vectorNumbers;

    if (argc < 2 || argc > 3001)
    {
        std::cout << "Please provide 1 - 3000 integers to sort" << std::endl;
        return 1;
    }
    if (parseInput(argc, argv, vectorNumbers))
        return (1);
    printVector(vectorNumbers, "Vector contents before");
    std::vector<int> sorted = ford_johnson(vectorNumbers);
    printVector(sorted, "Vector contents after");
    return 0;
}