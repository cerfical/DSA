#include "AdapterTests.hpp"
#include <DSA/Stack.hpp>


using StackTests = AdapterTests<dsa::Stack, int>;

TEST_F(StackTests, pushPutsElementInStackTop) {
	pushValueAndCheckTop(0);
	pushValueAndCheckTop(3);
	pushValueAndCheckTop(5);
	pushValueAndCheckTop(2);
}

TEST_F(StackTests, popReturnsElementInStackTop) {
	pushValues(2, 4, 1, 0);

	popAndCheckValue(0);
	popAndCheckValue(1);
	popAndCheckValue(4);
	popAndCheckValue(2);
}
