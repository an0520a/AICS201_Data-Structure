#ifndef __QUEUE_H__
#define __QUEUE_H__

#include <string>
#include <exception>

template <typename T>
class Queue
{
public:
    Queue(unsigned int _capacity = 0);
    Queue(const Queue &queue);
    void operator=(const Queue &queue);
    ~Queue();
    void push(const T &input);
    T pop();
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
    T *Q_p;
    unsigned int queueSize;
    unsigned int queueCapacity;
};

class Queue_error : public std::exception
{
public:
    Queue_error(const std::string &_errorMessage) : errorMessage("Queue error : " + _errorMessage) {}
    const char *what() const throw() override { return errorMessage.c_str(); }

private:
    std::string errorMessage;
};

#endif