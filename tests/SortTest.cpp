#include <gtest/gtest.h>
#include <DSA/Sort.hpp>

#include <algorithm>
#include <vector>



struct BubbleSort {
	template <typename R> void operator()(R&& data) const {
		dsa::bubbleSort(std::forward<R>(data));
	}
};

struct SelectionSort {
	template <typename R> void operator()(R&& data) const {
		dsa::selectionSort(std::forward<R>(data));
	}
};

struct InsertionSort {
	template <typename R> void operator()(R&& data) const {
		dsa::insertionSort(std::forward<R>(data));
	}
};

struct MergeSort {
	template <typename R> void operator()(R&& data) const {
		dsa::mergeSort(std::forward<R>(data));
	}
};

struct QuickSort {
	template <typename R> void operator()(R&& data) const {
		dsa::quickSort(std::forward<R>(data));
	}
};



using SortAlgos = testing::Types<BubbleSort, SelectionSort, InsertionSort, MergeSort, QuickSort>;

template <typename SortAlgo>
class SortTests : public testing::Test {
protected:

	void sortAndEnsureSorted(std::vector<int> data) {
		auto sortedData = data;
		std::ranges::sort(sortedData);
		SortAlgo()(data);

		ASSERT_EQ(data, sortedData);
	}

};

TYPED_TEST_SUITE(SortTests, SortAlgos);



TYPED_TEST(SortTests, emptySequence) {
	this->sortAndEnsureSorted({});
}

TYPED_TEST(SortTests, singleElementSequence) {
	this->sortAndEnsureSorted({ 15 });
}

TYPED_TEST(SortTests, twoElementSequence) {
	this->sortAndEnsureSorted({ 2, 1 });
	this->sortAndEnsureSorted({ 1, 2 });
	this->sortAndEnsureSorted({ 1, 1 });
}

TYPED_TEST(SortTests, threeElementSequence) {
	// unique elements
	this->sortAndEnsureSorted({ 1, 2, 3 });
	this->sortAndEnsureSorted({ 1, 3, 2 });
	this->sortAndEnsureSorted({ 2, 1, 3 });
	this->sortAndEnsureSorted({ 2, 3, 1 });
	this->sortAndEnsureSorted({ 3, 2, 1 });
	this->sortAndEnsureSorted({ 3, 1, 2 });

	// non-unique elements
	this->sortAndEnsureSorted({ 2, 1, 1 });
	this->sortAndEnsureSorted({ 1, 2, 1 });
	this->sortAndEnsureSorted({ 1, 1, 2 });

	this->sortAndEnsureSorted({ 1, 2, 2 });
	this->sortAndEnsureSorted({ 2, 1, 2 });
	this->sortAndEnsureSorted({ 2, 2, 1 });

	this->sortAndEnsureSorted({ 2, 2, 2 });
}



TYPED_TEST(SortTests, sortedSequenceWithUniqueElements) {
	this->sortAndEnsureSorted({ -15, -14, -13, -10, 0, 2, 5, 12, 13, 15, 18 });
}

TYPED_TEST(SortTests, reverseSortedSequenceWithUniqueElements) {
	this->sortAndEnsureSorted({ 16, 9, 8, 5, 4, 0, -1, -5, -7, -10, -12, -14 });
}

TYPED_TEST(SortTests, unsortedSequenceWithUniqueElements) {
	this->sortAndEnsureSorted({ -10, 0, 3, 5, 10, 15, -12, 12, 2, 6, 11 });
}



TYPED_TEST(SortTests, sortedSequenceWithRepetitions) {
	this->sortAndEnsureSorted({ -19, -19, -18, -17, -1, 0, 0, 10, 12, 12, 13, 15 });
}

TYPED_TEST(SortTests, reverseSortedSequenceWithRepetitions) {
	this->sortAndEnsureSorted({ 20, 19, 17, 10, 9, 9, 1, 1, 0, 0, -1, -1, -10, -12, -13, -13 });
}

TYPED_TEST(SortTests, unsortedSequenceWithRepetitions) {
	this->sortAndEnsureSorted({ 10, 20, 35, 35, 10, 0, -10, -15, -15, 0, 20, 35, 35, 10, -12 });
}
