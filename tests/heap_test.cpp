#include <catch2/catch_test_macros.hpp>
#include <dsa/Heap.hpp>

SCENARIO("manipulating heap elements", "[heap]") {
    GIVEN("a heap") {
        auto heap = dsa::Heap<int>();
        heap.push(47);

        AND_GIVEN("a value greater than any element of the heap") {
            WHEN("push() is called") {
                heap.push(48);

                THEN("put the new element on the heap's top") {
                    REQUIRE(heap.top() == 48);
                }
            }
        }

        AND_GIVEN("a value smaller than any element of the heap") {
            WHEN("push() is called") {
                heap.push(46);

                THEN("don't change the heap's top") {
                    REQUIRE(heap.top() == 47);
                }
            }
        }

        WHEN("push() is called") {
            heap.push(0);

            THEN("increase the heap size") {
                REQUIRE(heap.size() == 2);
            }
        }

        WHEN("pop() is called") {
            THEN("return the element on the heap's top") {
                REQUIRE(heap.pop() == 47);

                AND_THEN("decrease the heap size") {
                    REQUIRE(heap.size() == 0);
                }
            }
        }
    }
}
