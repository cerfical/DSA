cmake_minimum_required(VERSION 3.23)


project(DSA LANGUAGES CXX DESCRIPTION "Example implementations of the classic data structures and algorithms")
include(CTest)


add_library(dsa INTERFACE)

target_sources(dsa INTERFACE FILE_SET HEADERS BASE_DIRS "include"
	FILES
		"include/DSA/Sort.hpp"
		"include/DSA/Search.hpp"
		"include/DSA/List.hpp"
		"include/DSA/Heap.hpp"
)

target_include_directories(dsa INTERFACE "include")
target_compile_features(dsa INTERFACE cxx_std_20)


if(BUILD_TESTING)
	add_subdirectory(tests)
endif()
