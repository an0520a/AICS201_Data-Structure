#include <cstdio>
#include <stdexcept>
#include <memory.h>

template <typename T>
class ADD
{
public:
    constexpr T operator()(const T& x, const T& y) const { return x + y; }
};

template <typename T, typename ops = ADD<T>>
class SegmentTree
{
public:
    SegmentTree(T* arr, const size_t& size);
    SegmentTree(T* arr, const size_t& size, const ops& op);
    T getVal(const size_t& begin, const size_t& end) const;
    void change(const size_t& index, const T& val);

private:
    const T& init(size_t idx, size_t begin, size_t end);
    constexpr size_t getLeft(const size_t& idx) const { return idx << 1; }
    constexpr size_t getRight(const size_t& idx) const { return (idx << 1) + 1; }
    constexpr size_t getMidL(const size_t& begin, const size_t& end) const { return (begin + end) / 2; }
    constexpr size_t getMidR(const size_t& begin, const size_t& end) const { return (begin + end) / 2 + 1; }
    const T& getLeftVal(const size_t& idx) { return tree[idx << 1]; }
    const T& getRightVal(const size_t& idx) { return tree[(idx << 1) + 1]; }
    T getValCmp(size_t start, size_t last, size_t idx, size_t begin, size_t end) const;
    const T& changeCmp(size_t begin, size_t end, size_t treeIdx, const size_t& idx, const T& val);
    T* arr;
    T* tree;
    ops op;
    size_t size;
    size_t sizeArr;
};

template <typename T, typename ops>
SegmentTree<T, ops>::SegmentTree(T* _arr, const size_t& _size) : sizeArr(_size)
{
    arr = new T[sizeArr];
    for (size_t i = 0; i < sizeArr; i++) arr[i] = _arr[i];

    size = 1;
    for (size_t i = _size; i; i >>= 1)
    {
        size = (size << 1) + 1;
    }
    size++;

    tree = new T[size];
    init(1, 0, sizeArr - 1);
}

template <typename T, typename ops>
SegmentTree<T, ops>::SegmentTree(T* _arr, const size_t& _size, const ops& _op) : sizeArr(_size), op(_op)
{
    arr = new T[sizeArr];
    for (size_t i = 0; i < sizeArr; i++) arr[i] = _arr[i];

    size = 1;
    for (size_t i = _size; i; i >>= 1)
    {
        size = (size << 1) + 1;
    }
    size++;
    
    tree = new T[size];
    init(1, 0, sizeArr - 1);
}

template <typename T, typename ops>
const T& SegmentTree<T, ops>::init(size_t idx, size_t begin, size_t end)
{
    if(begin == end) return tree[idx] = arr[begin];
    else
    {
        size_t leftIdx = getLeft(idx);
        size_t RightIdx = getRight(idx);
        return tree[idx] = op(init(leftIdx, begin, getMidL(begin, end)), init(RightIdx, getMidR(begin, end), end));
    } 
}

template <typename T, typename ops>
T SegmentTree<T, ops>::getVal(const size_t& begin, const size_t& end) const
{
    return getValCmp(0, sizeArr - 1, 1, begin, end);
}

template <typename T, typename ops>
T SegmentTree<T, ops>::getValCmp(size_t start, size_t last, size_t idx, size_t begin, size_t end) const
{
    if(start == begin && last == end) return tree[idx];
    else
    {
        if(begin <= getMidL(start, last) && end > getMidL(start, last))
        {
            const T& x = getValCmp(start, getMidL(start, last), getLeft(idx), begin, getMidL(start, last));
            const T& y = getValCmp(getMidR(start, last), last, getRight(idx), getMidR(start, last), end);

            return op(x, y);
        }
        else if(begin <= getMidL(start, last))
        {
            return getValCmp(start, getMidL(start, last), getLeft(idx), begin, end);
        }
        else if(end > getMidL(start, last))
        {
            return getValCmp(getMidR(start, last), last, getRight(idx), begin, end);
        }
        else throw std::runtime_error("get Val 오류 발생");
    }
}

template <typename T, typename ops>
void SegmentTree<T, ops>::change(const size_t& index, const T& val)
{
    changeCmp(0, sizeArr - 1, 1, index, val);
}

template <typename T, typename ops>
const T& SegmentTree<T, ops>::changeCmp(size_t begin, size_t end, size_t treeIdx, const size_t& idx, const T& val)
{
    if(begin == idx && end == idx)
    {
        return tree[treeIdx] = arr[idx] = val;
    }
    else
    {
        if(idx <= getMidL(begin, end)) return tree[treeIdx] = op(changeCmp(begin, getMidL(begin, end), getLeft(treeIdx), idx, val), getRightVal(treeIdx));
        else                           return tree[treeIdx] = op(getLeftVal(treeIdx), changeCmp(getMidR(begin, end), end, getRight(treeIdx), idx, val));
    }
}

typedef unsigned int u32;
typedef unsigned long long u64;

int main()
{
    u64 N, Q;
    u64* arr;

    scanf(" %llu %llu", &N, &Q);

    arr = new u64[N];
    for (u64 i = 0; i < N; i++) scanf(" %llu", arr + i);

    SegmentTree<u64> tree(arr, N);

    for (u64 i = 0; i < Q; i++)
    {
        u64 x, y, a, b;
        scanf(" %llu %llu %llu %llu", &x, &y, &a, &b);

        if(x <= y) printf("%llu\n", tree.getVal(x - 1, y - 1));
        else       printf("%llu\n", tree.getVal(y - 1, x - 1));
        tree.change(a - 1, b);
    }

    delete[] arr;
}