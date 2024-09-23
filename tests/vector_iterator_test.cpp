#include <dsa/Vector.hpp>

#include <catch2/catch_test_macros.hpp>


static constexpr const auto* VectorIteratorTags = "[vector][iterator]";

SCENARIO("comparing iterators", VectorIteratorTags) {
    const auto cont = dsa::Vector{ 1, 2, 3 };

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


SCENARIO("iterator movement", VectorIteratorTags) {
    const auto cont = dsa::Vector{ 1, 2, 3 };

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
