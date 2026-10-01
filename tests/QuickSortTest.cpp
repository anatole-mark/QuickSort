#include "gtest/gtest.h"
#include "../include/quickSort.hpp"

TEST(QuickSortTest, EmptyRange) {
    std::vector<int> values;

    sort::quicksort(
        values.data(),
        values.data(),
        std::less<int>{}
    );

    EXPECT_TRUE(values.empty());
}

TEST(QuickSortTest, SingleElement) {
    std::vector<int> values{42};

    sort::quicksort(
        values.data(),
        values.data() + values.size(),
        std::less<int>{}
    );

    EXPECT_EQ(values, std::vector<int>{42});
}

TEST(QuickSortTest, AlreadySorted) {
    std::vector<int> values{1, 2, 3, 4, 5};

    sort::quicksort(
        values.data(),
        values.data() + values.size(),
        std::less<int>{}
    );

    EXPECT_EQ(values, (std::vector<int>{1, 2, 3, 4, 5}));
}

TEST(QuickSortTest, ReverseSorted) {
    std::vector<int> values{9, 8, 7, 6, 5, 4, 3, 2, 1};

    sort::quicksort(
        values.data(),
        values.data() + values.size(),
        std::less<int>{}
    );

    EXPECT_EQ(
        values,
        (std::vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9})
    );
}

TEST(QuickSortTest, Duplicates) {
    std::vector<int> values{
        5, 1, 5, 3, 5, 2, 1, 5
    };

    sort::quicksort(
        values.data(),
        values.data() + values.size(),
        std::less<int>{}
    );

    EXPECT_EQ(
        values,
        (std::vector<int>{1, 1, 2, 3, 5, 5, 5, 5})
    );
}

TEST(QuickSortTest, NegativeNumbers) {
    std::vector<int> values{
        -10, 5, 0, -3, 8, -1, 2
    };

    sort::quicksort(
        values.data(),
        values.data() + values.size(),
        std::less<int>{}
    );

    EXPECT_EQ(
        values,
        (std::vector<int>{-10, -3, -1, 0, 2, 5, 8})
    );
}

TEST(QuickSortTest, DescendingOrder) {
    std::vector<int> values{1, 5, 2, 4, 3};

    sort::quicksort(
        values.data(),
        values.data() + values.size(),
        std::greater<int>{}
    );

    EXPECT_EQ(values, (std::vector<int>{5, 4, 3, 2, 1}));
}