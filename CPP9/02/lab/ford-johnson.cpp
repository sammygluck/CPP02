#include <iostream>
#include <list>
#include <iterator>

// Utility function to find the insertion point in a sorted list
std::list<int>::iterator findInsertionPoint(std::list<int>& sortedList, int value) {
    std::list<int>::iterator it = sortedList.begin();
    while (it != sortedList.end() && *it <= value) {
        ++it;
    }
    return it;
}

// Function to insert maxima into the sorted list of minima
void insertMaxima(std::list<int>& sortedMinima, const std::list<int>& maxima) {
    for (std::list<int>::const_iterator maxIt = maxima.begin(); maxIt != maxima.end(); ++maxIt) {
        std::list<int>::iterator pos = findInsertionPoint(sortedMinima, *maxIt);
        sortedMinima.insert(pos, *maxIt); // Insert maximum into the correct position
    }
}

void printList(const std::list<int>& list) {
    for (std::list<int>::const_iterator it = list.begin(); it != list.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}

// Function to pair elements and classify them into minima and maxima
void pairAndClassify(const std::list<int>& input, std::list<int>& minima, std::list<int>& maxima) {
    std::list<int>::const_iterator it = input.begin();
    while (it != input.end()) {
        if (std::next(it) != input.end()) {
            if (*it < *std::next(it)) {
                minima.push_back(*it);
                maxima.push_back(*std::next(it));
            } else {
                minima.push_back(*std::next(it));
                maxima.push_back(*it);
            }
            std::advance(it, 2);
        } else {
            // Handle odd element case by adding the last element directly to minima
            minima.push_back(*it);
            break;
        }
    }
}


// Recursive sorting function using the Ford-Johnson algorithm
void fordJohnsonSort(std::list<int>& list) {
    if (list.size() <= 1) {
        return; // Base case: a single element is already sorted
    }

    std::list<int> minima;
    std::list<int> maxima;
    pairAndClassify(list, minima, maxima);

    fordJohnsonSort(minima); // Recursively sort the minima

    list = minima; // Assume minima are now sorted
    insertMaxima(list, maxima); // This function will be defined later
}

int main() 
{
    std::list<int> inputList = {34, 7, 23, 32, 5, 62, 78, 4, 97, 45};
    std::cout << "Original list: ";
    printList(inputList);

    fordJohnsonSort(inputList);

    std::cout << "Sorted list: ";
    printList(inputList);
    
    return 0;
}
