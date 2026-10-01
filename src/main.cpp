#include <iostream>
#include "../include/quickSort.hpp"

int main()
{
    // int arr[] { 5, 3, 8, 4, 2, 7, 1, 10 };
    int arr[] { 9, 10, 9, 16, 19, 12, 8 };
    size_t ind{ 0 };

    quicksort::sort(arr, arr + 7, [](const int a, const int b){ return a < b; });

    for (const int& i : arr)
    {
        std::cout << i << " ";
    }

    return 0;
}