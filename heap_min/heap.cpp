#include "heap.hpp"
#include <cstdlib>

template <typename T>
Heap<T>::Heap() : heapSize(0), heapCapacity(1), heap((T *)calloc(1, sizeof(T))) { last = heap - 1; }

template <typename T>
Heap<T>::~Heap() { free(heap); }

template <typename T>
inline bool Heap<T>::empty() const { return heapSize == 0; }

template <typename T>
inline unsigned int Heap<T>::height() const
{
    int height = 0;
    int tmp = heapSize;

    while (tmp)
    {
        tmp >>= 1, height++;
    }

    return height;
}

template <typename T>
inline unsigned int Heap<T>::size() const { return heapSize; }

template <typename T>
void Heap<T>::insert(const T &val)
{
    if (empty())
    {
        last = heap, *last = val, heapSize++;
        return;
    }

    if (isFull())
        reserve();

    *(++last) = val, heapSize++; // nex last nodet = val, last node = next last node, heapSize++;

    unsigned int tmp_index = heapSize - 1;
    unsigned int tmp_par_index = (heapSize >> 1) - 1; // tmp = last의 부모의 인덱스 값

    while (tmp_index != 0 && *(heap + tmp_index) < *(heap + tmp_par_index))
    {

        T tmp_val = *(heap + tmp_par_index);
        *(heap + tmp_par_index) = *(heap + tmp_index);
        *(heap + tmp_index) = tmp_val;
        T debug_par = *(heap + tmp_par_index);
        T debug_tmp = *(heap + tmp_index);

        tmp_index = tmp_par_index;
        tmp_par_index = ((tmp_index - 1) >> 1);
    }
}

template <typename T>
void Heap<T>::erase(Position &where)
{
    unsigned int tmp_index = where.index;
    unsigned int tmp_leftChild_index = (tmp_index << 1) ^ 1;
    unsigned int tmp_rightChild_index = ((tmp_index + 1) << 1);

    if (tmp_index >= heapSize)
        throw Heap_error("invalid locate");

    *(heap + tmp_index) = *last;
    heapSize--, last--;

    while (1)
    {
        if ((tmp_leftChild_index) >= heapSize && (tmp_rightChild_index >= heapSize))
            break;
        else if (tmp_leftChild_index >= heapSize)
        {
            if (*(heap + tmp_index) <= *(heap + tmp_rightChild_index))
                break;

            T tmp_next_val = *(heap + tmp_rightChild_index);
            *(heap + tmp_rightChild_index) = *(heap + tmp_index);
            *(heap + tmp_index) = tmp_next_val;

            break;
        }
        else if (tmp_rightChild_index >= heapSize)
        {
            if (*(heap + tmp_index) <= *(heap + tmp_leftChild_index))
                break;

            T tmp_next_val = *(heap + tmp_leftChild_index);
            *(heap + tmp_leftChild_index) = *(heap + tmp_index);
            *(heap + tmp_index) = tmp_next_val;

            break;
        }

        if (!(*(heap + tmp_index) > *(heap + tmp_leftChild_index) || *(heap + tmp_index) > *(heap + tmp_rightChild_index)))
            return;

        int tmp_next_index =
            (*(heap + tmp_leftChild_index) < *(heap + tmp_rightChild_index)) ? tmp_leftChild_index : tmp_rightChild_index;

        T tmp_next_val = *(heap + tmp_next_index);
        *(heap + tmp_next_index) = *(heap + tmp_index);
        *(heap + tmp_index) = tmp_next_val;

        tmp_index = tmp_next_index;
        tmp_leftChild_index = ((tmp_index + 1) << 1) - 1;
        tmp_rightChild_index = ((tmp_index + 1) << 1);
    }
}

template <typename T>
void Heap<T>::erase()
{
    unsigned int tmp_index = 0;
    unsigned int tmp_leftChild_index = 1;
    unsigned int tmp_rightChild_index = 2;

    if (tmp_index >= heapSize)
        throw Heap_error("invalid locate");

    *(heap + tmp_index) = *last;
    heapSize--, last--;

    while (1)
    {
        if ((tmp_leftChild_index) >= heapSize && (tmp_rightChild_index >= heapSize))
            break;
        else if (tmp_leftChild_index >= heapSize)
        {
            if (*(heap + tmp_index) <= *(heap + tmp_rightChild_index))
                break;

            T tmp_next_val = *(heap + tmp_rightChild_index);
            *(heap + tmp_rightChild_index) = *(heap + tmp_index);
            *(heap + tmp_index) = tmp_next_val;

            break;
        }
        else if (tmp_rightChild_index >= heapSize)
        {
            if (*(heap + tmp_index) <= *(heap + tmp_leftChild_index))
                break;

            T tmp_next_val = *(heap + tmp_leftChild_index);
            *(heap + tmp_leftChild_index) = *(heap + tmp_index);
            *(heap + tmp_index) = tmp_next_val;

            break;
        }

        if (!(*(heap + tmp_index) > *(heap + tmp_leftChild_index) || *(heap + tmp_index) > *(heap + tmp_rightChild_index)))
            return;

        int tmp_next_index =
            (*(heap + tmp_leftChild_index) < *(heap + tmp_rightChild_index)) ? tmp_leftChild_index : tmp_rightChild_index;

        T tmp_next_val = *(heap + tmp_next_index);
        *(heap + tmp_next_index) = *(heap + tmp_index);
        *(heap + tmp_index) = tmp_next_val;

        tmp_index = tmp_next_index;
        tmp_leftChild_index = ((tmp_index + 1) << 1) - 1;
        tmp_rightChild_index = ((tmp_index + 1) << 1);
    }
}

template <typename T>
void Heap<T>::clear() { heapSize = 0; }

template <typename T>
Heap<T>::Position::Position() : hp(nullptr), index(0) {}

template <typename T>
Heap<T>::Position::Position(const Heap *_heap, int _index) : hp(_heap), index(_index) {}

template <typename T>
inline const T &Heap<T>::Position::getVal() const { return *((*hp).heap + index); }

template <typename T>
inline typename Heap<T>::Position &Heap<T>::Position::setParent()
{
    if (isRoot())
        throw Heap_error("this is Root");
    index = (index - 1) >> 1;

    return *this;
}

template <typename T>
inline typename Heap<T>::Position &Heap<T>::Position::setLeftChild()
{
    int tmp = (index << 1) ^ 1;
    index = tmp;

    return *this;
}

template <typename T>
inline typename Heap<T>::Position &Heap<T>::Position::setRightChild()
{
    int tmp = ((index + 1) << 1);
    index = tmp;

    return *this;
}

template <typename T>
inline typename Heap<T>::Position Heap<T>::Position::getParent() const
{
    return Position(hp, (index - 1) >> 1);
}

template <typename T>
inline typename Heap<T>::Position Heap<T>::Position::getLeftChild() const
{
    int tmp = (index << 1) ^ 1;
    return Position(hp, tmp);
}

template <typename T>
inline typename Heap<T>::Position Heap<T>::Position::getRightChild() const
{
    int tmp = ((index + 1) << 1);
    return Position(hp, tmp);
}

template <typename T>
int Heap<T>::Position::depth() const
{
    int depth = 0;
    int tmp = index + 1;

    while (tmp)
    {
        tmp >>= 1, depth++;
    }

    return depth;
}

template <typename T>
inline bool Heap<T>::Position::isLeftChild() const
{
    if (isRoot())
        return false;
    else
        return index & 1; // 홀수라면 왼쪽 자식이므로 1을 반환
}

template <typename T>
inline bool Heap<T>::Position::isRightChild() const
{
    if (isRoot())
        return false;
    else
        return !(index & 1); // 짝수라면 오른쪽 자식이므로 1을 반환
}

template <typename T>
inline bool Heap<T>::Position::isRoot() const { return (index == 0) ? true : false; }

template <typename T>
inline bool Heap<T>::isFull() const { return heapSize == heapCapacity; }

template <typename T>
inline void Heap<T>::reserve(unsigned int _heapCapacity)
{
    T *tmp;
    if (_heapCapacity <= heapSize)
        throw Heap_error("input heapCapacity less then heapSize");
    if (!(tmp = (T *)realloc(heap, sizeof(T) * (_heapCapacity))))
        throw Heap_error("Out of Memory");
    else if (tmp != heap)
        heap = tmp, last = tmp + heapSize - 1;

    heapCapacity = _heapCapacity;
}

template <typename T>
inline void Heap<T>::reserve()
{
    T *tmp;
    if (!(tmp = (T *)realloc(heap, sizeof(T) * ((heapCapacity << 1) ^ 1))))
        throw Heap_error("Out of Memory");
    else if (tmp != heap)
        heap = tmp, last = tmp + heapSize - 1;

    heapCapacity = (heapCapacity << 1) ^ 1;
}

template <typename T>
inline typename Heap<T>::Position Heap<T>::getRoot() const
{
    if (empty())
        throw Heap_error("Heap is emtpy");

    return Position(this, 0);
}

template <typename T>
inline typename Heap<T>::Position Heap<T>::getLast() const
{
    if (empty())
        throw Heap_error("Heap is emtpy");

    return Position(this, last - heap);
}