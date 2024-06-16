#include "AdapterTest.hpp"

#include <DSA/Stack.hpp>
#include <gtest/gtest.h>


using StackTest = AdapterTest<dsa::Stack, int>;


TEST_F(StackTest, pushPutsElementInStackTop) {
    pushValueAndCheckTop(0);
    pushValueAndCheckTop(3);
    pushValueAndCheckTop(5);
    pushValueAndCheckTop(2);
}


TEST_F(StackTest, popReturnsElementInStackTop) {
    pushValues(2, 4, 1, 0);

    popAndCheckValue(0);
    popAndCheckValue(1);
    popAndCheckValue(4);
    popAndCheckValue(2);
}
