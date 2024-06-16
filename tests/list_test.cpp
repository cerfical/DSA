#include <catch2/catch_test_macros.hpp>
#include <dsa/List.hpp>

#include <utility>


using namespace dsa;


class DtorCallTracer {
public:

    DtorCallTracer(const DtorCallTracer&) = delete;
    DtorCallTracer& operator=(const DtorCallTracer&) = delete;


    DtorCallTracer(DtorCallTracer&& other) noexcept {
        dtorCalls_ = std::exchange(other.dtorCalls_, {});
    }

    DtorCallTracer& operator=(DtorCallTracer&& other) noexcept {
        dtorCalls_ = std::exchange(other.dtorCalls_, {});
        return *this;
    }


    DtorCallTracer(int* dtorCalls = {}) noexcept
        : dtorCalls_(dtorCalls) {}

    ~DtorCallTracer() {
        if(dtorCalls_) {
            (*dtorCalls_)++;
        }
    }


private:
    int* dtorCalls_ = {};
};


SCENARIO("list can be emptied", "[list]") {
    GIVEN("a non-empty list") {
        int dtorCalls = 0;

        auto list = List<DtorCallTracer>();
        list.pushBack(&dtorCalls);
        list.pushBack(&dtorCalls);
        list.pushBack(&dtorCalls);

        WHEN("clear() is called") {
            list.clear();

            THEN("remove all elements from the list") {
                REQUIRE(list.size() == 0);

                AND_THEN("destroy the removed elements") {
                    REQUIRE(dtorCalls == 3);

                    AND_THEN("mark the list as being empty") {
                        REQUIRE(list.isEmpty());
                    }
                }
            }
        }
    }
}


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


SCENARIO("comparing list iterators", "[list][iterator]") {
    const auto list = List<int>{ 1, 2, 3 };

    GIVEN("two equivalent iterators") {
        THEN("the iterators are equal") {
            REQUIRE(list.begin() == list.begin());
        }
    }

    GIVEN("two different iterators") {
        THEN("the iterators are not equal") {
            REQUIRE(list.begin() != list.end());
        }
    }
}


SCENARIO("iterator movement", "[list][iterator]") {
    const auto list = List<int>{ 1, 2, 3 };

    GIVEN("an iterator") {
        auto it = ++list.begin();

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
