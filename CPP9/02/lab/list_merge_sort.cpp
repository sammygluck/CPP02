#include <iostream>
#include <list>

std::list<int> merge(std::list<int>& left, std::list<int>& right)
{
    std::list<int> result;
    std::list<int>::const_iterator itLeft = left.begin();
    std::list<int>::const_iterator itRight = right.begin();

    while (itLeft != left.end() && itRight != right.end())
    {
        if (*itLeft <= *itRight)
        {
            result.push_back(*itLeft);
            ++itLeft;
        }
        else
        {
            result.push_back(*itRight);
            ++itRight;
        }
    }

    while (itLeft != left.end())
    {
        result.push_back(*itLeft);
        ++itLeft;
    }

    while (itRight != right.end())
    {
        result.push_back(*itRight);
        ++itRight;
    }

    return result;
}

std::list<int> mergeSort(std::list<int>& inputList)
{
    if (inputList.size() <= 1)
        return inputList;

    std::list<int>::iterator middle = inputList.begin();
    std::advance(middle, inputList.size() /2);

    std::list<int> left(inputList.begin(), middle);
    std::list<int> right(middle, inputList.end());

    left = mergeSort(left);
    right = mergeSort(right);

    return merge(left, right);
}

void printList(const std::list<int>& myList)
{
    std::list<int>::const_iterator it = myList.begin();
    while (it != myList.end())
    {
        std::cout << *it << " ";
        it++;
    }
    std::cout << std::endl;
}

int main(int argc, char **argv)
{
    if (argc < 2)
        return 1;
    (void) argv;
    std::list<int> myList{12, 45, 9, 8, 6};
    int list_size = myList.size();
    std::cout << "The list size is: " << list_size << std::endl;
    printList(myList);

    std::list<int> sortList;
    sortList = mergeSort(myList);
    printList(sortList);
}