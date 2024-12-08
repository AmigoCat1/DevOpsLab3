include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/heads/main.zip

)
FetchContent_MakeAvailable(googletest)
enable_testing()
add_executable(test_func test_func.cpp func.cpp)
target_link_libraries(test_func gtest gtest_main)
add_test(NAME test_func COMMAND test_func)
