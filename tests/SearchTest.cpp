#include <gtest/gtest.h>
#include <DSA/Search.hpp>

#include <algorithm>
#include <optional>
#include <vector>



template <typename SearchAlgo>
class SearchTests : public testing::Test {
protected:

	void search(std::vector<int> values, int searchValue) {
		const auto it = SearchAlgo()(values, searchValue);
		if(it != values.cend()) {
			found = *it;
		} else {
			found = {};
		}
	}

	std::optional<int> found;

};



struct LinearSearch {
	auto operator()(std::vector<int>& values, int searchValue) const {
		return dsa::linearSearch(values, searchValue);
	}
};

struct BinarySearch {
	auto operator()(std::vector<int>& values, int searchValue) const {
		std::ranges::sort(values);
		return dsa::binarySearch(values, searchValue);
	}
};



using SearchAlgos = testing::Types<LinearSearch, BinarySearch>;

TYPED_TEST_SUITE(SearchTests, SearchAlgos);



TYPED_TEST(SearchTests, searchOnEmptySequence) {
	this->search({}, 0);
	ASSERT_TRUE(!this->found.has_value());
}


TYPED_TEST(SearchTests, searchOnSingleElementSequence) {
	this->search({ 10 }, 10);
	ASSERT_TRUE(this->found.has_value());
	ASSERT_EQ(this->found.value(), 10);

	this->search({ 20 }, 30);
	ASSERT_TRUE(!this->found.has_value());
}


TYPED_TEST(SearchTests, firstElementSearch) {
	this->search({ 50, 65, 0, 0, 35, 145, -100, -15, 100, -100, 200 }, 50);
	ASSERT_TRUE(this->found.has_value());
	ASSERT_EQ(this->found.value(), 50);
}


TYPED_TEST(SearchTests, lastElementSearch) {
	this->search({ 80, 75, -10, 20, 50, -60, -70, 75, 45, -10, -15, -10 }, -10);
	ASSERT_TRUE(this->found.has_value());
	ASSERT_EQ(this->found.value(), -10);
}


TYPED_TEST(SearchTests, randomElementSearch) {
	this->search({ -51, -15, -13, -5, -57, 0, 45, 70, 0, 20, 15, 30, 9 }, -5);
	ASSERT_TRUE(this->found.has_value());
	ASSERT_EQ(this->found.value(), -5);
}


TYPED_TEST(SearchTests, absentElementSearch) {
	this->search({ -2, -32, 0, 4, 100, 20, 345, 2, 203, 4, 5, 10, 12 }, -1000);
	ASSERT_TRUE(!this->found.has_value());
}
