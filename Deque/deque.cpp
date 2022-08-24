#include "deque.hpp"

template <typename T>
Deque<T>::Deque(unsigned int _dequeCapacity) : dequeCapacity(_dequeCapacity), dequeSize(0), D_p((T *)malloc(sizeof(T) * _dequeCapacity))
{
    if (_dequeCapacity < 0)
        throw Deque_error("Objects with negative max_dequeSize cannot be created.");

    start = D_p,
    end = D_p + _dequeCapacity - 1;
}

template <typename T>
Deque<T>::Deque(const Deque &deque)
{
    dequeCapacity = deque.dequeCapacity;
    dequeSize = deque.dequeSize;
    D_p = (T *)calloc(dequeCapacity, sizeof(T));
    start = D_p + deque.start - deque.D_p;
    end = D_p + deque.end - deque.D_p;
    memcpy(D_p, deque.D_p, sizeof(T) * dequeCapacity);
}

template <typename T>
void Deque<T>::operator=(const Deque &deque)
{
    if (D_p != deque.D_p)
    {
        if (dequeSize == 0)
            free(D_p);

        dequeCapacity = deque.dequeCapacity;
        dequeSize = deque.dequeSize;
        D_p = (T *)calloc(dequeCapacity, sizeof(T));
        start = D_p + deque.start - deque.D_p;
        end = D_p + deque.end - deque.D_p;
        memcpy(D_p, deque.D_p, sizeof(T) * dequeCapacity);
    }
}

template <typename T>
Deque<T>::~Deque()
{
    free(D_p);
    D_p = nullptr;
}

template <typename T>
void Deque<T>::push_front(const T &input)
{
    if (dequeSize >= dequeCapacity)
        Deque<T>::reserve(dequeCapacity * 2);

    dequeSize++;
    start = D_p + ((start - 1 - D_p + dequeCapacity) % dequeCapacity);
    *start = input;

    if (dequeCapacity == 1)
        end = start;
}

template <typename T>
void Deque<T>::push_back(const T &input)
{
    if (dequeSize >= dequeCapacity)
        Deque<T>::reserve(dequeCapacity * 2);

    dequeSize++;
    end = D_p + (end + 1 - D_p) % dequeCapacity;
    *end = input;

    if (dequeCapacity == 1)
        end = start;
}

template <typename T>
T Deque<T>::pop_front()
{
    if (!dequeSize)
        throw Deque_error("Deque is empty!");

    T temp = *start;

    start = D_p + (start + 1 - D_p) % dequeCapacity;
    dequeSize--;

    if (dequeCapacity == 1)
        end = start - 1;

    return temp;
}

template <typename T>
T Deque<T>::pop_back()
{
    if (!dequeSize)
        throw Deque_error("Deque is empty!");

    T temp = *end;

    end = D_p + (end - 1 - D_p + dequeCapacity) % dequeCapacity;
    dequeSize--;

    if (dequeCapacity == 1)
        end = start - 1;

    return temp;
}

template <typename T>
const T &Deque<T>::front() const
{
    if (!dequeSize)
        throw Deque_error("deque is empty!");

    return *start;
}

template <typename T>
const T &Deque<T>::back() const
{
    if (!dequeSize)
        throw Deque_error("deque is empty!");

    return *end;
}

template <typename T>
bool Deque<T>::full() const
{
    if (dequeSize == dequeCapacity)
        return 1;
    else
        return 0;
}

template <typename T>
bool Deque<T>::empty() const
{
    if (dequeSize == 0)
        return 1;
    else
        return 0;
}

template <typename T>
unsigned int Deque<T>::size() const
{
    return dequeSize;
}

template <typename T>
unsigned int Deque<T>::capacity() const
{
    return dequeCapacity;
}

template <typename T>
void Deque<T>::reserve(unsigned int _dequeCapacity)
{
    if (_dequeCapacity == 0 && dequeCapacity == 0)
    {
        if (!(D_p = (T *)calloc(1, sizeof(T))))
            throw Deque_error("Out of memory");
        start = D_p;
        end = D_p - 1;
        dequeCapacity = 1;
        return;
    }

    if (_dequeCapacity > 60000)
        throw Deque_error("over the max reserve dequeCapacity");

    if (_dequeCapacity > dequeCapacity)
    {

        T *temp;

        if (!(temp = (T *)realloc(D_p, sizeof(T) * _dequeCapacity)))
            throw Deque_error("Out of memory");

        if (D_p != temp)
        {
            start = temp + (start - D_p);
            end = temp + (end - D_p);
            D_p = temp;
        }

        if (start > end)
        {
            T *p2 = D_p + dequeCapacity;
            for (T *p = D_p; p <= end;)
                *(p2++) = *(p++);

            end = start + dequeSize - 1;
        }
        dequeCapacity = _dequeCapacity;

        return;
    }
    else // 사이즈 감소에 대해서는 테스트 해보지 못했음.
    {
        throw Deque_error("reserve capacity must be greater than origin capacity");
    }
}