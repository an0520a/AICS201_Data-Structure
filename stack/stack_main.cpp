#include <iostream>
#include "stack.hpp"
#include "stack.cpp"

using namespace std;

int main()
{
    Stack<int> stack(10);

    int k = 0;

    try
    {
        for (int i = 0; i < 100000; i++)
            stack.push(i);
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }

    try
    {
        for (int i = 0; i < 11; i++)
            cout << stack.pop() << endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
}