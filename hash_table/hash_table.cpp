#include <iostream>
#include <memory.h>

template <typename T>
inline int basic_cmp(T a, T b);

template <typename T>
void merge_sort(T *arr, unsigned int first, unsigned int last, int(fp)(T, T) = basic_cmp); // stable sort

template <typename T>
inline void merge_sort(T *arr, unsigned int size, int(fp)(T, T) = basic_cmp);

template <typename T>
inline void merge_sort(T *first, T *last, int(fp)(T, T) = basic_cmp);

template <typename T>
long long binary_search(T *arr, unsigned int size, const T &val);

int main()
{
    unsigned int n1, n2;
    scanf(" %u", &n1);

    int *arr = (int *)malloc(n1 * sizeof(int));

    for (unsigned int i = 0; i < n1; i++)
    {
        scanf(" %d", arr + i);
    }

    merge_sort(arr, n1);

    scanf(" %u", &n2);

    for (unsigned int i = 0; i < n2; i++)
    {
        int f, tmp, index, top, low;
        scanf(" %d", &f);

        index = binary_search(arr, n1, f);

        if(index == -1) { printf("0 "); continue;}
        tmp = arr[index];
        top = index;
        low = index;

        while (true)
        {
            if (top == n1 - 1)
                break;

            if (arr[top + 1] == tmp)
                top++;
            else
                break;
        }

        while (true)
        {
            if (low == 0)
                break;

            if (arr[low - 1] == tmp)
                low--;
            else
                break;
        }

        printf("%u ", top - low + 1);
    }

    free(arr);
}

template <typename T>
long long binary_search(T *arr, unsigned int size, const T &val)
{
    int front = 0;
    int back = size - 1;
    int middle = (front + back) / 2;

    while (back > front)
    {
        if (val == arr[middle])
        {
            return middle;
        }
        else if (val < arr[middle])
        {
            back = middle - 1;
        }
        else if (val > arr[middle])
        {
            front = middle + 1;
        }

        middle = (front + back) / 2;
    }

    return -1;
}

template <typename T>
int basic_cmp(T a, T b)
{
    return (a > b) ? 1 : ((a == b) ? 0 : -1);
}

template <typename T>
void merge_sort(T *arr, unsigned int first, unsigned int last, int(fp)(T, T))
{
    if (first == last)
        return;

    unsigned int size = last - first + 1;
    unsigned int mid_f = (first + last) / 2;
    unsigned int mid_l = mid_f + 1;

    T *arr_p = arr + first;
    T *tmp;

    merge_sort(arr, first, mid_f, fp);
    merge_sort(arr, mid_l, last, fp);

    tmp = (T *)malloc(size * sizeof(T));
    memcpy(tmp, arr_p, size * sizeof(T));

    T *p1 = tmp;
    T *p1_last = tmp + (mid_f - first);
    T *p2 = tmp + (mid_l - first);
    T *p2_last = tmp + (last - first);

    for (unsigned int i = 0; i < size; i++)
    {
        if (fp(*p1, *p2) <= 0)
            arr_p[i] = *p1, p1++;
        else
            arr_p[i] = *p2, p2++;

        if (p1 > p1_last)
        {
            memcpy(arr_p + i + 1, p2, (p2_last - p2 + 1) * sizeof(T));
            break;
        }
        if (p2 > p2_last)
        {
            memcpy(arr_p + i + 1, p1, (p1_last - p1 + 1) * sizeof(T));
            break;
        }
    }

    free(tmp);
}

template <typename T>
void merge_sort(T *arr, unsigned int size, int(fp)(T, T))
{
    if (size <= 1)
        return;

    merge_sort(arr, 0, size - 1, fp);
}

template <typename T>
void merge_sort(T *first, T *last, int(fp)(T, T))
{
    if (first == last)
        return;
    return merge_sort(first, 0, last - first - 1, fp);
}