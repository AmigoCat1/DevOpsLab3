AUTOMAKE_OPTIONS = foreign

bin_PROGRAMS = FuncCosh
FuncCosh_SOURCES = main.cpp FuncCosh.cpp calculateTime.cpp HTTPserver.cpp

lib_LTLIBRARIES = libFuncCosh.la
libFuncCosh_la_SOURCES = FuncCosh.cpp calculateTime.cpp

check_PROGRAMS = UnitTest
UnitTest_SOURCES = UnitTest.cpp FuncCosh.cpp calculateTime.cpp HTTPserver.cpp

EXTRA_DIST = Makefile.am
