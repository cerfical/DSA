#include <dsa/HeapUtil.hpp>
#include <gtest/gtest.h>

#include <algorithm>
#include <vector>


using namespace dsa;


class HeapUtilTest : public testing::Test {
protected:

    void validateHeap(const std::vector<int>& data, bool isHeap) {
        if(isHeap) {
            ASSERT_TRUE(HeapUtil::isHeap(data));
        } else {
            ASSERT_FALSE(HeapUtil::isHeap(data));
        }
    }


    void createAndValidateHeap(std::vector<int> data) {
        HeapUtil::createHeap(data);
        validateHeap(data, true);
    }

    void insertLastAndValidateHeap(std::vector<int> data, int value) {
        HeapUtil::createHeap(data);
        data.push_back(value);

        HeapUtil::insertLast(data);
        validateHeap(data, true);
    }


    void extractTopAndValidateHeap(std::vector<int> data) {
        HeapUtil::createHeap(data);
        HeapUtil::extractTop(data);
        data.pop_back();

        validateHeap(data, true);
    }

    void extractTopAndEnsureLargest(std::vector<int> data) {
        const auto max = *std::ranges::max_element(data);

        HeapUtil::createHeap(data);
        const auto value = HeapUtil::extractTop(data);

        ASSERT_EQ(value, max);
    }
};


TEST_F(HeapUtilTest, isHeapAcceptsEmptySequence) {
    validateHeap({}, true);
}


TEST_F(HeapUtilTest, isHeapCorrectlyChecksMaxHeapProperty) {
    validateHeap({ 6, 5, 4, 3, 2, 1, 0 }, true);
    validateHeap({ 6, 4, 5, 2, 3, 0, 1 }, true);
    validateHeap({ 12, 4, 11, 3, 1, 3, 10 }, true);

    validateHeap({ 0, 0, 0, 0, 0, 0, 0 }, true);
    validateHeap({ 2, 1 }, true);
    validateHeap({ 1 }, true);

    validateHeap({ 0, 1, 2, 3, 4, 5, 6 }, false);

    validateHeap({ 5, 3, 2, 2, 4, 0, 1 }, false);
    validateHeap({ 5, 4, 3, 2, 1, 0, 6 }, false);
    validateHeap({ 1, 2 }, false);
}


TEST_F(HeapUtilTest, createHeapAcceptsEmptySequence) {
    createAndValidateHeap({});
}


TEST_F(HeapUtilTest, createHeapEnforcesMaxHeapProperty) {
    createAndValidateHeap({ 9, 2, 0, 1, 2, 3, 2, 4, 8, 7, 6, 0 });

    createAndValidateHeap({ 1, 2, 3, 4, 5, 6, 7 });
    createAndValidateHeap({ 7, 6, 5, 4, 3, 2, 1 });

    createAndValidateHeap({ 1, 2 });
    createAndValidateHeap({ 0 });
}


TEST_F(HeapUtilTest, insertLastMaintainsMaxHeapProperty) {
    insertLastAndValidateHeap({ 0, 1, 2, 3, 4 }, 5); // 5 should become the top of the heap
    insertLastAndValidateHeap({ 3, 4, 5, 8, 6 }, 0); // 0 should be placed somewhere in the leaf node
    insertLastAndValidateHeap({ 1, 4, 3, 5, 6 }, 3); // 3 should become an internal node

    insertLastAndValidateHeap({ 1 }, 0);
    insertLastAndValidateHeap({ 1 }, 2);

    insertLastAndValidateHeap({}, 1);
}


TEST_F(HeapUtilTest, extractTopMaintainsMaxHeapProperty) {
    extractTopAndValidateHeap({ 0, 1, 2, 3, 4 });
    extractTopAndValidateHeap({ 0 });
}


TEST_F(HeapUtilTest, extractTopReturnsLargestElement) {
    extractTopAndEnsureLargest({ 0, 1, 2, 3, 4, 5, 6 });
}
