#include <gtest/gtest.h>
#include <vector>

#include <DSA/HeapUtils.hpp>


class HeapUtilsTests : public testing::Test {
protected:

	void createAndValidateHeap(std::vector<int>&& data) {
		dsa::HeapUtils::createHeap(data);
		m_data = std::move(data);

		ASSERT_TRUE(hasHeapProperty());
	}

	void heapifyAndValidate(std::vector<int>&& data, std::size_t n) {
		dsa::HeapUtils::heapify(data, n);
		m_data = std::move(data);

		ASSERT_TRUE(hasHeapProperty(n));
	}


private:
	
	bool hasHeapProperty(std::size_t n = 0) {
		return hasHeapProperty(n, dsa::HeapUtils::leftChildOf(n))
			&& hasHeapProperty(n, dsa::HeapUtils::rightChildOf(n));
	}

	bool hasHeapProperty(std::size_t n, std::size_t child) {
		if(child < m_data.size()) {
			if(m_data[child] < m_data[n] || !hasHeapProperty(child)) {
				return false;
			}
		}
		return true;
	}
	
	
	std::vector<int> m_data;
};


TEST_F(HeapUtilsTests, createHeapAcceptsEmptySequence) {
	createAndValidateHeap({});
}

TEST_F(HeapUtilsTests, createHeapEnforcesMinHeapProperty) {
	createAndValidateHeap({ 0 });
	createAndValidateHeap({ 1, 2 });

	createAndValidateHeap({ 1, 2, 3, 4, 5, 6, 7 });
	createAndValidateHeap({ 7, 6, 5, 4, 3, 2, 1 });

	createAndValidateHeap({ 9, 2, 0, 1, 2, 3, 10, 2, 4, 8, 7, 6, 0, 15 });
}


TEST_F(HeapUtilsTests, heapifyRepairsBrokenHeap) {
	heapifyAndValidate({ 3, 4, 1, 8, 9, 10, 12 }, 2);
}

TEST_F(HeapUtilsTests, heapifyPreservesWellFormedHeap) {
	heapifyAndValidate({ 0, 2, 1, 3, 4, 8, 5, 10, 9 }, 5);
}
