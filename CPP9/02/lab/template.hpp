#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <vector>
#include <list>
#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <iterator>

class PmergeMe {
public:
    // Constructor to initialize with command line arguments
    PmergeMe(int argc, char **argv);

    // Function to print the vector
    void printVector(const std::vector<int>& vec) const;

    // Function to print the list
    void printList(const std::list<int>& lst) const;

    // Function to sort using vector
    void sortVector();

    // Function to sort using list
    void sortList();

private:
    std::vector<int> vec;
    std::list<int> lst;

    // Merge-insert sort for vector
    std::vector<int> mergeSortVector(std::vector<int>& inputVector);
    std::vector<int> mergeVector(const std::vector<int>& left, const std::vector<int>& right);

    // Merge-insert sort for list
    std::list<int> mergeSortList(std::list<int>& inputList);
    std::list<int> mergeList(const std::list<int>& left, const std::list<int>& right);

    // Helper function to convert command line arguments to vector and list
    void parseInput(int argc, char **argv);
};

#endif