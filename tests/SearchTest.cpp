#include <DSA/Search.hpp>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <algorithm>
#include <vector>

using testing::Contains;
using testing::Not;

using DataSample = std::vector<int>;
using SearchTest = testing::TestWithParam<std::tuple<int, DataSample>>;

TEST_P(SearchTest, LinearSearch) {
	const auto& searchValue = std::get<0>(GetParam());
	const auto& data = std::get<1>(GetParam());
	
	const auto valueFound = linearSearch(data, searchValue);
	if(valueFound != data.cend()) {
		ASSERT_EQ(*valueFound, searchValue);
	} else {
		ASSERT_THAT(data, Not(Contains(searchValue)));
	}
}

TEST_P(SearchTest, BinarySearch) {
	const auto& searchValue = std::get<0>(GetParam());
	auto data = std::get<1>(GetParam());
	std::ranges::sort(data);

	const auto valueFound = binarySearch(data, searchValue);
	if(valueFound != data.end()) {
		ASSERT_EQ(*valueFound, searchValue);
	} else {
		ASSERT_THAT(data, Not(Contains(searchValue)));
	}
}

INSTANTIATE_TEST_SUITE_P(, SearchTest, testing::Values(
	std::make_tuple(0, DataSample()), // empty sequence
	std::make_tuple(10, DataSample({ 10 })), // one element: successful search
	std::make_tuple(30, DataSample({ 20 })), // one element: failing search
	std::make_tuple(15, DataSample({ 15, 10 })), // two elements: successful search
	std::make_tuple(45, DataSample({ 10, 30 })), // two elements: failing search
	std::make_tuple(0, DataSample({ -10, 0, -30 })), // three elements: successful search
	std::make_tuple(-10, DataSample({ 90, -35, 15 })), // three elements: failing search

	std::make_tuple(0, DataSample({ -50, 65, 0, 0, 35, 145, -100, -15, 100, -100, 200 })), // random elements: successful search
	std::make_tuple(10, DataSample({ 80, 75, -10, 20, 50, -60, -70, 75, 45, -10, -15, -10 })), // random elements: failing search

	std::make_tuple(-5, DataSample({ -55, -15, -10, -5, -5, 0, 0, 0, 15, 20, 30, 45, 70 })), // sorted elements: successful search 
	std::make_tuple(-5, DataSample({ -70, -60, -40, 0, 15, 40, 80, 80, 85, 85, 90, 100 })) // sorted elements: failing search
));
