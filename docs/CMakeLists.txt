set(DOC_TOOL Doxygen)


find_package(${DOC_TOOL})

if(NOT ${DOC_TOOL}_FOUND)
    message(WARNING "${DOC_TOOL} not found: documentation disabled")
    return()
endif()


# Configure Doxygen output
set(DOXYGEN_REPEAT_BRIEF NO)
set(DOXYGEN_BUILTIN_STL_SUPPORT YES)
set(DOXYGEN_WARN_IF_UNDOCUMENTED NO)
set(DOXYGEN_INLINE_SIMPLE_STRUCTS YES)
set(DOXYGEN_INLINE_INFO NO)
set(DOXYGEN_SHOW_USED_FILES NO)
set(DOXYGEN_SHOW_FILES NO)
set(DOXYGEN_VERBATIM_HEADERS NO)
set(DOXYGEN_COLLABORATION_GRAPH NO)
set(DOXYGEN_USE_MDFILE_AS_MAINPAGE "README.md")

# Get the list of interface headers of the library
get_target_property(DSA_LIB_HEADERS
    dsa HEADER_SET
)

doxygen_add_docs(dsa-docs "${DSA_LIB_HEADERS}" "../README.md"
    ALL USE_STAMP_FILE
)
