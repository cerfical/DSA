#include <catch2/catch_test_macros.hpp>

import dsa;


static constexpr const auto* ListIteratorTags = "[list][iterator]";

SCENARIO("comparing iterators", ListIteratorTags) {
    const auto cont = dsa::List{ 1, 2, 3 };

    GIVEN("two equivalent iterators") {
        THEN("the iterators are equal") {
            REQUIRE(cont.begin() == cont.begin());
        }
    }

    GIVEN("two different iterators") {
        THEN("the iterators are not equal") {
            REQUIRE(cont.begin() != cont.end());
        }
    }
}


SCENARIO("iterator movement", ListIteratorTags) {
    const auto cont = dsa::List{ 1, 2, 3 };

    GIVEN("an iterator") {
        auto it = ++cont.begin();

        WHEN("incrementing the iterator") {
            THEN("moves the iterator to the next element") {
                REQUIRE(*(++it) == 3);
            }
        }

        WHEN("decrementing the iterator") {
            THEN("moves the iterator to the next element") {
                REQUIRE(*(--it) == 1);
            }
        }

        WHEN("post incrementing the iterator") {
            THEN("returns the unchanged iterator") {
                REQUIRE(*(it++) == 2);
            }
        }

        WHEN("post decrementing the iterator") {
            THEN("returns the unchanged iterator") {
                REQUIRE(*(it--) == 2);
            }
        }
    }
}
