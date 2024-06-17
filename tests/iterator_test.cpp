#include <dsa/List.hpp>
#include <dsa/Vector.hpp>

#include <catch2/catch_template_test_macros.hpp>
#include <catch2/catch_test_macros.hpp>


using List = dsa::List<int>;
using Vector = dsa::Vector<int>;

#define ITERATOR_SCENARIO(testName) TEMPLATE_TEST_CASE("Scenario: " testName, "[iterator]", List, Vector)


ITERATOR_SCENARIO("comparing iterators") {
    const auto cont = TestType{ 1, 2, 3 };

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


ITERATOR_SCENARIO("iterator movement") {
    const auto cont = TestType{ 1, 2, 3 };

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
