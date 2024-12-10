
AUTOMAKE_OPTIONS = foreign

TESTS = UnitTest.cpp
bin_PROGRAMS = FuncCosh
lib_LTLIBRARIES = libFuncCosh.la
FuncCosh_SOURCES = FuncCosh.cpp FuncCosh.h calculateTime.cpp calculateTime.h HTTPserver.cpp

check_PROGRAMS = UnitTest

UnitTest_SOURCES = UnitTest.cpp FuncCosh.cpp FuncCosh.h calculateTime.cpp calculateTime.h
EXTRA_DIST = Makefile.am
