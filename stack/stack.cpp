#include <iostream>
#include "stack.hpp"
#include <memory.h>

template <typename T>
Stack<T>::Stack(int stackCapacity) : basePointer((T *)calloc(stackCapacity, sizeof(T))), stackCapacity(stackCapacity), stackSize(0)
{
    if (stackCapacity < 0)
        throw Stack_error("Objects with negative stackCapacity cannot be created.");

    stackPointer = basePointer - 1;
}

template <typename T>
Stack<T>::Stack(const Stack &stack)
{
    stackCapacity = stack.stackCapacity;
    stackSize = stack.stackSize;
    basePointer = (T *)calloc(stackCapacity, sizeof(T));
    memcpy(basePointer, stack.basePointer, sizeof(T) * stackSize);
}

template <typename T>
void Stack<T>::operator=(const Stack &stack)
{
    if (basePointer != stack.basePointer)
    {
        if (stackSize == 0)
            free(basePointer);

        stackCapacity = stack.stackCapacity;
        stackSize = stack.stackSize;
        basePointer = (T *)calloc(stackCapacity, sizeof(T));
        memcpy(basePointer, stack.basePointer, sizeof(T) * stackSize);
    }
}

template <typename T>
Stack<T>::~Stack()
{
    free(basePointer);
    basePointer = nullptr;
    stackPointer = nullptr;
}

template <typename T>
bool Stack<T>::empty() const
{
    return stackSize == 0;
}

template <typename T>
bool Stack<T>::full() const
{
    return stackSize == stackCapacity;
}

template <typename T>
unsigned int Stack<T>::size() const
{
    return stackSize;
}

template <typename T>
unsigned int Stack<T>::capacity() const
{
    return stackCapacity;
}

template <typename T>
const T &Stack<T>::top() const
{
    if (empty())
        throw Stack_error("stack is empty!");

    return *stackPointer;
}

template <typename T>
void Stack<T>::push(const T &val)
{
    if (full())
        reserve(stackCapacity * 2);

    stackSize++;
    *++stackPointer = val;
}

template <typename T>
T Stack<T>::pop()
{
    if (empty())
        throw Stack_error("Stack is empty!");

    stackSize--;
    return *stackPointer--;
}

template <typename T>
void Stack<T>::reserve(unsigned int _reserve)
{
    if (_reserve < stackCapacity)
        throw Stack_error("stackCapacity of reassign is leen than the original stackCapacity");
    if (_reserve == 0)
    {
        if (!(basePointer = (T *)malloc(sizeof(T))))
            throw Stack_error("Out of memory");
        stackPointer = basePointer - 1;
        stackCapacity = 1;
        return;
    }

    T *tmp;
    if (!(tmp = (T *)realloc(basePointer, _reserve * sizeof(T))))
        throw Stack_error("Out of memory");
    else if (tmp != basePointer)
    {
        basePointer = tmp;
        stackPointer = tmp + stackSize - 1;
    }

    stackCapacity = _reserve;
}