set(TEST_TOOL GTest)

find_package(${TEST_TOOL})


if(NOT ${TEST_TOOL}_FOUND)
    message(WARNING "${TEST_TOOL} not found: tests disabled")
    return()
endif()


include(GoogleTest)


add_executable(dsa-tests
    "SearchTest.cpp"
    "SortTest.cpp"

    "HeapUtilTest.cpp"
    "ListTest.cpp"

    "HeapTest.cpp"
    "QueueTest.cpp"
    "StackTest.cpp"
)

target_sources(dsa-tests INTERFACE FILE_SET HEADERS
    FILES "AdapterTest.hpp"    
)

target_link_libraries(dsa-tests
    PRIVATE GTest::gtest_main
    PRIVATE GTest::gtest
    PRIVATE GTest::gmock

    PRIVATE dsa
)


gtest_discover_tests(dsa-tests)
