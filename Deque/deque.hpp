#ifndef __DEQUE_H__
#define __DEQUE_H__

#include <exception>
#include <string>

class Deque_error : public std::exception
{
public:
    Deque_error(const std::string &_errorMessage) : errorMessage("Deque error : " + _errorMessage) {}
    const char *what() const throw() override { return errorMessage.c_str(); }

private:
    std::string errorMessage;
};

template <typename T>
class Deque
{
public:
    Deque(unsigned int _capacity = 0);
    Deque(const Deque &deque);
    void operator=(const Deque &deque);
    ~Deque();
    void push_front(const T &_val);
    void push_back(const T &_val);
    T pop_front();
    T pop_back();
    const T &front() const;
    const T &back() const;
    bool full() const;
    bool empty() const;
    unsigned int size() const;
    unsigned int capacity() const;
    void reserve(unsigned int _capacity);

private:
    T *start;
    T *end;
    T *D_p;
    unsigned int dequeSize;
    unsigned int dequeCapacity;
};

#endif