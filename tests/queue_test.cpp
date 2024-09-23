#include <catch2/catch_test_macros.hpp>
import dsa;


SCENARIO("manipulating queue elements", "[queue]") {
    GIVEN("a queue") {
        auto queue = dsa::Queue<int>();
        queue.push(47);

        WHEN("push() is called") {
            queue.push(12);

            THEN("put the new element on the queue's back") {
                REQUIRE(queue.back() == 12);

                AND_THEN("increase the queue size") {
                    REQUIRE(queue.size() == 2);
                }
            }
        }

        WHEN("pop() is called") {
            THEN("return the element on the queue's front") {
                REQUIRE(queue.pop() == 47);

                AND_THEN("decrease the queue size") {
                    REQUIRE(queue.size() == 0);
                }
            }
        }
    }
}
