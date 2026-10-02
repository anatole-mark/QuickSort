#pragma once

#include <cstdint>
#include "utility.hpp"

namespace sort
{
    constexpr size_t INSERTION_THRESHOLD = 25;

    template<typename T, typename Cmp>
    static size_t hoaresPartition(T* first, T* last, Cmp comp)
    {
        T pivot = utility::median(first, last, comp);

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

            utility::swap(*l, *r);
            ++l;
            --r;
        }

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
                utility::swap(*i, *(i - 1));
                --i;
            }
            ++i;
        }
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

            size_t partition = hoaresPartition(first, last, comp);

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
    }
}
