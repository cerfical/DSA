#include <gtest/gtest.h>
#include <DSA/Heap.hpp>


class HeapTests : public testing::Test {
protected:
	
	void pushAndCheck(int value, int expect) {
		m_data.push(value);
		ASSERT_EQ(m_data.top(), expect);
	}

	void popAndCheck(int expect) {
		ASSERT_EQ(m_data.pop(), expect);
	}

	void push(int value) {
		m_data.push(value);
	}

private:
	dsa::Heap<int> m_data;
};


TEST_F(HeapTests, pushPutsSmallestValueAtTop) {
	pushAndCheck(5, 5);
	pushAndCheck(3, 3);
	pushAndCheck(4, 3);
	pushAndCheck(1, 1);
	pushAndCheck(0, 0);
	pushAndCheck(2, 0);
}

TEST_F(HeapTests, popExtractsElementsInDescendingOrder) {
	push(4);
	push(6);
	popAndCheck(4);

	push(3);
	push(3);
	push(2);
	popAndCheck(2);
	popAndCheck(3);
	popAndCheck(3);

	push(0);
	popAndCheck(0);
	popAndCheck(6);
}
