#include "../incl/Base.hpp"
#include "../incl/A.hpp"
#include "../incl/B.hpp"
#include "../incl/C.hpp"

Base* generate(void)
{
    srand(time(NULL)); //must I prefix with std::?
    int randomNum = rand() % 3;

    switch (randomNum)
    {
        case 0:
            std::cout << "A class created" << std::endl; 
            return new A;
        case 1:
            std::cout << "B class created" << std::endl;
            return new B;
        case 2:
            std::cout << "C class created" << std::endl;
            return new C;
        default:
            return NULL;
    }
}

void identify(Base* p)
{
    if (dynamic_cast<A*>(p) != NULL)
        std::cout << "A" << std::endl;
    else if (dynamic_cast<B*>(p) != NULL)
        std::cout << "B" << std::endl;
    else if (dynamic_cast<C*>(p) != NULL)
        std::cout << "C" << std::endl;
    else
        std::cout << "Unknown class" << std::endl;
}

void identify(Base& p)
{
    try
    {
        A& a = dynamic_cast<A&>(p);
        (void)a;
        std::cout << "A" << std::endl;
        return;
    }
    catch(const std::exception& e)
    {
        // std::cerr << e.what() << '\n';
    }

    try
    {
        B& b = dynamic_cast<B&>(p);
        (void)b;
        std::cout << "B" << std::endl;
        return;
    }
    catch(const std::exception& e)
    {
        
    }
    try
    {
        C& c = dynamic_cast<C&>(p);
        (void)c;
        std::cout << "C" << std::endl;
        return;
    }
    catch(const std::exception& e)
    {
    }
    
    
    
}