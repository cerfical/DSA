#include <dsa/List.hpp>

#include <catch2/catch_test_macros.hpp>

using namespace dsa;


SCENARIO("new elements can be added to list", "[list]") {
    GIVEN("a list") {
        auto list = List<int>{ 1, 2, 3 };

        WHEN("pushBack() is called") {
            list.pushBack(12);

            THEN("increase the list size") {
                REQUIRE(list.size() == 4);

                AND_THEN("put the new element to the list's back") {
                    REQUIRE(list.back() == 12);
                }
            }
        }

        WHEN("pushFront() is called") {
            list.pushFront(47);

            THEN("increase the list size") {
                REQUIRE(list.size() == 4);

                AND_THEN("put the new element to the list's front") {
                    REQUIRE(list.front() == 47);
                }
            }
        }
    }
}


SCENARIO("elements can be removed from list", "[list]") {
    GIVEN("a non-empty list") {
        auto list = List<int>{ 1, 2, 3 };

        WHEN("popBack() is called") {
            THEN("return the last element in the list") {
                REQUIRE(list.popBack() == 3);

                AND_THEN("decrease the list size") {
                    REQUIRE(list.size() == 2);

                    AND_THEN("remove the last element from the list") {
                        REQUIRE(list.back() == 2);
                    }
                }
            }
        }

        WHEN("popFront() is called") {
            THEN("return the first element in the list") {
                REQUIRE(list.popFront() == 1);

                AND_THEN("decrease the list size") {
                    REQUIRE(list.size() == 2);

                    AND_THEN("remove the first element from the list") {
                        REQUIRE(list.front() == 2);
                    }
                }
            }
        }
    }
}
