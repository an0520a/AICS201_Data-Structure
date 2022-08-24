#include <iostream>
#include "heap.hpp"
#include "heap.cpp"
#include <vector>
#include <algorithm>
#include <random>
#include <time.h>
#include <memory.h>

template <typename T>
class compare
{
public:
    int operator()(const T &a, const T &b) { return (a < b) ? -1 : ((a == b) ? 0 : 1); }
};

template <typename T>
class compare_rev
{
public:
    int operator()(const T &a, const T &b) { return (a < b) ? 1 : ((a == b) ? 0 : -1); }
};

using namespace std;

int main()
{
    compare_rev<int> tmp;
    Heap<int, compare_rev<int>> heap(tmp);

    int arr[] = {0, 89, 6, 1, 3, 5, 3, 1, 5, 6, 4, 6, -8, -4, -3, -140, -50};
    unsigned int size = sizeof(arr) / sizeof(arr[0]);

    for (unsigned int i = 0; i < size; i++)
    {
        heap.insert(arr[i]);
    }

    for (unsigned int i = 0; i < size; i++)
    {
        printf(" %d", *heap.root());
        heap.erase();
    }

    printf("\n");

    {
        compare<int> tmp;
        Heap<int, compare<int>> heap(tmp);
        //Heap<int> heap;

        const int max = 10000000;
        random_device rd;
        mt19937 gen(rd());

        uniform_int_distribution<int> dis(0, max);

        vector<int> unsort;
        unsort.reserve(max);
        for (int i = 0; i < max; i++)
            unsort.push_back(dis(gen));

        clock_t start = clock();

        vector<int> sort1 = unsort;

        heap.reserve(max);

        for (int i = 0; i < max; i++)
            heap.insert(sort1[i]);

        for (int i = 0; i < max; i++)
            sort1[i] = *heap.root(), heap.erase();

        clock_t end = clock();

        cout << "sort what using heap class time(ns) : " << end - start << "\n\n";

        vector<int> sort3 = unsort;

        start = clock();

        sort(&sort3[0], &sort3[sort3.size()]);

        end = clock();

        cout << "quick sort time(ns) : " << end - start << "\n\n";

        bool flag = true;
        for (int i = 0; i < max; i++)
            if (sort1[i] != sort3[i])
                cout << "find different!\n", flag = false;

        if (flag)
            cout << "sort result is not differnt!\n\n";
    }
}