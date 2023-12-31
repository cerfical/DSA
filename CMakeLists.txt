﻿cmake_minimum_required(VERSION 3.23)


project(DSA LANGUAGES CXX DESCRIPTION "Example implementations of classic data structures and algorithms")
include(CTest)


option(BUILD_DOC "Generate documentation from source tree with Doxygen" OFF)


add_library(dsa INTERFACE)

target_sources(dsa INTERFACE FILE_SET HEADERS BASE_DIRS "include"
	FILES
		"include/DSA/DSA.hpp"
		
		"include/DSA/Sort.hpp"
		"include/DSA/Search.hpp"
		
		"include/DSA/ListNode.hpp"
		"include/DSA/ListConstIterator.hpp"
		"include/DSA/ListIterator.hpp"
		"include/DSA/List.hpp"
	
		"include/DSA/Queue.hpp"
		"include/DSA/Stack.hpp"

		"include/DSA/HeapUtils.hpp"
		"include/DSA/Heap.hpp"
)

target_include_directories(dsa INTERFACE "include")
target_compile_features(dsa INTERFACE cxx_std_20)


if(BUILD_DOC)
	add_subdirectory(docs)
endif()


if(BUILD_TESTING)
	add_subdirectory(tests)
endif()
