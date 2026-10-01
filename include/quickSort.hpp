#pragma once

#include <cstdint>
#include <iostream>

// #define DEBUG

namespace sort
{
    constexpr size_t INSERTION_THRESHOLD = 25;

    template<typename T>
    void printArray(T* first, T* last)
    {
        T* i = first;

        while (i < last)
        {
            std::cout << *(i++) << " ";
        }

        std::cout << "\n";
    }

    template<typename T, typename Cmp>
    size_t hoaresPartition(T* first, T* last, T pivot, Cmp comp)
    {
        T* l{ first };
        T* r{ last - 1 };
        size_t ind = last - first;

        while (true)
        {
            while (l <= r && comp(*l, pivot)) ++l;
            while (l <= r && comp(pivot, *r)) --r;

            if (l > r)
            {
                ind = l - first;
                break;
            }

            std::swap(*l, *r);
            ++l;
            --r;
        }

        #ifdef DEBUG
        std::cout << "Printing from Hoare's partition:\n";
        printArray(first, last);
        #endif

        return ind;
    }

    template<typename T, typename Cmp>
    void insertionSort(T* first, T* last, Cmp comp)
    {
        if (last - first < 2) return;

        T* i = first + 1;

        while (i < last)
        {
            while (i > first && comp(*i, *(i - 1)))
            {
                T temp = std::move(*i);
                *i = std::move(*(i - 1));
                *(i - 1) = std::move(temp);
                --i;
            }
            ++i;
        }

        #ifdef DEBUG
        std::cout << "Printing from Insertion sort:\n";
        printArray(first, last);
        #endif
    }

    template <typename T, typename Cmp>
    void quicksort(T* first, T* last, Cmp comp)
    {
        while (last - first >= 2)
        {
            if (last - first <= INSERTION_THRESHOLD)
            {
                insertionSort(first, last, comp);
                return;
            }

            T* mid = first + (last - first) / 2;
            T pivot = (*first / 3) + (*mid / 3) + (*(last - 1) / 3);

            size_t partition = hoaresPartition(first, last, pivot, comp);

            const size_t l{ partition };
            const size_t r{ last - first - partition };

            if (l < r)
            {
                quicksort(first, first + partition, comp);
                first = first + partition;
            }
            else
            {
                quicksort(first + partition, last, comp);
                last = first + partition;
            }
        }

        #ifdef DEBUG
        std::cout << "Printing from sort:\n";
        printArray(first, last);
        #endif
    }
}
