cmake_minimum_required(VERSION 3.50)

project(stl_impl LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON) # fail loudly if compiler doesnt support my standard

add_library(stl_impl INTERFACE) # INTERFACE means header only library, no compiled artefacts

# toggle from command line with cmake -B build -DSTL_IMPL_BUILD_BENCHMARKS=ON
option(STL_IMPL_BUILD_TESTS "Build tests" ON) 

if(STL_IMPL_BUILD_TESTS)
    enable_testing() #cmake built in test runner support (ctest)
    add_subdirectory(tests) # look in /tests for another cmakelists
endif()

