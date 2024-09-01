#include "RPN.hpp"

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        std::cerr << "Usage: ./RPN expression" << std::endl;
        return (1);
    }

    std::string input(argv[1]);
    std::istringstream tokens(input);
    std::stack<int> calcStack;
    std::string token;

    while(tokens >> token)
    {
        if (std::isdigit(token[0]))
        {
            if (token.size() > 1 || std::atoi(token.c_str()) >= 10)
            {
                std::cerr << "Error: Numbers must be single digit and less than 10." << std::endl;
                return 1;
            }
            calcStack.push(std::atoi(token.c_str()));
        }
        else if (token == "+" || token == "-" || token == "*" || token == "/")
        {
            if (calcStack.size() < 2)
            {
                std::cerr << "Error: Not enough operands for operation" << std::endl;
                return (1);
            }
            int operand1 = calcStack.top();
            calcStack.pop();
            int operand2 = calcStack.top();
            calcStack.pop();

            int result = 0;
            if (token == "+")
                result = operand1 + operand2;
            else if (token == "-")
                result = operand1 - operand2;
            else if (token == "*")
                result = operand1 * operand2;
            else if (token == "/")
            {
                if (operand2 == 0)
                {
                    std::cerr << "Error: Division by zero" << std::endl;
                    return (1);
                }
                result = operand1 / operand2;
            }
            calcStack.push(result);    
        }
        else
        {
            std::cerr << "Error: Invalid token '" << token << "'" << std::endl;
            return (1);
        }
    }

    if (calcStack.size() != 1)
    {
        std::cerr << "Error: The input RPN expression doesn't resolve to a single value" << std::endl;
        return (1);
    }

    std::cout << "Result: " << calcStack.top() << std::endl;
    return 0;
}