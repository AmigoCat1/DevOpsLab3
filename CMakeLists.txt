cmake_minimum_required(VERSION 3.22) 
project(DevOpsLab3)  # Name project

# Output files
add_executable(func main.cpp func.cpp)
add_executable(test_func test_func.cpp func.cpp)

# Add library
target_link_libraries(test_func gtest gtest_main)
add_test(NAME test_func COMMAND test_func)
