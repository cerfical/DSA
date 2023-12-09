find_package(GTest REQUIRED)
include(GoogleTest)

add_executable(dsa-tests
	"SearchTests.cpp"
	"SortTests.cpp"

	"HeapUtilsTests.cpp"
	"ListTests.cpp"

	"AdapterTests.hpp"
	"HeapTests.cpp"
	"QueueTests.cpp"
	"StackTests.cpp"
)

target_link_libraries(dsa-tests
	PRIVATE GTest::gtest_main
	PRIVATE GTest::gtest
	PRIVATE GTest::gmock
	PRIVATE dsa
)

gtest_discover_tests(dsa-tests)
