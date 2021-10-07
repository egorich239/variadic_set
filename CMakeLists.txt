cmake_minimum_required(VERSION 3.18)
project(variadic_set)

set(CMAKE_CXX_STANDARD 17)

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/2d924d7a971e9667d76ad09727fb2402b4f8a1e3.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_library(variadic_set INTERFACE)
target_include_directories(variadic_set INTERFACE .)

enable_testing()
add_executable(variadic_set_test variadic_set_test.cc)
target_link_libraries(variadic_set_test gmock_main variadic_set)

include(GoogleTest)
gtest_discover_tests(variadic_set_test)