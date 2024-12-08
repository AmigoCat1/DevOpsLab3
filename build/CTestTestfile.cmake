# CMake generated Testfile for 
# Source directory: /home/andrey/DevOpsLab3
# Build directory: /home/andrey/DevOpsLab3/build
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(test_func "/home/andrey/DevOpsLab3/build/test_func")
set_tests_properties(test_func PROPERTIES  _BACKTRACE_TRIPLES "/home/andrey/DevOpsLab3/CMakeLists.txt;11;add_test;/home/andrey/DevOpsLab3/CMakeLists.txt;0;")
subdirs("_deps/googletest-build")
