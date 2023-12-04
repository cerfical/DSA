#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <DSA/Sort.hpp>

#include <algorithm>
#include <vector>

MATCHER(IsSorted, negation ? "unsorted container" : "sorted container") {
	if(std::ranges::is_sorted(arg)) {
		*result_listener << "whose elements are in order";
		return true;
	} else {
		*result_listener << "whose elements are out of order";
		return false;
	}
}

using DataSample = std::vector<int>;
using SortTest = testing::TestWithParam<DataSample>;

TEST_P(SortTest, BubbleSort) {
	auto data = GetParam();
	dsa::bubbleSort(data);

	ASSERT_THAT(data, IsSorted());
}

TEST_P(SortTest, SelectionSort) {
	auto data = GetParam();
	dsa::selectionSort(data);
	
	ASSERT_THAT(data, IsSorted());
}

TEST_P(SortTest, InsertionSort) {
	auto data = GetParam();
	dsa::insertionSort(data);
	
	ASSERT_THAT(data, IsSorted());
}

TEST_P(SortTest, MergeSort) {
	auto data = GetParam();
	dsa::mergeSort(data);
	
	ASSERT_THAT(data, IsSorted());
}

TEST_P(SortTest, QuickSort) {
	auto data = GetParam();
	dsa::quickSort(data);

	ASSERT_THAT(data, IsSorted());
}

INSTANTIATE_TEST_SUITE_P(, SortTest, testing::Values(
	DataSample({ }), // empty sequence
	DataSample({ 10 }), // sequence with only one element
	DataSample({ 15, -10 }), // two elements
	DataSample({ -10, 0, 100 }), // three elements
	DataSample({ -10, 0, 0, 15, 100, 150, -125, 125, 125, 0, 10 }), // elements in random order
	DataSample({ -150, -150, -15, -10, 0, 0, 50, 120, 130, 135 }), // sorted elements
	DataSample({ 100, 90, 90, 85, 15, 0, 0, -5, -5, -10, -75, -330 }) // elements sorted in reverse order
));
