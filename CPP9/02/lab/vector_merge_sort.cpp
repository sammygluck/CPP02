#include <iostream>
#include <vector> // changed from <list> to <vector>

// Function to merge two sorted vectors
std::vector<int> merge(const std::vector<int>& left, const std::vector<int>& right) {
    std::vector<int> result;
    std::vector<int>::const_iterator itLeft = left.begin();
    std::vector<int>::const_iterator itRight = right.begin();

    // Merge the two vectors
    while (itLeft != left.end() && itRight != right.end()) {
        if (*itLeft <= *itRight) {
            result.push_back(*itLeft);
            ++itLeft;
        } else {
            result.push_back(*itRight);
            ++itRight;
        }
    }

    // Append remaining elements from the left vector
    while (itLeft != left.end()) {
        result.push_back(*itLeft);
        ++itLeft;
    }

    // Append remaining elements from the right vector
    while (itRight != right.end()) {
        result.push_back(*itRight);
        ++itRight;
    }

    return result;
}

// Function to perform merge sort on a vector
std::vector<int> mergeSort(std::vector<int> &inputVector) { // changed from list to vector
    // Base case: a vector of zero or one elements is already sorted
    if (inputVector.size() <= 1) {
        return inputVector;
    }

    // Split the vector into two halves
    std::vector<int>::iterator middle = inputVector.begin();
    std::advance(middle, inputVector.size() / 2);

    std::vector<int> left(inputVector.begin(), middle); // changed from list to vector
    std::vector<int> right(middle, inputVector.end()); // changed from list to vector

    // Recursively sort both halves
    left = mergeSort(left);
    right = mergeSort(right);

    // Merge the sorted halves
    return merge(left, right);
}

// Function to print the elements of a vector
void printVector(const std::vector<int>& myVector) { // changed from list to vector
    for (std::vector<int>::const_iterator it = myVector.begin(); it != myVector.end(); ++it) { // changed from list to vector
        std::cout << *it << " ";
    }
    std::cout << std::endl; // Print a newline at the end
}

int main(int argc, char **argv) {
    std::vector<int> myVector; // changed from list to vector
    myVector.push_back(12);
    myVector.push_back(45);
    myVector.push_back(8);
    myVector.push_back(6);

    std::cout << "Original vector: "; // changed from list to vector
    printVector(myVector); // changed from list to vector

    myVector = mergeSort(myVector); // changed from list to vector

    std::cout << "Sorted vector: "; // changed from list to vector
    printVector(myVector); // changed from list to vector

    return 0;
}

