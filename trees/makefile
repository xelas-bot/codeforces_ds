CXX = g++
INC_DIR = ../include/catch2

CXXFLAGS=-std=c++20 -Wall -Wextra -pedantic -O3
CXXFLAGS+=  $(addprefix -I, $(INC_DIR))

LDFLAGS = -L../lib/

TARGETS = base_tree.cpp
MY_INCS = base_av_tree.hpp

TARGETS_TEST = tests/test.cpp


# all: 
# 	mkdir -p target
# 	$(CXX) $(TARGETS) $(MY_INCS) $(CXXFLAGS) -o target/rbtree

test:
	g++ -I../include tests/test.cpp libCatch2Main.a libCatch2.a -o target/test
