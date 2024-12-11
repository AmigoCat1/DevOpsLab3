AUTOMAKE_OPTIONS = foreign

bin_PROGRAMS = FuncCosh
FuncCosh_SOURCES = main.cpp 

lib_LTLIBRARIES = libFuncCosh.la
libFuncCosh_la_SOURCES = FuncCosh.cpp FuncCosh.h 

check_PROGRAMS = UnitTest
UnitTest_SOURCES = UnitTest.cpp FuncCosh.cpp FuncCosh.h calculateTime.cpp 

EXTRA_DIST = Makefile.am
