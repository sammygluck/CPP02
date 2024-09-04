#include "../incl/Base.hpp"

Base* generate(void);
void identify(Base* p);
void identify(Base& p);

int main()
{
    Base* base = generate();
    Base &ref = *base;
    std::cout << "Identifying pointer...." << std::endl;
    identify(base);
    std::cout << "Identifying reference...." << std::endl;
    identify(ref);
    delete base;
    return 0;
}