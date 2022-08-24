#ifndef STACK_H
#define STACK_H

#include <string>
#include <exception>

class Stack_error : public std::exception
{
public:
    Stack_error(const std::string &_errorMessage) : errorMessage("Stack error : " + _errorMessage) {}
    const char *what() const throw() override { return errorMessage.c_str(); }

private:
    std::string errorMessage;
};

template <typename T>
class Stack
{
public:
    Stack(int capacity = 0);
    Stack(const Stack &stack);
    void operator=(const Stack &stack);
    ~Stack();
    bool empty() const;
    bool full() const;
    unsigned int size() const;
    unsigned int capacity() const;
    const T &top() const;
    void push(const T &_val);
    T pop();
    void reserve(unsigned int _capacity);

private:
    unsigned int stackSize;
    unsigned int stackCapacity;
    T *basePointer;
    T *stackPointer;
};

#endif