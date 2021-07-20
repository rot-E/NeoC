cmake_minimum_required(VERSION 3.13)

project(NeoC
    VERSION 1.0
    DESCRIPTION "Neo C Programming Environment Library"
    LANGUAGES C
)

# guard against in-source builds
if(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
    message(FATAL_ERROR "In-source builds not allowed. Please make a new directory (called a build directory) and run CMake from there. You may need to remove CMakeCache.txt. ")
endif()

add_subdirectory(lib/NeoC)
add_subdirectory(examples EXCLUDE_FROM_ALL)