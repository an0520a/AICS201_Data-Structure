#include "vector.hpp"
#include <memory.h>

template <typename T>
Vector<T>::Vector(unsigned int _size) : vec((T *)calloc(_size, sizeof(T))), vecCapacity(_size), vecSize(_size) {}

template <typename T>
Vector<T>::Vector(unsigned int numberOfValue, const T &value)
    : vec((T *)calloc(numberOfValue, sizeof(T))), vecCapacity(numberOfValue), vecSize(numberOfValue)
{
    if (sizeof(T) == 1)
        memset(vec, value, vecSize);
    else
        for (unsigned int i = 0; i < vecSize; i++)
            vec[i] = value;
}

template <typename T>
Vector<T>::Vector(const Iterator &first, const Iterator &last)
    : vec((T *)calloc(last - first, sizeof(T))), vecCapacity(last - first), vecSize(last - first)
{
    if (first.index > last.index)
        throw Vector_error("first Iterator is after the last");
    else if (first.vector != last.vector)
        throw Vector_error("The first iterator and the last iterator point to different vector");

    if (first.index == last.index)
        return;

    memmove(vec, (*first.vector).vec + first.index, (last.index - first.index) * sizeof(T));
}

template <typename T>
Vector<T>::Vector(const Vector &_vector)
    : vec((T *)calloc(_vector.vecCapacity, sizeof(T))), vecCapacity(_vector.vecCapacity), vecSize(_vector.vecSize)
{
    memcpy(vec, _vector.vec, sizeof(T) * vecSize);
}

template <typename T>
Vector<T>::Vector(std::initializer_list<T> _list)
    : vec((T *)calloc(_list.size(), sizeof(T))), vecCapacity(_list.size()), vecSize(_list.size())
{
    memcpy(vec, _list.begin(), sizeof(T) * vecSize);
}

template <typename T>
Vector<T> &Vector<T>::operator=(const Vector &input)
{
    if (vec != input.vec)
    {
        clear();

        vecCapacity = input.vecCapacity;
        vecSize = input.vecSize;
        vec = (T *)calloc(vecCapacity, sizeof(T));

        memcpy(vec, input.vec, sizeof(T) * vecSize);
    }

    return *this;
}

template <typename T>
Vector<T>::~Vector() { free(vec); }

template <typename T>
inline int Vector<T>::size() const { return vecSize; }

template <typename T>
inline int Vector<T>::capacity() const { return vecCapacity; }

template <typename T>
inline bool Vector<T>::empty() const { return vecSize == 0; }

template <typename T>
inline unsigned long long Vector<T>::max_size() const { return VECTOR_MAX_SIZE; }

template <typename T>
inline void Vector<T>::resize(unsigned int _size, const T &val)
{
    if (_size > vecCapacity)
        reserve(_size);
    if (_size > vecSize)
    {
        if (sizeof(T) == 1)
            memset(vec + vecSize, val, _size - vecSize);
        else
        {
            for (unsigned int i = vecSize; i < _size; i++)
                vec[i] = val;
        }
    }

    vecSize = _size;
}

template <typename T>
inline void Vector<T>::reserve(unsigned int _capacity)
{

    if (_capacity < vecCapacity)
        throw Vector_error("capacity to reserve is leen than the original capacity");
    if (_capacity == 0)
    {
        vec = (T *)calloc(1, sizeof(T));
        vecCapacity = 1;
        return;
    }

    T *tmp;

    if (!(tmp = (T *)realloc(vec, sizeof(T) * _capacity)))
        throw Vector_error("Out of Memory");
    else if (tmp != vec)
        vec = tmp;

    vecCapacity = _capacity;
}

template <typename T>
inline void Vector<T>::swap(Vector &target)
{
    T *vec_tmp;
    T vecSize_tmp;
    T vecCapacity_tmp;

    vec = target.vec;
    vecSize = target.vecSize;
    vecCapacity = target.vecCapacity;

    target.vec = vec_tmp;
    target.vecSize = vecSize_tmp;
    target.vecCapacity = vecCapacity_tmp;
}

template <typename T>
void Vector<T>::assign(const Iterator &first, const Iterator &last)
{
    if (first.vector != last.vector)
        throw Vector_error("The first iterator or the last iterator point to different vector");
    else if (first > last)
        throw Vector_error("first Iterator is after the last");

    unsigned int _size = last - first;

    if (_size > vecCapacity)
        reserve(_size);

    int i = 0;
    for (Iterator it = first; it < last; it++, i++)
        vec[i] = *it;

    vecSize = _size;
}

template <typename T>
void Vector<T>::assign(unsigned int _size, const T &val)
{
    if (_size > vecCapacity)
        reserve(_size);

    if (sizeof(T) == 1)
        memset(vec, val, _size);
    else
        for (unsigned int i = 0; i < _size; i++)
            vec[i] = val;

    vecSize = _size;
}

template <typename T>
void Vector<T>::insert(unsigned int index, const T &val)
{
    if (index > vecSize)
        throw Vector_error("An access to an invalid index has occured");
    else if (vecSize == vecCapacity)
        reserve(vecCapacity * 2);

    memmove(vec + index + 1, vec + index, (vecSize - index) * sizeof(T));

    *(vec + index) = val;
    vecSize++;
}

template <typename T>
void Vector<T>::insert(const Iterator &position, const T &val)
{
    if (position.vector != this)
        throw Vector_error("iterator point to different vector");
    else if (position.index > vecSize)
        throw Vector_error("An access to an invalid Iterator has occured");
    else if (vecSize == vecCapacity)
        reserve(vecCapacity * 2);

    memmove(vec + position.index + 1, vec + position.index, (vecSize - position.index) * sizeof(T));

    *(vec + position.index) = val;
    vecSize++;
}

template <typename T>
void Vector<T>::insert(const Iterator &position, const Iterator &first, const Iterator &last)
{
    unsigned int index = position.index;
    if (position.vector != this)
        throw Vector_error("Invaild Iterator");
    else if (index > vecSize)
        throw Vector_error("An access to an invalid index has occured");
    else if (first.index > last.index)
        throw Vector_error("first Iterator is after the last");
    else if (first.vector != last.vector)
        throw Vector_error("The first iterator or the last iterator point to different vector");

    if (first.index == last.index)
        return;
    else if (vecCapacity < vecSize + last.index - first.index)
        reserve((vecSize + last.index - first.index) * 2);

    memmove(vec + index + last.index - first.index, vec + index, (vecSize - index) * sizeof(T));
    memmove(vec + index, (*first.vector).vec + first.index, (last.index - first.index) * sizeof(T));

    vecSize += last.index - first.index;
}

template <typename T>
void Vector<T>::insert(unsigned int index, const Iterator &first, const Iterator &last)
{
    if (index > vecSize)
        throw Vector_error("An access to an invalid index has occured");
    else if (first.index > last.index)
        throw Vector_error("first Iterator is after the last");
    else if (first.vector != last.vector)
        throw Vector_error("The first iterator or the last iterator point to different vector");
    else if (first.index == last.index)
        return;

    if (vecCapacity < vecSize + last.index - first.index)
        reserve((vecSize + last.index - first.index) * 2);

    memmove(vec + index + last.index - first.index, vec + index, (vecSize - index) * sizeof(T));
    memmove(vec + index, (*first.vector).vec + first.index, (last.index - first.index) * sizeof(T));

    vecSize += last.index - first.index;
}

template <typename T>
inline void Vector<T>::push_back(const T &val)
{
    if (vecSize == vecCapacity)
        reserve(vecCapacity * 2);

    *(vec + vecSize) = val;
    vecSize++;
}

template <typename T>
inline T Vector<T>::pop_back()
{
    if (vecSize == 0)
        throw Vector_error("vector is empty");

    T tmp = *(vec + vecSize - 1);
    vecSize--;
    return tmp;
}

template <typename T>
inline T &Vector<T>::at(unsigned int index) const
{
    if (index >= vecSize || index < 0)
        throw Vector_error("An access to an invalid index has occured");

    return *(vec + index);
}

template <typename T>
inline T &Vector<T>::operator[](unsigned int index) const { return *(vec + index); }

template <typename T>
inline T &Vector<T>::front() const { return *vec; }

template <typename T>
inline T &Vector<T>::back() const
{
    if (vecSize == 0)
        throw Vector_error("vector is empty");

    return *(vec + vecSize - 1);
}

template <typename T>
inline void Vector<T>::erase(unsigned int index)
{
    if (index >= vecSize)
        throw Vector_error("An access to an invalid index has occured");

    memmove(vec + index, vec + index + 1, (vecSize - index - 1) * sizeof(T));

    vecSize--;
}

template <typename T>
inline void Vector<T>::erase(unsigned int first, unsigned int last)
{
    if (first >= vecSize || last >= vecSize)
        throw Vector_error("An access to an invalid index has occured");
    else if (first > last)
        throw Vector_error("first is after the last");

    memmove(vec + first, vec + last, (vecSize - last) * sizeof(T));

    vecSize -= last - first;
}

template <typename T>
inline void Vector<T>::erase(const Iterator &first, const Iterator &last)
{
    if (first.vector != this || last.vector != this)
        throw Vector_error("The first iterator or the last iterator point to different vector");
    else if (first.index >= vecSize || last.index >= vecSize)
        throw Vector_error("An access to an invalid index has occured");
    else if (first.index > last.index)
        throw Vector_error("first is after the last");

    memmove(vec + first.index, vec + last.index, (vecSize - last.index) * sizeof(T));

    vecSize -= last.index - first.index;
}

template <typename T>
inline void Vector<T>::clear() { vecSize = 0; }

template <typename T>
inline typename Vector<T>::Iterator Vector<T>::begin() const { return Iterator(this, 0); }

template <typename T>
inline typename Vector<T>::Iterator Vector<T>::end() const { return Iterator(this, vecSize); }

template <typename T>
inline Vector<T>::Iterator::Iterator() : vector(nullptr), index(T(NULL)) {}

template <typename T>
inline Vector<T>::Iterator::Iterator(const Vector *_vector, unsigned int _index) : vector(_vector), index(_index) {}

template <typename T>
inline T &Vector<T>::Iterator::operator*() const { return (*vector)[index]; }

template <typename T>
inline T &Vector<T>::Iterator::operator[](int _num) const { return (*vector)[index + _num]; }

template <typename T>
inline typename Vector<T>::Iterator Vector<T>::Iterator::operator+(unsigned int num) const { return Iterator(vector, index + num); }

template <typename T>
inline typename Vector<T>::Iterator Vector<T>::Iterator::operator-(unsigned int num) const { return Iterator(vector, index - num); }

template <typename T>
inline typename Vector<T>::Iterator &Vector<T>::Iterator::operator+=(unsigned int num)
{
    index += num;
    return *this;
}

template <typename T>
inline typename Vector<T>::Iterator &Vector<T>::Iterator::operator-=(unsigned int num)
{
    index -= num;
    return *this;
}

template <typename T>
inline long long Vector<T>::Iterator::operator-(const Iterator &it) const { return index - it.index; }

template <typename T>
inline typename Vector<T>::Iterator &Vector<T>::Iterator::operator=(const Iterator &it)
{
    vector = it.vector, index = it.index;
    return *this;
}

template <typename T>
inline typename Vector<T>::Iterator &Vector<T>::Iterator::operator++()
{
    index++;
    return *this;
}

template <typename T>
inline typename Vector<T>::Iterator Vector<T>::Iterator::operator++(int)
{
    Iterator tmp(vector, index);
    index++;
    return tmp;
}

template <typename T>
inline typename Vector<T>::Iterator &Vector<T>::Iterator::operator--()
{
    index--;
    return *this;
}

template <typename T>
inline typename Vector<T>::Iterator Vector<T>::Iterator::operator--(int)
{
    Iterator tmp(vector, index);
    index--;
    return tmp;
}

template <typename T>
inline bool Vector<T>::Iterator::operator==(const Iterator &it) const { return vector == it.vector && index == it.index; }

template <typename T>
inline bool Vector<T>::Iterator::operator!=(const Iterator &it) const { return vector != it.vector || index != it.index; }

template <typename T>
inline bool Vector<T>::Iterator::operator>(const Iterator &it) const { return index > it.index; }

template <typename T>
inline bool Vector<T>::Iterator::operator>=(const Iterator &it) const { return index >= it.index; }

template <typename T>
inline bool Vector<T>::Iterator::operator<(const Iterator &it) const { return index < it.index; }

template <typename T>
inline bool Vector<T>::Iterator::operator<=(const Iterator &it) const { return index <= it.index; }