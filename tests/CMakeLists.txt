set(TEST_TOOL Catch2)

find_package(${TEST_TOOL})


if(NOT ${TEST_TOOL}_FOUND)
    message(WARNING "${TEST_TOOL} not found: tests disabled")
    return()
endif()


include(Catch)


add_executable(dsa-tests
    "search_test.cpp"
    "sort_test.cpp"

    "list_test.cpp"
    "iterator_test.cpp"
    "vector_test.cpp"

    "heap_test.cpp"
    "queue_test.cpp"
    "stack_test.cpp"
)

target_link_libraries(dsa-tests
    PRIVATE Catch2::Catch2WithMain
    PRIVATE dsa
)


catch_discover_tests(dsa-tests)
