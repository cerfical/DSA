cmake_minimum_required(VERSION 3.28)


project(DSA LANGUAGES CXX DESCRIPTION "Classic data structures and algorithms")

include(CTest)


option(BUILD_DOCS "Generate documentation from the source tree using Doxygen" ON)


add_library(dsa)

target_sources(dsa PUBLIC FILE_SET CXX_MODULES
    FILES
        "src/dsa.ixx"

        "src/sort.ixx"
        "src/search.ixx"
        
        "src/List.ixx"
        "src/Vector.ixx"

        "src/Queue.ixx"
        "src/Stack.ixx"

        "src/heap_util.ixx"
        "src/Heap.ixx"
)


target_include_directories(dsa INTERFACE "include")

target_compile_features(dsa PUBLIC cxx_std_20)


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
