//
// Created by Anatole Mark on 02/10/2026.
//

#pragma once
#include <iostream>

namespace utility
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

    template<typename T>
    void swap(T& lhs, T& rhs) noexcept
    {
        T temp = std::move(lhs);
        lhs = std::move(rhs);
        rhs = std::move(temp);
    }

    template<typename T, typename Cmp>
    T median(T* first, T* last, Cmp comp)
    {
        T* mid = first + (last - first) / 2;

        if (comp(*mid, *first)) swap(*mid, *first);
        if (comp(*(last - 1), *first)) swap(*(last - 1), *first);
        if (comp(*(last - 1), *mid)) swap(*(last - 1), *mid);

        return *mid;
    }
}
