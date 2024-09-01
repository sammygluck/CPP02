#include "template.hpp"

// Constructor to initialize with command line arguments
PmergeMe::PmergeMe(int argc, char **argv) {
    parseInput(argc, argv);
}

// Helper function to convert command line arguments to vector and list
void PmergeMe::parseInput(int argc, char **argv) {
    for (int i = 1; i < argc; ++i) {
        int num = std::atoi(argv[i]);
        if (num <= 0) {
            std::cerr << "Error: invalid positive integer" << std::endl;
            exit(EXIT_FAILURE);
        }
        vec.push_back(num);
        lst.push_back(num);
    }
}

// Function to print the vector
void PmergeMe::printVector(const std::vector<int>& vec) const {
    for (size_t i = 0; i < vec.size(); ++i) {
        std::cout << vec[i] << " ";
    }
    std::cout << std::endl;
}

// Function to print the list
void PmergeMe::printList(const std::list<int>& lst) const {
    for (std::list<int>::const_iterator it = lst.begin(); it != lst.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}

// Function to sort using vector
void PmergeMe::sortVector() {
    clock_t start = clock();
    vec = mergeSortVector(vec);
    clock_t end = clock();
    double elapsed = double(end - start) / CLOCKS_PER_SEC;
    std::cout << "Time to process a range of " << vec.size() << " elements with std::vector: " << elapsed << "s" << std::endl;
}

// Merge-insert sort for vector
std::vector<int> PmergeMe::mergeSortVector(std::vector<int>& inputVector) {
    if (inputVector.size() <= 1) {
        return inputVector;
    }
    std::vector<int>::iterator middle = inputVector.begin() + inputVector.size() / 2;
    std::vector<int> left(inputVector.begin(), middle);
    std::vector<int> right(middle, inputVector.end());

    left = mergeSortVector(left);
    right = mergeSortVector(right);

    return mergeVector(left, right);
}

// Merge function for vector
std::vector<int> PmergeMe::mergeVector(const std::vector<int>& left, const std::vector<int>& right) {
    std::vector<int> result;
    size_t i = 0, j = 0;
    while (i < left.size() && j < right.size()) {
        if (left[i] <= right[j]) {
            result.push_back(left[i++]);
        } else {
            result.push_back(right[j++]);
        }
    }
    while (i < left.size()) {
        result.push_back(left[i++]);
    }
    while (j < right.size()) {
        result.push_back(right[j++]);
    }
    return result;
}

// Function to sort using list
void PmergeMe::sortList() {
    clock_t start = clock();
    lst = mergeSortList(lst);
    clock_t end = clock();
    double elapsed = double(end - start) / CLOCKS_PER_SEC;
    std::cout << "Time to process a range of " << lst.size() << " elements with std::list: " << elapsed << "s" << std::endl;
}

// Merge-insert sort for list
std::list<int> PmergeMe::mergeSortList(std::list<int>& inputList) {
    if (inputList.size() <= 1) {
        return inputList;
    }
    std::list<int>::iterator middle = inputList.begin();
    std::advance(middle, inputList.size() / 2);
    std::list<int> left(inputList.begin(), middle);
    std::list<int> right(middle, inputList.end());

    left = mergeSortList(left);
    right = mergeSortList(right);

    return mergeList(left, right);
}

// Merge function for list
std::list<int> PmergeMe::mergeList(const std::list<int>& left, const std::list<int>& right) {
    std::list<int> result;
    std::list<int>::const_iterator itLeft = left.begin();
    std::list<int>::const_iterator itRight = right.begin();

    while (itLeft != left.end() && itRight != right.end()) {
        if (*itLeft <= *itRight) {
            result.push_back(*itLeft);
            ++itLeft;
        } else {
            result.push_back(*itRight);
            ++itRight;
        }
    }
    while (itLeft != left.end()) {
        result.push_back(*itLeft);
        ++itLeft;
    }
    while (itRight != right.end()) {
        result.push_back(*itRight);
        ++itRight;
    }
    return result;
}



int main(int argc, char **argv) {
    if (argc < 2) {
        std::cerr << "Error: no input provided." << std::endl;
        return 1;
    }

    PmergeMe pmergeMe(argc, argv);

    std::cout << "Before: ";
    pmergeMe.printVector(pmergeMe.vec); // Print the unsorted vector

    pmergeMe.sortVector(); // Sort and time the vector

    std::cout << "After: ";
    pmergeMe.printVector(pmergeMe.vec); // Print the sorted vector

    std::cout << "Before: ";
    pmergeMe.printList(pmergeMe.lst); // Print the unsorted list

    pmergeMe.sortList(); // Sort and time the list

    std::cout << "After: ";
    pmergeMe.printList(pmergeMe.lst); // Print the sorted list

    return 0;
}

