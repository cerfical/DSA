#include <catch2/catch_test_macros.hpp>

import dsa;


SCENARIO("manipulating stack elements", "[stack]") {
    GIVEN("a stack") {
        auto stack = dsa::Stack<int>();
        stack.push(47);

        WHEN("push() is called") {
            stack.push(12);

            THEN("put the new element on the stack's top") {
                REQUIRE(stack.top() == 12);

                AND_THEN("increase the stack size") {
                    REQUIRE(stack.size() == 2);
                }
            }
        }

        WHEN("pop() is called") {
            THEN("return the element on the stack's top") {
                REQUIRE(stack.pop() == 47);

                AND_THEN("decrease the stack size") {
                    REQUIRE(stack.size() == 0);
                }
            }
        }
    }
}
