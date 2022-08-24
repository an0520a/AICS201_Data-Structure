#include "heap.hpp"

template <typename T, typename cmp_f>
Heap<T, cmp_f>::Heap(cmp_f _cmp) : heapCapacity(0), heapSize(0), cmp(_cmp), heap(nullptr) {}

template <typename T, typename cmp_f>
Heap<T, cmp_f>::~Heap() { free(heap); }

template <typename T, typename cmp_f>
bool Heap<T, cmp_f>::full() const { return heapCapacity == heapSize; }

template <typename T, typename cmp_f>
bool Heap<T, cmp_f>::empty() const { return heapSize == 0; }

template <typename T, typename cmp_f>
size_t Heap<T, cmp_f>::size() const { return heapSize; }

template <typename T, typename cmp_f>
size_t Heap<T, cmp_f>::capacity() const { return heapCapacity; }

template <typename T, typename cmp_f>
typename Heap<T, cmp_f>::Position Heap<T, cmp_f>::root() const { return Position(*this, 0); }

template <typename T, typename cmp_f>
void Heap<T, cmp_f>::insert(const T &val)
{
    if (full())
        reserve();

    unsigned int index = heapSize;
    unsigned int par_index = (index - 1) >> 1;

    T t = val;
    heap[index] = val;

    heapSize++;

    if (!index)
        return; // index가 root면 종료

    while (true)
    {
        if (!index)
            return;

        int cmp_result = cmp(heap[index], heap[par_index]);

        T tmp;

        if (cmp_result < 0)
        {
            tmp = heap[par_index];
            heap[par_index] = heap[index];
            heap[index] = tmp;
        }
        else
            return;

        index = par_index;
        par_index = (index - 1) >> 1;
    }
}

template <typename T, typename cmp_f>
void Heap<T, cmp_f>::erase(const Position &position)
{
    if (empty())
        return;

    unsigned int index = position.pos;
    unsigned int left_index = (index << 1) | 1;
    unsigned int right_index = (index + 1) << 1;

    heap[index] = *(heap + heapSize - 1);

    heapSize--;

    while (left_index < heapSize && right_index < heapSize)
    {
        int result = cmp(heap[left_index], heap[right_index]);
        T tmp;

        if (result <= 0)
        {
            tmp = heap[index];

            if (cmp(heap[index], heap[left_index]) <= 0)
            {
                return;
            }
            tmp = heap[left_index], heap[left_index] = heap[index], heap[index] = tmp, index = left_index;
        }
        else
        {
            if (cmp(heap[index], heap[right_index]) <= 0)
            {
                return;
            }
            tmp = heap[right_index], heap[right_index] = heap[index], heap[index] = tmp, index = right_index;
        }

        left_index = (index << 1) | 1;
        right_index = (index + 1) << 1;
    }

    if (left_index < heapSize && cmp(heap[index], heap[left_index]) > 0)
    {
        T tmp;
        tmp = heap[left_index], heap[left_index] = heap[index], heap[index] = tmp, index = left_index;
    }
}

template <typename T, typename cmp_f>
void Heap<T, cmp_f>::erase()
{
    erase(root());
}

template <typename T, typename cmp_f>
void Heap<T, cmp_f>::reserve()
{
    if (heapCapacity == 0)
    {
        heap = (T *)malloc(sizeof(T));
        heapCapacity = 1;
        return;
    }

    T *tmp;
    if (!(tmp = (T *)realloc(heap, ((heapCapacity << 1) | 1) * sizeof(T))))
        throw Heap_error("realloc failed");

    heap = tmp;
    heapCapacity = (heapCapacity << 1) | 1;
}

template <typename T, typename cmp_f>
void Heap<T, cmp_f>::reserve(size_t _capacity)
{
    if (heapCapacity == 0)
    {
        heap = (T *)malloc(sizeof(T));
        heapCapacity = 1;
        return;
    }

    if (_capacity <= heapCapacity)
        return;

    T *tmp;
    if (!(tmp = (T *)realloc(heap, ((heapCapacity << 1) | 1) * sizeof(T))))
        throw Heap_error("realloc failed");

    heap = tmp;
    heapCapacity = _capacity;
}

template <typename T, typename cmp_f>
Heap<T, cmp_f>::Position::Position(const Heap &_hp, unsigned int _pos) : hp(_hp), pos(_pos) {}

template <typename T, typename cmp_f>
const T &Heap<T, cmp_f>::Position::operator*() const { return *(hp.heap + pos); }

template <typename T, typename cmp_f>
typename Heap<T, cmp_f>::Position Heap<T, cmp_f>::Position::getLeftChi() const { return Position(hp, (pos << 1) | 1); }

template <typename T, typename cmp_f>
typename Heap<T, cmp_f>::Position Heap<T, cmp_f>::Position::getRightChi() const { return Position(hp, (pos + 1) << 1); }

template <typename T, typename cmp_f>
typename Heap<T, cmp_f>::Position Heap<T, cmp_f>::Position::getPar() const { return Position(hp, (pos - 1) >> 1); }

template <typename T, typename cmp_f>
typename Heap<T, cmp_f>::Position &Heap<T, cmp_f>::Position::setLeftChi() { pos = (pos << 1) | 1; return *this; }

template <typename T, typename cmp_f>
typename Heap<T, cmp_f>::Position &Heap<T, cmp_f>::Position::setRightChi() { pos = (pos + 1) << 1; return *this; }

template <typename T, typename cmp_f>
typename Heap<T, cmp_f>::Position& Heap<T, cmp_f>::Position::setPar() { pos = (pos - 1) >> 1; return *this; }