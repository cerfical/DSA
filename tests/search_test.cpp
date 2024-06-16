#include <catch2/catch_template_test_macros.hpp>
#include <catch2/catch_test_macros.hpp>
#include <dsa/search.hpp>

#include <optional>
#include <vector>


#define SEARCH_SCENARIO(testName) \
    TEMPLATE_TEST_CASE("Scenario: " testName, "[search][algo]", LinearSearch, BinarySearch)


struct BinarySearch {
    template <typename R, typename T>
    static std::optional<T> search(const R& values, const T& searchValue) {
        const auto it = dsa::binarySearch(values, searchValue);
        if(it != values.cend()) {
            return *it;
        }
        return {};
    }
};

struct LinearSearch {
    template <typename R, typename T>
    static std::optional<T> search(const R& values, const T& searchValue) {
        const auto it = dsa::linearSearch(values, searchValue);
        if(it != values.cend()) {
            return *it;
        }
        return {};
    }
};


SEARCH_SCENARIO("searching for a value") {
    GIVEN("an empty sequence") {
        const auto empty = std::vector<int>();

        AND_GIVEN("an arbitrary value") {
            const auto searchValue = 0;

            THEN("report unsuccessful search") {
                REQUIRE_FALSE(TestType::search(empty, searchValue));
            }
        }
    }

    GIVEN("a non-empty sequence") {
        auto list = std::vector<int>{ 1, 2, 3, 4, 5 };

        AND_GIVEN("a search value that is not present in the sequence") {
            const auto searchValue = 0;

            THEN("report unsuccessful search") {
                REQUIRE_FALSE(TestType::search(list, searchValue));
            }
        }

        AND_GIVEN("a search value that is the first element of the sequence") {
            const auto searchValue = 1;

            THEN("report successful search") {
                REQUIRE(TestType::search(list, searchValue));
            }
        }

        AND_GIVEN("a search value that is the last element of the sequence") {
            const auto searchValue = 5;

            THEN("report successful search") {
                REQUIRE(TestType::search(list, searchValue));
            }
        }

        AND_GIVEN("a search value that is the middle element of the sequence") {
            const auto searchValue = 3;

            THEN("report successful search") {
                REQUIRE(TestType::search(list, searchValue));
            }
        }
    }
}
