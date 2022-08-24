#ifndef __HEAP_H__
#define __HEAP_H__

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

template <typename T, typename cmp_f = int (*)(const T &, const T &)>
class Heap
{
public:
    Heap(cmp_f = [](const T &a, const T &b) -> int
         { return (a < b) ? -1 : ((a == b) ? 0 : 1); }); // size must be 0 or 2^n - 1
    ~Heap();

    class Position
    {
    public:
        const T &operator*() const;
        Position getLeftChi() const;
        Position getRightChi() const;
        Position getPar() const;
        Position &setLeftChi();
        Position &setRightChi();
        Position &setPar();

    private:
        Position(const Heap &hp, unsigned int pos);
        const Heap &hp;
        unsigned int pos;
        friend class Heap;
    };

    bool full() const;
    bool empty() const;
    size_t size() const;
    size_t capacity() const;
    void insert(const T &val);
    void erase(const Position &position);
    void erase();
    void reserve(size_t capacity);
    Position root() const;

private:
    void reserve();
    cmp_f cmp;
    size_t heapCapacity;
    size_t heapSize;
    T *heap;
};

#endif