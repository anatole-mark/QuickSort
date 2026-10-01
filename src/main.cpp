#include <fstream>
#include <iostream>
#include <random>
#include <nanobench.h>
#include "../include/quickSort.hpp"

#define BENCHMARK
// #define WRITE_TO_FILE

static void fillArray(int* first, const size_t n)
{
    std::random_device rd;
    std::mt19937 gen(rd());

    for (int* i = first; i < first + n; ++i)
    {
        *i = gen();
    }
}

static bool intCompare(const int a, const int b)
{
    return a < b;
}

int main()
{
    // benchmarking parameter
    constexpr size_t NUMBER_OF_ITERATIONS_PER_EPOCH = 10000;

    constexpr size_t sz = 100;

    int dummy[sz];
    int arrayHybridSort[sz];
    int arrayInsertionSort[sz];

    /* Since measuring the performance of a sorting algorithm requires constantly passing in
     * an unsorted array, the benchmarking results include the cost of fillArray() as well.
     * Nanobench does provide a setup() function, which could potentially solve this issue, but
     * it comes with the limitation of only being triggered once per epoch. The problem is
     * we're calling sort functions multiple times per epoch. For the purposes of this implementation
     * said issue is neglectable, because we only care about finding the threshold, after which the
     * overhead of sort::quicksort no longer stops it from outperforming insertion sort
    */
    #ifdef BENCHMARK
    const auto fillArrayBenchmark = ankerl::nanobench::Bench()
        .minEpochIterations(NUMBER_OF_ITERATIONS_PER_EPOCH)
        .run("fillArray", [&] { fillArray(dummy, sz); });

    const auto insertionSortBenchmark = ankerl::nanobench::Bench()
        .minEpochIterations(NUMBER_OF_ITERATIONS_PER_EPOCH)
        .run("Insertion sort", [&]
    {
        fillArray(arrayInsertionSort, sz);
        sort::insertionSort(arrayInsertionSort, arrayInsertionSort + sz, intCompare);
    });

    const auto hybridSortBenchmark = ankerl::nanobench::Bench()
        .minEpochIterations(NUMBER_OF_ITERATIONS_PER_EPOCH)
        .run("Hybrid approach sort", [&]
    {
        fillArray(arrayHybridSort, sz);
        sort::quicksort(arrayHybridSort, arrayHybridSort + sz, intCompare);
    });
    #endif

    std::cout << "\n";
    std::cout << "arrayIterative is sorted: " << std::is_sorted(
        arrayInsertionSort, arrayInsertionSort + sz, intCompare) << std::endl;
    std::cout << "array is sorted: " << std::is_sorted(
        arrayHybridSort, arrayHybridSort + sz, intCompare) << std::endl;

    #ifdef WRITE_TO_FILE
    std::ofstream fileOut;
    fileOut.open("../benchmark.csv", std::ios_base::app);

    fileOut << sz << ",";
    fileOut << insertionSortBenchmark.results()[0].average(
        ankerl::nanobench::Result::Measure::elapsed) << ",";
    fileOut << hybridSortBenchmark.results()[0].average(
        ankerl::nanobench::Result::Measure::elapsed) << "\n";

    fileOut.close();
    #endif

    return 0;
}