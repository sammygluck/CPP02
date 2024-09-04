// Write a test program in main.cpp that:
// Creates a Data object.
// Serializes the object's address.
// Deserializes the resulting numeric value.
// Checks if the deserialized pointer matches the original object's address.

#include "../incl/Data.hpp"
#include "../incl/Serializer.hpp"


int main()
{
    Data data;
    data.setValue(42);
    std::cout << "Original value: " << data.getValue() << std::endl;

    std::cout << "Serializing..." << std::endl;
    uintptr_t ptr = Serializer::serialize(&data);
    std::cout << "Serialized value: " << ptr << std::endl;
    std::cout << "Deserializing..." << std::endl;
    Data *dataPtr = Serializer::deserialize(ptr);

    std::cout << "Deserialized value: " << dataPtr->getValue() << std::endl;

    if (dataPtr == &data)
        std::cout << "Deserialized pointer matches original pointer" << std::endl;
    else
        std::cout << "Deserialized pointer does not match original pointer" << std::endl;

    return 0;
}
