#include <DSA/Search.hpp>
#include <gtest/gtest.h>

#include <algorithm>
#include <optional>
#include <vector>


struct LinearSearch {
    template <typename R, typename T>
    auto operator()(const R& values, const T& searchValue) const {
        return dsa::linearSearch(values, searchValue);
    }
};

struct BinarySearch {
    template <typename R, typename T>
    auto operator()(R& values, const T& searchValue) const {
        std::ranges::sort(values);
        return dsa::binarySearch(values, searchValue);
    }
};


using SearchAlgos = testing::Types<LinearSearch, BinarySearch>;

template <typename SearchAlgo>
class SearchTest : public testing::Test {
protected:

    void searchAndEnsureFound(std::vector<int> values, int searchValue) {
        const auto foundValue = search(values, searchValue);

        ASSERT_TRUE(foundValue.has_value());
        ASSERT_EQ(foundValue.value(), searchValue);
    }

    void searchAndEnsureNotFound(std::vector<int> values, int searchValue) {
        const auto foundValue = search(values, searchValue);
        ASSERT_TRUE(!foundValue.has_value());
    }

private:

    std::optional<int> search(std::vector<int>& values, int searchValue) {
        const auto it = SearchAlgo()(values, searchValue);
        if(it != values.cend()) {
            return *it;
        }
        return {};
    }
};

TYPED_TEST_SUITE(SearchTest, SearchAlgos);


TYPED_TEST(SearchTest, findsNothingIfEmptySequence) {
    this->searchAndEnsureNotFound({}, 0);
}


TYPED_TEST(SearchTest, findsFirstElement) {
    this->searchAndEnsureFound({ 5, 6, 0, 0, 3, 1, -1, -5, 2, -3, 5 }, 5);
}


TYPED_TEST(SearchTest, findsLastElement) {
    this->searchAndEnsureFound({ 8, 7, -1, 2, 5, -6, -7, 9, 4, -2, -3, -9 }, -9);
}


TYPED_TEST(SearchTest, findsRandomElement) {
    this->searchAndEnsureFound({ -6, -1, -2, -5, -7, 0, 4, 7, 0, 2, 1, 3, 9 }, -5);

    this->searchAndEnsureFound({ 3, 1, 2 }, 1);
    this->searchAndEnsureFound({ 1, 5 }, 5);
    this->searchAndEnsureFound({ 1 }, 1);
}


TYPED_TEST(SearchTest, findsNothingIfAbsentElement) {
    this->searchAndEnsureNotFound({ -2, -3, 0, 4, 1, 2, 3, 2, 6, 4, 5, -4, 7 }, -1000);

    this->searchAndEnsureNotFound({ 2, 1, 3 }, 4);
    this->searchAndEnsureNotFound({ 2, 1 }, 0);
    this->searchAndEnsureNotFound({ 2 }, 3);
}
