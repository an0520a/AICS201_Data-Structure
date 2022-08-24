#include <iostream>
#include "heap.hpp"
#include "heap.cpp"
#include <vector>
#include <algorithm>
#include <random>
#include <time.h>
#include <memory.h>

template <typename T>
int basic_cmp(const T& a, const T& b)
{
    if      (a  < b) return -1;
    else if (a == b) return  0;
    else             return  1;
}

template <typename T>
void merge_sort(T *arr, unsigned int size, int (*cmp)(const T&, const T&) = basic_cmp)
{
    if(size == 1) return;

    merge_sort(arr, (size + 1) / 2);
    merge_sort(arr + (size + 1) / 2, size / 2);

    T* tmp = (T*)malloc(size * sizeof(T));
    memcpy(tmp, arr, size * sizeof(T));

    T* p1 = tmp;
    T* p2 = tmp + (size + 1) / 2;
    T* p1_last = p2;
    T* p2_last = tmp + size;

    for(unsigned int i = 0; i < size; i++)
    {
        if      (p1 == p1_last) { memcpy(arr + i, p2, (size - i) * sizeof(T)); return; }
        else if (p2 == p2_last) { memcpy(arr + i, p1, (size - i) * sizeof(T)); return; }

        if (cmp(*p1, *p2) <= 0) arr[i] = *p1, p1++;
        else                    arr[i] = *p2, p2++;
    }
}

using namespace std;

int main()
{
    cout << "----------------start Heap test----------------\n\n";

    Heap<int> heap;

    cout << "empty test : " << heap.empty() << endl;
    cout << "heap insert, 9 5 20 13 7 6 1" << endl;
    heap.insert(9);
    heap.insert(5);
    heap.insert(20);
    heap.insert(13);
    heap.insert(7);
    heap.insert(6);
    heap.insert(1);

    cout << "empty test : " << heap.empty() << endl;
    cout << "size test : " << heap.size() << endl;

    cout << "heap out & erase test : ";
    while (heap.size())
    {
        Heap<int>::Position tmp = heap.getRoot();
        cout << heap.getRoot().getVal() << " ", heap.erase(tmp);
    }
    cout << endl;

    cout << "heap clear" << endl;
    cout << "heap insert, 9 5 7 6 1" << endl;
    heap.insert(9);
    heap.insert(5);
    heap.insert(7);
    heap.insert(6);
    heap.insert(1);

    Heap<int>::Position position = heap.getRoot();
    cout << "Position test , isDeapth(Expected value : 1) : " << position.depth() << endl;
    cout << "Position test, Root : " << position.getVal() << endl;
    cout << "Position test, Root of left childe : " << position.getLeftChild().getVal() << endl;
    cout << "Position test, Root of Right childe : " << position.getRightChild().getVal() << endl;
    position.setLeftChild();
    cout << "Position test , isDeapth(Expected value : 2) : " << position.depth() << endl;
    cout << "Position test , set reft child" << endl;
    cout << "Position test , get reft child : " << position.getLeftChild().getVal() << endl;
    cout << "Position test , get right child : " << position.getRightChild().getVal() << endl;
    position.setRightChild();
    cout << "Position test , set Right child" << endl;
    cout << "Position test , isDeapth(Expected value : 3) : " << position.depth() << endl;
    cout << "Position test , get Parentd : " << position.getParent().getVal() << endl;
    cout << "Position test , set Parentd : " << position.setParent().getVal() << endl;

    cout << endl;

    {
        Heap<int> heap;

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
            sort1[i] = heap.getRoot().getVal(), heap.erase();

        clock_t end = clock();

        cout << "sort what using heap class time(ns) : " << end - start << "\n\n";

        vector<int> sort3 = unsort;

        start = clock();

        merge_sort(&sort3[0], sort3.size());

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