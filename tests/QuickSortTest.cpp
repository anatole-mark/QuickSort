#include "gtest/gtest.h"
#include "../include/quickSort.hpp"

#include <algorithm>
#include <functional>
#include <array>
#include <limits>
#include <string>
#include <vector>

constexpr std::size_t TEST_SIZE = 100;

TEST(QuickSortTest, EmptyArray)
{
    int a[0]{ };

    sort::quicksort(a, a, std::less());

    EXPECT_TRUE(std::is_sorted(a, a));
}

TEST(QuickSortTest, SingleElement)
{
    int a[]{ 42 };

    sort::quicksort(a, a + 1, std::less());

    EXPECT_EQ(a[0], 42);
}


TEST(QuickSortTest, TwoElementsAlreadySorted)
{
    int a[]{ 1, 2 };

    sort::quicksort(a, a + 2, std::less());

    EXPECT_EQ(a[0], 1);
    EXPECT_EQ(a[1], 2);
}


TEST(QuickSortTest, TwoElementsReverseSorted)
{
    int a[]{ 2, 1 };

    sort::quicksort(a, a + 2, std::less());

    EXPECT_EQ(a[0], 1);
    EXPECT_EQ(a[1], 2);
}


TEST(QuickSortTest, SmallOddArray)
{
    int a[]{ 5, 1, 4, 2, 3 };

    sort::quicksort(a, a + 5, std::less());

    EXPECT_TRUE(std::is_sorted(a, a + 5));
}


TEST(QuickSortTest, SmallEvenArray)
{
    int a[]{ 8, 3, 7, 1, 6, 2 };

    sort::quicksort(a, a + 6, std::less());

    EXPECT_TRUE(std::is_sorted(a, a + 6));
}


TEST(QuickSortTest, RandomIntegers)
{
    int a[TEST_SIZE];

    for (std::size_t i = 0; i < TEST_SIZE; ++i)
        a[i] = static_cast<int>((i * 37) % TEST_SIZE);

    sort::quicksort(a, a + TEST_SIZE, std::less());

    EXPECT_TRUE(std::is_sorted(a, a + TEST_SIZE));
}


TEST(QuickSortTest, AlreadySortedIntegers)
{
    int a[TEST_SIZE];

    for (std::size_t i = 0; i < TEST_SIZE; ++i)
        a[i] = static_cast<int>(i);

    sort::quicksort(a, a + TEST_SIZE, std::less());

    EXPECT_TRUE(std::is_sorted(a, a + TEST_SIZE));
}


TEST(QuickSortTest, ReverseSortedIntegers)
{
    int a[TEST_SIZE];

    for (std::size_t i = 0; i < TEST_SIZE; ++i)
        a[i] = static_cast<int>(TEST_SIZE - i);

    sort::quicksort(a, a + TEST_SIZE, std::less());

    EXPECT_TRUE(std::is_sorted(a, a + TEST_SIZE));
}


TEST(QuickSortTest, AllEqualIntegers)
{
    int a[TEST_SIZE];

    std::fill(std::begin(a), std::end(a), 42);

    sort::quicksort(a, a + TEST_SIZE, std::less());

    EXPECT_TRUE(std::all_of(
        std::begin(a),
        std::end(a),
        [](const int value) { return value == 42; }
    ));
}


TEST(QuickSortTest, ManyDuplicateIntegers)
{
    int a[TEST_SIZE];

    for (std::size_t i = 0; i < TEST_SIZE; ++i)
        a[i] = static_cast<int>(i % 5);

    sort::quicksort(a, a + TEST_SIZE, std::less());

    EXPECT_TRUE(std::is_sorted(a, a + TEST_SIZE));
}


TEST(QuickSortTest, NegativeIntegers)
{
    int a[TEST_SIZE];

    for (std::size_t i = 0; i < TEST_SIZE; ++i)
        a[i] = static_cast<int>(i) - 50;

    std::reverse(std::begin(a), std::end(a));

    sort::quicksort(a, a + TEST_SIZE, std::less());

    EXPECT_TRUE(std::is_sorted(a, a + TEST_SIZE));
}


TEST(QuickSortTest, ExtremeIntegers)
{
    int a[TEST_SIZE];

    for (std::size_t i = 0; i < TEST_SIZE; ++i)
        a[i] = static_cast<int>(i);

    a[17] = std::numeric_limits<int>::min();
    a[73] = std::numeric_limits<int>::max();

    sort::quicksort(a, a + TEST_SIZE, std::less());

    EXPECT_TRUE(std::is_sorted(a, a + TEST_SIZE));
}


TEST(QuickSortTest, Doubles)
{
    double a[TEST_SIZE];

    for (std::size_t i = 0; i < TEST_SIZE; ++i)
        a[i] = static_cast<double>((i * 17) % TEST_SIZE) / 3.0;

    sort::quicksort(a, a + TEST_SIZE, std::less());

    EXPECT_TRUE(std::is_sorted(a, a + TEST_SIZE));
}


TEST(QuickSortTest, Floats)
{
    float a[TEST_SIZE];

    for (std::size_t i = 0; i < TEST_SIZE; ++i)
        a[i] = static_cast<float>((i * 23) % TEST_SIZE) / 7.0f;

    sort::quicksort(a, a + TEST_SIZE, std::less());

    EXPECT_TRUE(std::is_sorted(a, a + TEST_SIZE));
}


TEST(QuickSortTest, Characters)
{
    char a[TEST_SIZE];

    for (std::size_t i = 0; i < TEST_SIZE; ++i)
        a[i] = static_cast<char>('a' + (i % 26));

    std::reverse(std::begin(a), std::end(a));

    sort::quicksort(a, a + TEST_SIZE, std::less());

    EXPECT_TRUE(std::is_sorted(a, a + TEST_SIZE));
}


TEST(QuickSortTest, Strings)
{
    std::string a[TEST_SIZE];

    const std::string words[] = {
        "banana",
        "apple",
        "orange",
        "kiwi",
        "grape",
        "watermelon",
        "pear"
    };

    for (std::size_t i = 0; i < TEST_SIZE; ++i)
        a[i] = words[(i * 3) % std::size(words)];

    sort::quicksort(a, a + TEST_SIZE, std::less());

    EXPECT_TRUE(std::is_sorted(a, a + TEST_SIZE));
}


TEST(QuickSortTest, StringsReverseSorted)
{
    std::string a[TEST_SIZE];

    for (std::size_t i = 0; i < TEST_SIZE; ++i)
        a[i] = std::to_string(TEST_SIZE - i);

    sort::quicksort(a, a + TEST_SIZE, std::less());

    EXPECT_TRUE(std::is_sorted(a, a + TEST_SIZE));
}


TEST(QuickSortTest, CustomType)
{
    struct Person
    {
        std::string name;
        int age;

        bool operator==(const Person& other) const
        {
            return name == other.name && age == other.age;
        }
    };

    Person people[TEST_SIZE];

    for (std::size_t i = 0; i < TEST_SIZE; ++i)
    {
        people[i].name = "Person" + std::to_string(i);
        people[i].age = static_cast<int>((i * 17) % 80);
    }

    sort::quicksort(
        people,
        people + TEST_SIZE,
        [](const Person& a, const Person& b) {
            return a.age < b.age;
        }
    );

    for (std::size_t i = 1; i < TEST_SIZE; ++i)
        EXPECT_LE(people[i - 1].age, people[i].age);
}

TEST(QuickSortTest, StdArray)
{
    std::array<int, TEST_SIZE> a{ };

    for (std::size_t i = 0; i < a.size(); ++i)
        a[i] = static_cast<int>((i * 41) % TEST_SIZE);

    sort::quicksort(a.data(), a.data() + a.size(), std::less());

    EXPECT_TRUE(std::is_sorted(a.begin(), a.end()));
}


TEST(QuickSortTest, StdVector)
{
    std::vector<int> a(TEST_SIZE);

    for (std::size_t i = 0; i < a.size(); ++i)
        a[i] = static_cast<int>((i * 29) % TEST_SIZE);

    sort::quicksort(a.data(), a.data() + a.size(), std::less());

    EXPECT_TRUE(std::is_sorted(a.begin(), a.end()));
}


TEST(QuickSortTest, VectorOfStrings)
{
    std::vector<std::string> a(TEST_SIZE);

    for (std::size_t i = 0; i < a.size(); ++i)
        a[i] = "item_" + std::to_string((i * 13) % TEST_SIZE);

    sort::quicksort(a.data(), a.data() + a.size(), std::less());

    EXPECT_TRUE(std::is_sorted(a.begin(), a.end()));
}

TEST(QuickSortTest, DescendingIntegers)
{
    int a[TEST_SIZE];

    for (std::size_t i = 0; i < TEST_SIZE; ++i)
        a[i] = static_cast<int>(i);

    sort::quicksort(a, a + TEST_SIZE, std::greater());

    EXPECT_TRUE(std::is_sorted(a, a + TEST_SIZE, std::greater()));
}


TEST(QuickSortTest, StringsByLength)
{
    std::string a[TEST_SIZE];

    for (std::size_t i = 0; i < TEST_SIZE; ++i)
        a[i] = std::string((i % 20) + 1, 'x');

    sort::quicksort(
        a,
        a + TEST_SIZE,
        [](const std::string& lhs, const std::string& rhs)
        {
            return lhs.length() < rhs.length();
        }
    );

    for (std::size_t i = 1; i < TEST_SIZE; ++i)
        EXPECT_LE(a[i - 1].length(), a[i].length());
}


TEST(QuickSortTest, JustAboveInsertionThreshold)
{
    constexpr std::size_t size = sort::INSERTION_THRESHOLD + 1;

    int a[size];

    for (std::size_t i = 0; i < size; ++i)
        a[i] = static_cast<int>(size - i);

    sort::quicksort(a, a + size, std::less());

    EXPECT_TRUE(std::is_sorted(a, a + size));
}