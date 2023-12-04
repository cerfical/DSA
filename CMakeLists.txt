cmake_minimum_required(VERSION 3.23)

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
	include(CTest)
endif()

add_library(dsa INTERFACE)

target_include_directories(dsa INTERFACE "include")
target_compile_features(dsa INTERFACE cxx_std_20)
target_sources(dsa
	INTERFACE
		"include/DSA/Sort.hpp"
		"include/DSA/Search.hpp"
)

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME AND BUILD_TESTING)
	add_subdirectory(tests)
endif()