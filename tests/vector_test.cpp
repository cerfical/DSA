#include <dsa/Vector.hpp>

#include <catch2/catch_test_macros.hpp>

using namespace dsa;


SCENARIO("new elements can be added to vector", "[vector]") {
    GIVEN("a vector") {
        auto vec = Vector<int>{ 1, 2, 3 };

        WHEN("pushBack() is called") {
            vec.pushBack(12);

            THEN("increase the vector size") {
                REQUIRE(vec.size() == 4);

                AND_THEN("put the new element to the vector's back") {
                    REQUIRE(vec.back() == 12);
                }
            }
        }
    }
}


SCENARIO("elements can be removed from vector", "[vector]") {
    GIVEN("a non-empty vector") {
        auto vec = Vector<int>{ 1, 2, 3 };

        WHEN("popBack() is called") {
            THEN("return the last element in the vector") {
                REQUIRE(vec.popBack() == 3);

                AND_THEN("decrease the vector size") {
                    REQUIRE(vec.size() == 2);

                    AND_THEN("remove the last element from the list") {
                        REQUIRE(vec.back() == 2);
                    }
                }
            }
        }
    }
}


SCENARIO("manipulating vector capacity", "[vector]") {
    GIVEN("a vector") {
        auto vec = Vector<int>();

        AND_GIVEN("a capacity greater than the current one") {
            const auto newCapacity = 10;

            WHEN("reserve() is called") {
                vec.reserve(newCapacity);

                THEN("update the vector's capacity to the given one") {
                    REQUIRE(vec.capacity() >= newCapacity);
                }
            }
        }

        AND_GIVEN("a capacity not greater than the current one") {
            const auto newCapacity = 0;

            WHEN("reserve() is called") {
                vec.reserve(newCapacity);

                THEN("preserve the vector's capacity") {
                    REQUIRE(vec.capacity() == newCapacity);
                }
            }
        }
    }
}
