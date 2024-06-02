#include <gtest/gtest.h>

#include <algorithm>
#include <vector>

#include <DSA/Sort.hpp>



struct BubbleSort {
	template <typename R> void operator()(R& data) const {
		dsa::bubbleSort(data);
	}
};

struct SelectionSort {
	template <typename R> void operator()(R& data) const {
		dsa::selectionSort(data);
	}
};

struct InsertionSort {
	template <typename R> void operator()(R& data) const {
		dsa::insertionSort(data);
	}
};


struct MergeSort {
	template <typename R> void operator()(R& data) const {
		dsa::mergeSort(data);
	}
};

struct QuickSort {
	template <typename R> void operator()(R& data) const {
		dsa::quickSort(data);
	}
};

struct HeapSort {
	template <typename R> void operator()(R& data) const {
		dsa::heapSort(data);
	}
};



using SortAlgos = testing::Types<BubbleSort, SelectionSort, InsertionSort, MergeSort, QuickSort, HeapSort>;

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



TYPED_TEST(SortTests, acceptsEmptySequence) {
	this->sortAndEnsureSorted({});
}

TYPED_TEST(SortTests, correctlySortsSequencesWithUniqueElements) {
	// sorted sequences
	this->sortAndEnsureSorted({ -15, -14, -13, -10, 0, 2, 5, 12, 13, 15, 18 });
	this->sortAndEnsureSorted({ 1, 2, 3 });
	this->sortAndEnsureSorted({ 1, 2 });

	// reverse sorted sequences
	this->sortAndEnsureSorted({ 16, 9, 8, 5, 4, 0, -1, -5, -7, -10, -12, -14 });
	this->sortAndEnsureSorted({ 3, 2, 1 });
	this->sortAndEnsureSorted({ 2, 1 });

	// unsorted sequences
	this->sortAndEnsureSorted({ -10, 0, 3, 5, 10, 15, -12, 12, 2, 6, 11 });
	this->sortAndEnsureSorted({ 1, 3, 2 });
	this->sortAndEnsureSorted({ 2, 1, 3 });
	this->sortAndEnsureSorted({ 2, 3, 1 });
	this->sortAndEnsureSorted({ 3, 1, 2 });
}

TYPED_TEST(SortTests, correctlySortsSequencesWithRepetitions) {
	// sorted sequences
	this->sortAndEnsureSorted({ -19, -19, -18, -17, -1, 0, 0, 10, 12, 12, 13, 15 });
	this->sortAndEnsureSorted({ 1, 1, 2 });
	this->sortAndEnsureSorted({ 1, 2, 2 });

	// reverse sorted sequences
	this->sortAndEnsureSorted({ 20, 19, 17, 10, 9, 9, 1, 1, 0, 0, -1, -1, -10, -12, -13, -13 });
	this->sortAndEnsureSorted({ 2, 2, 1 });
	this->sortAndEnsureSorted({ 2, 1, 1 });

	// unsorted sequences
	this->sortAndEnsureSorted({ 10, 20, 35, 35, 10, 0, -10, -15, -15, 0, 20, 35, 35, 10, -12 });
	this->sortAndEnsureSorted({ 1, 2, 1 });
	this->sortAndEnsureSorted({ 2, 1, 2 });
	this->sortAndEnsureSorted({ 2, 2, 2 });
	this->sortAndEnsureSorted({ 1, 1 });
	this->sortAndEnsureSorted({ 15 });
}
