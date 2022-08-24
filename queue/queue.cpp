#include "queue.hpp"

template <typename T>
Queue<T>::Queue(unsigned int _queueCapacity) : queueCapacity(_queueCapacity), queueSize(0), Q_p((T *)calloc(_queueCapacity, sizeof(T)))
{
    if (_queueCapacity < 0)
        throw Queue_error("Objects with negative queueCapacity cannot be created.");

    end = Q_p - 1;
    start = Q_p;
}

template <typename T>
Queue<T>::Queue(const Queue &queue)
{
    queueCapacity = queue.queueCapacity;
    queueSize = queue.queueSize;
    Q_p = (T *)calloc(queueCapacity, sizeof(T));
    start = Q_p + queue.start - queue.Q_p;
    end = Q_p + queue.end - queue.Q_p;
    memcpy(Q_p, queue.Q_p, sizeof(T) * queueCapacity);
}

template <typename T>
void Queue<T>::operator=(const Queue &queue)
{
    if (Q_p != queue.Q_p)
    {
        if (queueSize == 0)
            free(Q_p);

        queueCapacity = queue.queueCapacity;
        queueSize = queue.queueSize;
        Q_p = (T *)calloc(queueCapacity, sizeof(T));
        start = Q_p + queue.start - queue.Q_p;
        end = Q_p + queue.end - queue.Q_p;
        memcpy(Q_p, queue.Q_p, sizeof(T) * queueCapacity);
    }
}

template <typename T>
Queue<T>::~Queue()
{
    free(Q_p);
}

template <typename T>
void Queue<T>::push(const T &input)
{
    if (queueSize >= queueCapacity)
        Queue<T>::reserve(queueCapacity * 2);

    queueSize++;
    end = Q_p + (end - Q_p + 1) % queueCapacity;
    *end = input;
}

template <typename T>
T Queue<T>::pop()
{
    if (!queueSize)
        throw Queue_error("Queue is empty!");

    T temp = *start;

    start = Q_p + (start + 1 - Q_p) % queueCapacity;
    queueSize--;

    return temp;
}

template <typename T>
const T &Queue<T>::front() const
{
    if (!queueSize) throw Queue_error("Queue is empty!");

    return *start;
}

template <typename T>
const T &Queue<T>::back() const
{
    if (!queueSize) throw Queue_error("Queue is empty!");

    return *end;
}

template <typename T>
bool Queue<T>::full() const
{
    if (queueSize == queueCapacity)
        return 1;
    else
        return 0;
}

template <typename T>
bool Queue<T>::empty() const
{
    if (queueSize == 0)
        return 1;
    else
        return 0;
}

template <typename T>
unsigned int Queue<T>::size() const
{
    return queueSize;
}

template <typename T>
unsigned int Queue<T>::capacity() const
{
    return queueCapacity;
}

template <typename T>
void Queue<T>::reserve(unsigned int _queueCapacity)
{
    if (_queueCapacity == 0 && queueCapacity == 0)
    {
        if (!(Q_p = (T *)calloc(1, sizeof(T))))
            throw Queue_error("Out of memory");
        start = Q_p;
        end = Q_p - 1;
        queueCapacity = 1;
        return;
    }

    if (_queueCapacity > queueCapacity)
    {

        T *temp;

        if (!(temp = (T *)realloc(Q_p, sizeof(T) * _queueCapacity)))
            throw Queue_error("Out of memory");

        if (Q_p != temp)
        {
            start = temp + (start - Q_p);
            end = temp + (end - Q_p);
            Q_p = temp;
        }

        if (start > end)
        {
            T *p2 = Q_p + queueCapacity;
            for (T *p = Q_p; p <= end;)
                *(p2++) = *(p++);

            end = start + queueSize - 1;
        }
        queueCapacity = _queueCapacity;

        return;
    }
    else // 사이즈 감소에 대해서는 테스트 해보지 못했음.
    {
        return;
        throw Queue_error("reserve capacity must be greater than origin capacity");
    }
}