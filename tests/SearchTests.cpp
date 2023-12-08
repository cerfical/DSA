#include <gtest/gtest.h>
#include <DSA/Search.hpp>

#include <algorithm>
#include <optional>
#include <vector>



struct LinearSearch {
	template <typename R, typename T>
	auto operator()(R&& values, T&& searchValue) const {
		return dsa::linearSearch(std::forward<R>(values), std::forward<T>(searchValue));
	}
};

struct BinarySearch {
	template <typename R, typename T>
	auto operator()(R&& values, T&& searchValue) const {
		std::ranges::sort(std::forward<R>(values));
		return dsa::binarySearch(std::forward<R>(values), std::forward<T>(searchValue));
	}
};



using SearchAlgos = testing::Types<LinearSearch, BinarySearch>;

template <typename SearchAlgo>
class SearchTests : public testing::Test {
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

TYPED_TEST_SUITE(SearchTests, SearchAlgos);



TYPED_TEST(SearchTests, searchOnEmptySequence) {
	this->searchAndEnsureNotFound({}, 0);
}

TYPED_TEST(SearchTests, searchOnSingleElementSequence) {
	this->searchAndEnsureFound({ 10 }, 10);
	this->searchAndEnsureNotFound({ 20 }, 30);
}

TYPED_TEST(SearchTests, firstElementSearch) {
	this->searchAndEnsureFound({ 50, 65, 0, 0, 35, 145, -100, -15, 100, -100, 200 }, 50);
}

TYPED_TEST(SearchTests, lastElementSearch) {
	this->searchAndEnsureFound({ 80, 75, -10, 20, 50, -60, -70, 75, 45, -10, -15, -10 }, -10);
}

TYPED_TEST(SearchTests, randomElementSearch) {
	this->searchAndEnsureFound({ -51, -15, -13, -5, -57, 0, 45, 70, 0, 20, 15, 30, 9 }, -5);
}

TYPED_TEST(SearchTests, absentElementSearch) {
	this->searchAndEnsureNotFound({ -2, -32, 0, 4, 100, 20, 345, 2, 203, 4, 5, 10, 12 }, -1000);
}
