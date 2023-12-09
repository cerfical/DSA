#include "AdapterTests.hpp"
#include <DSA/Heap.hpp>


using HeapTests = AdapterTests<dsa::Heap, int>;

TEST_F(HeapTests, pushPutsLargestElementInHeapTop) {
	pushValueAndCheckTop(0, 0);
	pushValueAndCheckTop(3, 3);
	pushValueAndCheckTop(2, 3);
	pushValueAndCheckTop(4, 4);
	pushValueAndCheckTop(5, 5);
	pushValueAndCheckTop(3, 5);
}

TEST_F(HeapTests, popReturnsLargestElement) {
	pushValues(4, 6);
	popAndCheckValue(6);

	pushValues(3, 3, 2, 5);
	popAndCheckValue(5);
	popAndCheckValue(4);
	popAndCheckValue(3);
	popAndCheckValue(3);

	pushValues(6, 0);
	popAndCheckValue(6);
	popAndCheckValue(2);
	popAndCheckValue(0);
}
