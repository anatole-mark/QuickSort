#pragma once

#include <cstdint>
#include <iostream>

namespace quicksort
{
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

        std::cout << "Printing from Hoare's partition:\n";
        printArray(first, last);
        return ind;
    }

    template<typename T, typename Cmp>
    void iterSort(T* first, T* last, Cmp comp)
    {
        const size_t n = last - first;

        if (n < 2) return;

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

        std::cout << "Printing from Iterative sort:\n";
        printArray(first, last);
    }

    template <typename T, typename Cmp>
    void sort(T* first, T* last, Cmp comp)
    {
        if (last - first < 2) return;

        if (last - first == 2)
        {
            iterSort(first, last, comp);
            return;
        }

        T* mid = first + (last - first) / 2;
        T pivot = (*first + *mid + *(last - 1)) / 3;

        size_t partition = hoaresPartition(first, last, pivot, comp);

        const size_t l{ partition };
        const size_t r{ last - first - partition };

        if (l < r)
        {
            sort(first, first + partition, comp);
            iterSort(first + partition, last, comp);
        }
        else
        {
            sort(first + partition, last, comp);
            iterSort(first, first + partition, comp);
        }

        std::cout << "Printing from sort:\n";
        printArray(first, last);
    }
}
