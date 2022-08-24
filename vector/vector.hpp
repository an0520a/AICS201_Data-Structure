#pragma once

#include<exception>
#include<string>

#define VECTOR_MAX_SIZE 4294767295ULL

class Vector_error : public std::exception
{
public:
    Vector_error(const std::string &_errorMessage) : errorMessage("Vector error : " + _errorMessage) {}
    const char *what() const throw() override { return errorMessage.c_str(); }

private:
    std::string errorMessage;
};

template <typename T>
class Vector
{
public:
    class Iterator
    {
    public:
        Iterator();
        T &operator*() const;
        T &operator[](int _index) const;
        Iterator operator+(unsigned int _num) const;
        Iterator operator-(unsigned int _num) const;
        Iterator &operator+=(unsigned int _num);
        Iterator &operator-=(unsigned int _num);
        long long operator-(const Iterator &_it) const;
        Iterator &operator=(const Iterator &_it);
        friend typename Vector<T>::Iterator operator+(unsigned int num, const typename Vector<T>::Iterator &_it) { return _it + num; }
        Iterator &operator++();
        Iterator operator++(int);
        Iterator &operator--();
        Iterator operator--(int);
        bool operator==(const Iterator &_it) const;
        bool operator!=(const Iterator &_it) const;
        bool operator>(const Iterator &_it) const;
        bool operator>=(const Iterator &_it) const;
        bool operator<(const Iterator &_it) const;
        bool operator<=(const Iterator &_it) const;

    private:
        Iterator(const Vector *_vector, unsigned int _index);
        const Vector *vector;
        unsigned int index;
        friend class Vector;
    };

    typedef const Iterator const_Iterator;

    Vector(unsigned int _size = 0);
    Vector(unsigned int _numberOfValue, const T &_value);
    Vector(const Iterator &_first, const Iterator &_last);
    Vector(std::initializer_list<T> _list);
    Vector(const Vector &_vector);
    Vector &operator=(const Vector &_vector);
    ~Vector();

    Iterator begin() const;
    Iterator end() const;
    bool empty() const;
    int size() const;
    int capacity() const;
    unsigned long long max_size() const;
    void resize(unsigned int _size, const T &val = 0);
    void reserve(unsigned int _capacity);
    void swap(Vector &_target);
    void assign(const Iterator &_start, const Iterator &_end);
    void assign(unsigned int _size, const T &val);
    void insert(unsigned int _index, const T &val);
    void insert(const Iterator &_position, const T &val);
    void insert(const Iterator &_position, const Iterator &_first, const Iterator &_last);
    void insert(unsigned int index, const Iterator &first, const Iterator &last);
    void push_back(const T &val);
    T pop_back();
    T &at(unsigned int _index) const;
    T &operator[](unsigned int _index) const;
    T &front() const;
    T &back() const;
    void erase(unsigned int _index);
    void erase(unsigned int _first, unsigned int _last);
    void erase(const Iterator &_first, const Iterator &_last);
    void clear();

private:
    T *vec;
    unsigned int vecSize;
    unsigned int vecCapacity;
};