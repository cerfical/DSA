#include <gtest/gtest.h>
#include <algorithm>
#include <vector>

#include <DSA/HeapUtils.hpp>


class HeapUtilsTests : public testing::Test {
protected:

	void validateHeap(const std::vector<int>& data, bool isHeap) {
		if(isHeap) {
			ASSERT_TRUE(dsa::HeapUtils::isHeap(data));
		} else {
			ASSERT_FALSE(dsa::HeapUtils::isHeap(data));
		}
	}


	void createAndValidateHeap(std::vector<int> data) {
		dsa::HeapUtils::createHeap(data);
		validateHeap(data, true);
	}

	void insertLastAndValidateHeap(std::vector<int> data, int value) {
		dsa::HeapUtils::createHeap(data);
		data.push_back(value);

		dsa::HeapUtils::insertLast(data);
		validateHeap(data, true);
	}


	void extractTopAndValidateHeap(std::vector<int> data) {
		dsa::HeapUtils::createHeap(data);
		dsa::HeapUtils::extractTop(data);
		data.pop_back();

		validateHeap(data, true);
	}

	void extractTopAndEnsureSmallest(std::vector<int> data) {
		const auto min = *std::ranges::min_element(data);
		
		dsa::HeapUtils::createHeap(data);
		const auto value = dsa::HeapUtils::extractTop(data);

		ASSERT_EQ(value, min);
	}

};


TEST_F(HeapUtilsTests, isHeapAcceptsEmptySequence) {
	validateHeap({}, true);
}

TEST_F(HeapUtilsTests, isHeapCorrectlyChecksMinHeapPropertyPresence) {
	validateHeap({ 0, 2, 1, 4, 3, 6, 5 }, true);
	validateHeap({ 0, 1, 2, 3, 4, 5, 6 }, true);
	validateHeap({ 2, 10, 3, 11, 12, 3, 12 }, true);
	validateHeap({ 0, 0, 0, 0, 0, 0, 0 }, true);
	validateHeap({ 1, 2 }, true);
	validateHeap({ 1 }, true);

	validateHeap({ 6, 5, 4, 3, 2, 1, 0 }, false);
	validateHeap({ 1, 3, 2, 2, 4, 6, 5 }, false);
	validateHeap({ 1, 2, 3, 4, 5, 6, 0 }, false);
	validateHeap({ 2, 1 }, false);
}


TEST_F(HeapUtilsTests, createHeapAcceptsEmptySequence) {
	createAndValidateHeap({});
}

TEST_F(HeapUtilsTests, createHeapEnforcesMinHeapProperty) {
	createAndValidateHeap({ 9, 2, 0, 1, 2, 3, 2, 4, 8, 7, 6, 0 });
	
	createAndValidateHeap({ 1, 2, 3, 4, 5, 6, 7 });
	createAndValidateHeap({ 7, 6, 5, 4, 3, 2, 1 });

	createAndValidateHeap({ 1, 2 });
	createAndValidateHeap({ 0 });
}


TEST_F(HeapUtilsTests, insertLastMaintainsMinHeapProperty) {
	insertLastAndValidateHeap({ 0, 1, 2, 3, 4 }, 5); // 5 should be placed somewhere in the leaf node
	insertLastAndValidateHeap({ 3, 4, 5, 8, 6 }, 0); // 0 should become the top of the heap
	insertLastAndValidateHeap({ 1, 4, 3, 5, 6 }, 3); // 3 should become an internal node

	insertLastAndValidateHeap({ 1 }, 0);
	insertLastAndValidateHeap({ 1 }, 2);
	
	insertLastAndValidateHeap({ }, 1);
}


TEST_F(HeapUtilsTests, extractTopMaintainsMinHeapProperty) {
	extractTopAndValidateHeap({ 0, 1, 2, 3, 4 });
	extractTopAndValidateHeap({ 0 });
}

TEST_F(HeapUtilsTests, extractTopReturnsSmallestElement) {
	extractTopAndEnsureSmallest({ 0, 1, 2, 3, 4, 5, 6 });
}
