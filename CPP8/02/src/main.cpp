#include "../incl/MutantStack.hpp"

#include "MutantStack.hpp"
#include <iostream>
#include <list>

int main()
{
    // Create a MutantStack of integers
    MutantStack<int> mstack;

    // Push elements onto the stack
    mstack.push(5);
    mstack.push(17);

    // Check the top element
    std::cout << "Top element: " << mstack.top() << std::endl;

    // Pop the top element
    mstack.pop();

    // Check the size after pop
    std::cout << "Size after pop: " << mstack.size() << std::endl;

    // Push more elements onto the stack
    mstack.push(3);
    mstack.push(5);
    mstack.push(737);
    mstack.push(0);

    // Iterating through the stack using iterators
    MutantStack<int>::iterator it = mstack.begin();
    MutantStack<int>::iterator ite = mstack.end();

    std::cout << "MutantStack elements:" << std::endl;
    while (it != ite)
    {
        std::cout << *it << std::endl;
        ++it;
    }

    // Copying stack to another MutantStack
    std::stack<int> s(mstack);
    std::cout << "Copied stack size: " << s.size() << std::endl;

    // Compare output with std::list
    std::list<int> lstack;
    lstack.push_back(5);
    lstack.push_back(17);
    lstack.pop_back();
    lstack.push_back(3);
    lstack.push_back(5);
    lstack.push_back(737);
    lstack.push_back(0);

    std::cout << "List elements:" << std::endl;
    for (std::list<int>::iterator lit = lstack.begin(); lit != lstack.end(); ++lit)
    {
        std::cout << *lit << std::endl;
    }

    return 0;
}
