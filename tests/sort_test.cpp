#include <catch2/catch_template_test_macros.hpp>
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers.hpp>
#include <catch2/matchers/catch_matchers_range_equals.hpp>
#include <catch2/matchers/catch_matchers_vector.hpp>
#include <dsa/sort.hpp>

#include <vector>

#define SORT_SCENARIO(testName) \
    TEMPLATE_TEST_CASE( \
        "Scenario: " testName, \
        "[sort][algo]", \
        BubbleSort, \
        SelectionSort, \
        InsertionSort, \
        MergeSort, \
        QuickSort, \
        HeapSort \
    )


using namespace Catch::Matchers;


struct BubbleSort {
    static void sort(auto& data) {
        dsa::bubbleSort(data);
    }
};

struct SelectionSort {
    static void sort(auto& data) {
        dsa::selectionSort(data);
    }
};

struct InsertionSort {
    static void sort(auto& data) {
        dsa::insertionSort(data);
    }
};

struct MergeSort {
    static void sort(auto& data) {
        dsa::mergeSort(data);
    }
};

struct QuickSort {
    static void sort(auto& data) {
        dsa::quickSort(data);
    }
};

struct HeapSort {
    static void sort(auto& data) {
        dsa::heapSort(data);
    }
};


SORT_SCENARIO("sorting ranges with unique elements") {
    GIVEN("an unordered list of values") {
        auto list = std::vector<int>{ 6, 2, 3, 1, 4, 5 };

        WHEN("sort() is called") {
            TestType::sort(list);

            THEN("arrange the list elements in ascending order") {
                REQUIRE_THAT(list, RangeEquals(std::vector<int>{ 1, 2, 3, 4, 5, 6 }));
            }
        }
    }

    GIVEN("a list of elements sorted in descending order") {
        auto list = std::vector<int>{ 6, 5, 4, 3, 2, 1 };

        WHEN("sort() is called") {
            TestType::sort(list);

            THEN("arrange the list elements in ascending order") {
                REQUIRE_THAT(list, RangeEquals(std::vector<int>{ 1, 2, 3, 4, 5, 6 }));
            }
        }
    }

    GIVEN("a list of elements sorted in ascending order") {
        auto list = std::vector<int>{ 1, 2, 3 };

        WHEN("sort() is called") {
            TestType::sort(list);

            THEN("leave the element order as is") {
                REQUIRE_THAT(list, RangeEquals(std::vector<int>{ 1, 2, 3 }));
            }
        }
    }
}


SORT_SCENARIO("sorting ranges with repetitions") {
    GIVEN("an unordered list of values") {
        auto list = std::vector<int>{ 6, 2, 3, 1, 4, 5, 4, 1, 2, 2 };

        WHEN("sort() is called") {
            TestType::sort(list);

            THEN("arrange the list elements in ascending order") {
                REQUIRE_THAT(list, RangeEquals(std::vector<int>{ 1, 1, 2, 2, 2, 3, 4, 4, 5, 6 }));
            }
        }
    }

    GIVEN("a list of elements sorted in descending order") {
        auto list = std::vector<int>{ 6, 6, 6, 6, 5, 4, 4, 3, 2, 2, 1 };

        WHEN("sort() is called") {
            TestType::sort(list);

            THEN("arrange the list elements in ascending order") {
                REQUIRE_THAT(list, RangeEquals(std::vector<int>{ 1, 2, 2, 3, 4, 4, 5, 6, 6, 6, 6 }));
            }
        }
    }

    GIVEN("a list of elements sorted in ascending order") {
        auto list = std::vector<int>{ 1, 2, 2, 2, 3, 3 };

        WHEN("sort() is called") {
            TestType::sort(list);

            THEN("leave the element order as is") {
                REQUIRE_THAT(list, RangeEquals(std::vector<int>{ 1, 2, 2, 2, 3, 3 }));
            }
        }
    }
}
