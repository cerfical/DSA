#include "AdapterTest.hpp"
#include <DSA/Queue.hpp>


using QueueTests = AdapterTests<dsa::Queue, int>;

TEST_F(QueueTests, pushPutsElementInQueueBack) {
	pushValueAndCheckBack(0);
	pushValueAndCheckBack(3);
	pushValueAndCheckBack(5);
	pushValueAndCheckBack(2);
}

TEST_F(QueueTests, popReturnsElementInQueueFront) {
	pushValues(2, 4, 1, 0);

	popAndCheckValue(2);
	popAndCheckValue(4);
	popAndCheckValue(1);
	popAndCheckValue(0);
}
