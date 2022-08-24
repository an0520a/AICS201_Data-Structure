#ifndef HEAP_H
#define HEAP_H

#include <string>
#include <exception>

class Heap_error : public std::exception
{
public:
    Heap_error(const std::string &_errorMessage) : errorMessage("Heap error : " + _errorMessage) {}
    const char *what() const throw() override { return errorMessage.c_str(); }

private:
    std::string errorMessage;
};

// 최소힙. 배열기반. val이 key값 그 자체라는 가정하에 설계.
template <typename T>
class Heap
{
public:
    Heap();
    ~Heap();
    class Position
    {
    public:
        Position();
        const T &getVal() const;
        Position &setParent();
        Position &setLeftChild();
        Position &setRightChild();
        Position getParent() const;
        Position getLeftChild() const;
        Position getRightChild() const;
        int depth() const;
        bool isLeftChild() const;
        bool isRightChild() const;
        bool isRoot() const;

    private:
        Position(const Heap *_heap = nullptr, int _index = 0);
        const Heap *hp;
        unsigned int index;

        friend class Heap;
    };
    bool empty() const;
    unsigned int height() const;
    unsigned int size() const;
    void insert(const T &val);
    void reserve(); // capacity = capacity * 2 + 1
    void reserve(unsigned int _capacity);
    void erase();                // erase root
    void erase(Position &where); // erase where
    void clear();
    Position getRoot() const;
    Position getLast() const;

private:
    unsigned int heapSize;
    unsigned int heapCapacity;
    T *heap;
    T *last; // (last의 index) + 1 == size

    bool isFull() const;
};

#endif