#pragma once

#include <cstdint>
#include <iostream>

namespace quicksort
{
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
                ind = l - first - 1;
                break;
            }

            std::swap(*l, *r);
            ++l;
            --r;
        }

        return ind;
    }

    template<typename T, typename Cmp>
    void iterSort(T* first, T* last, Cmp comp)
    {
        size_t n = last - first;

        if (n < 2) return;

        for (size_t i = 2; i < n; ++i)
        {
            for (size_t j = 0; j < i - 1; ++j)
            {
                if (comp(*(first + j), *(first + j + 1)))
                {
                    T temp = std::move(*(first + j));
                    *(first + j) = std::move(*(first + j + 1));
                    *(first + j + 1) = std::move(temp);
                }
            }
        }
    }

    template <typename T, typename Cmp>
    void sort(T* first, T* last, Cmp comp)
    {
        if (last - first < 2) return;

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
    }
}
