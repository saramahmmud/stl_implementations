find_package(Catch2 3 QUIET)
if(NOT Catch2_FOUND)
    include(FetchContent)
    FetchContent_Declare(
        Catch2 
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git 
        GIT_TAG v3.5.4
    )
    FetchContent_MakeAvailable(Catch2)
endif()

add_executable(stl_impl_tests
    test_map.cpp
)

#links with stl_impl library and catch2
target_link_libraries(stl_impl_tests PRIVATE stl_impl Catch2::Catch2WithMain) 

include(CTest)
include(Catch)

#goes through binary and individually registers test cases fo individual ctest reporting
catch_discover_tests(stl_impl_tests)