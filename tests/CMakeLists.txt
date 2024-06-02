find_package(GTest REQUIRED)
include(GoogleTest)

add_executable(dsa-tests
	"SearchTest.cpp"
	"SortTest.cpp"

	"HeapUtilsTest.cpp"
	"ListTest.cpp"

	"AdapterTest.hpp"
	"HeapTest.cpp"
	"QueueTest.cpp"
	"StackTest.cpp"
)

target_link_libraries(dsa-tests
	PRIVATE GTest::gtest_main
	PRIVATE GTest::gtest
	PRIVATE GTest::gmock
	PRIVATE dsa
)

gtest_discover_tests(dsa-tests)
