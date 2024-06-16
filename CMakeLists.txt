cmake_minimum_required(VERSION 3.23)


project(DSA LANGUAGES CXX DESCRIPTION "Classic data structures and algorithms")

include(CTest)


option(BUILD_DOCS "Generate documentation from the source tree using Doxygen" ON)


add_library(dsa INTERFACE)

target_sources(dsa INTERFACE FILE_SET HEADERS BASE_DIRS "include"
    FILES
        "include/dsa/sort.hpp"
        "include/dsa/search.hpp"
        
        "include/dsa/ListNode.hpp"
        "include/dsa/ListConstIterator.hpp"
        "include/dsa/ListIterator.hpp"
        "include/dsa/List.hpp"
    
        "include/dsa/Queue.hpp"
        "include/dsa/Stack.hpp"

        "include/dsa/heap_util.hpp"
        "include/dsa/Heap.hpp"
)


target_include_directories(dsa INTERFACE "include")

target_compile_features(dsa INTERFACE cxx_std_20)


if(BUILD_DOCS)
    add_subdirectory(docs)
endif()

if(BUILD_TESTING)
    add_subdirectory(tests)
endif()


# Generate .gitignore file to take care of the build directory automatically
file(WRITE "${CMAKE_BINARY_DIR}/.gitignore" [[
*
]])
